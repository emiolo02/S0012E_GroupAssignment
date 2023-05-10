#include "core/gltf.h"
#include "core/math/mat4.h"
#include <iostream>
#include "Material.h"

// A lot of the following code is "borrowed" 
// from https://github.com/jessey-git/fx-gltf/tree/master/examples/viewer

struct vertex
{
    vec3 position;
    vec2 UV;
    vec3 normal;
    vec4 tangent;

    vertex()
    {
        this->position = vec3();
        this->UV = vec2();
        this->normal = vec3();
    }
    vertex(vec3 pos, vec2 UV, vec3 normal, vec4 tangent)
    {
        this->position = pos;
        this->UV = UV;
        this->normal = normal;
        this->tangent = tangent;
    }

    bool operator ==(vertex rhs)
    {
        return (this->position == rhs.position &&
            this->UV == rhs.UV &&
            this->normal == rhs.normal);
    }
};

struct Primitive
{
    std::vector<vertex> vertices;

    Material material;
};

class GLTFinfo
{
public:
    GLTFinfo(){}

    struct BufferInfo
    {
        fx::gltf::Accessor const* Accessor;
    
        uint8_t const* Data;
        uint32_t DataStride;
        uint32_t TotalSize;
    
        bool hasData = false;
    };
    
    enum TexType
    {
        BaseColor   = 0,
        Normal      = 1,
        Emissive    = 2,
        AO          = 3,
        
        Undefined   =-1 
    };

    struct ImageInfo
    {
        std::string FilePath;

        uint32_t BinarySize{};
        uint8_t const* BinaryData{};

        TexType type;

        bool isEmbedded;
        std::vector<uint8_t> embeddedData;

        bool IsBinary() const noexcept
        {
            return BinaryData != nullptr;
        }
    };

    BufferInfo positionBuffer;
    BufferInfo normalBuffer;
    BufferInfo tangentBuffer;
    BufferInfo texCoordBuffer;
    BufferInfo indexBuffer;
    
    std::vector<Primitive> primitives;
    std::vector<uint32_t> indices;

    std::vector<ImageInfo> imageInfos;
    

    static GLTFinfo Load(const char* path, int meshIndex)
    {
        GLTFinfo obj;

        // Get vertex attributes
    	fx::gltf::Document doc = fx::gltf::LoadFromText(path);
    	

        fx::gltf::Mesh const& mesh = doc.meshes[meshIndex];

        for (int i = 0; i < doc.meshes.size(); i++)
        {
            fx::gltf::Primitive const& primitive = mesh.primitives[0];

            for (auto& attrib : primitive.attributes)
            {
                if (attrib.first == "POSITION")
                {
                    obj.positionBuffer = GetData(doc, doc.accessors[attrib.second]);
                    obj.positionBuffer.hasData = true;
                }
                else if (attrib.first == "NORMAL")
                {
                    obj.normalBuffer = GetData(doc, doc.accessors[attrib.second]);
                    obj.normalBuffer.hasData = true;
                }
                else if (attrib.first == "TANGENT")
                {
                    obj.tangentBuffer = GetData(doc, doc.accessors[attrib.second]);
                    obj.tangentBuffer.hasData = true;
                }
                else if (attrib.first == "TEXCOORD_0")
                {
                    obj.texCoordBuffer = GetData(doc, doc.accessors[attrib.second]);
                    obj.texCoordBuffer.hasData = true;
                }
            }

            obj.indexBuffer = GetData(doc, doc.accessors[primitive.indices]);
            obj.RawToVertex();
        }
    

        // Image
        obj.imageInfos.resize(doc.images.size());

        for (int i = 0; i < doc.images.size(); i++)
        {
            fx::gltf::Image const& image = doc.images[doc.textures[i].source];

            obj.imageInfos[i].isEmbedded = image.IsEmbeddedResource();
            
            if (!image.uri.empty() && !obj.imageInfos[i].isEmbedded)
            {
                if (i == 0)
                {
                    obj.imageInfos[i].type = TexType::BaseColor;
                }
                else if (i == doc.materials[0].normalTexture.index)
                {
                    obj.imageInfos[i].type = TexType::Normal;
                }
                else if (i == doc.materials[0].emissiveTexture.index)
                {
                    obj.imageInfos[i].type = TexType::Emissive;
                }
                else if (i == doc.materials[0].occlusionTexture.index)
                {
                    obj.imageInfos[i].type = TexType::AO;
                }
                else
                {
                    obj.imageInfos[i].type = TexType::Undefined;
                }

                obj.imageInfos[i].FilePath = (fx::gltf::detail::GetDocumentRootPath(path) / image.uri).string();
            }
            else
            {
                if (obj.imageInfos[i].isEmbedded)
                {
                    image.MaterializeData(obj.imageInfos[i].embeddedData);
                    obj.imageInfos[i].BinaryData = &obj.imageInfos[i].embeddedData[0];
                    obj.imageInfos[i].BinarySize = static_cast<uint32_t>(obj.imageInfos[i].embeddedData.size());
                }
                else
                {
                    fx::gltf::BufferView const& bufferView = doc.bufferViews[image.bufferView];
                    fx::gltf::Buffer const& buffer = doc.buffers[bufferView.buffer];
            
                    obj.imageInfos[i].BinaryData = &buffer.data[bufferView.byteOffset];
                    obj.imageInfos[i].BinarySize = bufferView.byteLength;
                }
            }
        }

        


        return obj;
    }
    
private:
    static float ByteToFloat(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3)
    {
        float f;
        unsigned char b[] = { b0, b1, b2, b3 };
        memcpy(&f, &b, sizeof(f));
        return f;
    }

    void RawToVertex()
    {
        for (int i = 0; i < this->indexBuffer.TotalSize / 2; i++)
            indices.push_back((this->indexBuffer.Data[i * 2 + 1] << 8) | this->indexBuffer.Data[i * 2]);

        std::vector<vec3> positions;
        std::vector<vec3> normals;
        std::vector<vec2> UVs;
        std::vector<vec4> tangents;

        if (this->positionBuffer.hasData)
        for (int i = 0; i < this->positionBuffer.TotalSize; i += 12)
        {
            vec3 pos;
            for (int j = 0; j < 12; j += 4)
            {
                uint8_t b[4];

                for (int k = 0; k < 4; k++)
                    b[k] = positionBuffer.Data[i + j + k];
                
                pos[j / 4] = ByteToFloat(b[0], b[1], b[2], b[3]);
            }
            
            positions.push_back(pos);
        }
        
        if (this->normalBuffer.hasData)
        for (int i = 0; i < this->normalBuffer.TotalSize; i += 12)
        {
            vec3 nor;
            for (int j = 0; j < 12; j += 4)
            {
                uint8_t b[4];

                for (int k = 0; k < 4; k++)
                    b[k] = normalBuffer.Data[i + j + k];

                nor[j / 4] = ByteToFloat(b[0], b[1], b[2], b[3]);
            }

            normals.push_back(nor);
        }

        if (this->texCoordBuffer.hasData)
        for (int i = 0; i < this->texCoordBuffer.TotalSize; i += 8)
        {
            vec2 UV;
            for (int j = 0; j < 8; j += 4)
            {
                uint8_t b[4];

                for (int k = 0; k < 4; k++)
                    b[k] = texCoordBuffer.Data[i + j + k];

                UV[j / 4] = ByteToFloat(b[0], b[1], b[2], b[3]);
            }

            UVs.push_back(UV);
        }

        if (this->tangentBuffer.hasData)
        {
            for (int i = 0; i < this->tangentBuffer.TotalSize; i += 16)
            {
                vec4 tang;
                for (int j = 0; j < 16; j += 4)
                {
                    uint8_t b[4];

                    for (int k = 0; k < 4; k++)
                        b[k] = tangentBuffer.Data[i + j + k];

                    tang[j / 4] = ByteToFloat(b[0], b[1], b[2], b[3]);
                }

                tangents.push_back(tang);
            }
        }
        else
        {
            tangents = CalcTangents(positions, UVs, normals);
        }

        std::vector<vertex> vertices;
        for (int i = 0; i < positions.size(); i++)
        {
            vertices.push_back
            (
                vertex
                (
                    positions[i],
                    UVs[i],
                    normals[i],
                    tangents[i]
                )
            );
        }

        Primitive primitive;
        primitive.vertices = vertices;
        primitives.push_back(primitive);
    }

    std::vector<vec4> CalcTangents(std::vector<vec3> positions, std::vector<vec2> UVs, std::vector<vec3> normals)
    {
        // calculate tangent xyz
        
        std::vector<vec3> tangents;
        tangents.resize(positions.size());
        for (int i = 0; i < this->indices.size(); i += 3) 
        {
            int i0 = indices[i];
            int i1 = indices[i + 1];
            int i2 = indices[i + 2];

            vec3 pos0 = positions[i0];
            vec3 pos1 = positions[i1];
            vec3 pos2 = positions[i2];

            vec2 tex0 = UVs[i0];
            vec2 tex1 = UVs[i1];
            vec2 tex2 = UVs[i2];

            vec3 edge1 = pos1 - pos0;
            vec3 edge2 = pos2 - pos0;

            vec2 uv1 = tex1 - tex0;
            vec2 uv2 = tex2 - tex0;

            float r = 1.0f / (uv1.x * uv2.y - uv1.y * uv2.x);

            vec3 tangent(
                ((edge1.x * uv2.y) - (edge2.x * uv1.y)) * r,
                ((edge1.y * uv2.y) - (edge2.y * uv1.y)) * r,
                ((edge1.z * uv2.y) - (edge2.z * uv1.y)) * r
            );

            tangents[i0] += tangent;
            tangents[i1] += tangent;
            tangents[i2] += tangent;
        }

        // final tan vector
        std::vector<vec4> finalTangs;

        for (int i = 0; i < positions.size(); i++)
        {
            vec3 n = normals[i];

            vec3 t = tangents[i] - (n * dot(n, tangents[i]));
            t = normalize(t);

            finalTangs.push_back(vec4(t.x, t.y, t.z, 1));
        }

        return finalTangs;
    }

    static uint32_t CalculateDataTypeSize(fx::gltf::Accessor const& accessor) noexcept
    {
        uint32_t elementSize = 0;
        switch (accessor.componentType)
        {
        case fx::gltf::Accessor::ComponentType::Byte:
        case fx::gltf::Accessor::ComponentType::UnsignedByte:
            elementSize = 1;
            break;
        case fx::gltf::Accessor::ComponentType::Short:
        case fx::gltf::Accessor::ComponentType::UnsignedShort:
            elementSize = 2;
            break;
        case fx::gltf::Accessor::ComponentType::Float:
        case fx::gltf::Accessor::ComponentType::UnsignedInt:
            elementSize = 4;
            break;
        }

        switch (accessor.type)
        {
        case fx::gltf::Accessor::Type::Mat2:
            return 4 * elementSize;
            break;
        case fx::gltf::Accessor::Type::Mat3:
            return 9 * elementSize;
            break;
        case fx::gltf::Accessor::Type::Mat4:
            return 16 * elementSize;
            break;
        case fx::gltf::Accessor::Type::Scalar:
            return elementSize;
            break;
        case fx::gltf::Accessor::Type::Vec2:
            return 2 * elementSize;
            break;
        case fx::gltf::Accessor::Type::Vec3:
            return 3 * elementSize;
            break;
        case fx::gltf::Accessor::Type::Vec4:
            return 4 * elementSize;
            break;
        }

        return 0;
    }

    static BufferInfo GetData(fx::gltf::Document const& doc, fx::gltf::Accessor const& accessor)
    {
        fx::gltf::BufferView const& bufferView = doc.bufferViews[accessor.bufferView];
        fx::gltf::Buffer const& buffer = doc.buffers[bufferView.buffer];

        const uint32_t dataTypeSize = CalculateDataTypeSize(accessor);
        return BufferInfo{ &accessor, &buffer.data[static_cast<uint64_t>(bufferView.byteOffset) + accessor.byteOffset], dataTypeSize, accessor.count * dataTypeSize };
    }
};