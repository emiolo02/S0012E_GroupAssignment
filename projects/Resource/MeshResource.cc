#include "config.h"
#include "MeshResource.h"


MeshResource::MeshResource()
{
	this->primitives.resize(1);
}



MeshResource
MeshResource::CreateCube(float width, float height, float depth)
{
	MeshResource mesh;

	//front
	//mesh.vertices.push_back(vertex(vec3(-0.5f * width, -0.5f * height,  0.5f * depth), vec4(1, 1, 1, 1), vec2(0.0f, 0.0f), vec3(0, 0, 0)));
	//mesh.vertices.push_back(vertex(vec3( 0.5f * width, -0.5f * height,  0.5f * depth), vec4(1, 1, 1, 1), vec2(1.0f, 0.0f), vec3(0, 0, 0)));
	//mesh.vertices.push_back(vertex(vec3( 0.5f * width,  0.5f * height,  0.5f * depth), vec4(1, 1, 1, 1), vec2(1.0f, 1.0f), vec3(0, 0, 0)));
	//mesh.vertices.push_back(vertex(vec3(-0.5f * width,  0.5f * height,  0.5f * depth), vec4(1, 1, 1, 1), vec2(0.0f, 1.0f), vec3(0, 0, 0)));
	//
	////bottom
	//mesh.vertices.push_back(vertex(vec3(-0.5f * width, -0.5f * height,  0.5f * depth), vec4(1, 1, 1, 1), vec2(0.0f, 1.0f), vec3(0, 0, 0)));
	//mesh.vertices.push_back(vertex(vec3( 0.5f * width, -0.5f * height,  0.5f * depth), vec4(1, 1, 1, 1), vec2(1.0f, 1.0f), vec3(0, 0, 0)));
	//mesh.vertices.push_back(vertex(vec3(-0.5f * width, -0.5f * height, -0.5f * depth), vec4(1, 1, 1, 1), vec2(0.0f, 0.0f), vec3(0, 0, 0)));
	//mesh.vertices.push_back(vertex(vec3( 0.5f * width, -0.5f * height, -0.5f * depth), vec4(1, 1, 1, 1), vec2(0.0f, 1.0f), vec3(0, 0, 0)));
	//
	////top
	//mesh.vertices.push_back(vertex(vec3( 0.5f * width,  0.5f * height,  0.5f * depth), vec4(1, 1, 1, 1), vec2(0.0f, 1.0f), vec3(0, 0, 0)));
	//mesh.vertices.push_back(vertex(vec3(-0.5f * width,  0.5f * height,  0.5f * depth), vec4(1, 1, 1, 1), vec2(0.0f, 0.0f), vec3(0, 0, 0)));
	//mesh.vertices.push_back(vertex(vec3( 0.5f * width,  0.5f * height, -0.5f * depth), vec4(1, 1, 1, 1), vec2(1.0f, 1.0f), vec3(0, 0, 0)));
	//mesh.vertices.push_back(vertex(vec3(-0.5f * width,  0.5f * height, -0.5f * depth), vec4(1, 1, 1, 1), vec2(0.0f, 1.0f), vec3(0, 0, 0)));
	//
	////left
	//mesh.vertices.push_back(vertex(vec3(-0.5f * width, -0.5f * height,  0.5f * depth), vec4(1, 1, 1, 1), vec2(1.0f, 0.0f), vec3(0, 0, 0)));
	//mesh.vertices.push_back(vertex(vec3(-0.5f * width,  0.5f * height,  0.5f * depth), vec4(1, 1, 1, 1), vec2(1.0f, 1.0f), vec3(0, 0, 0)));
	//mesh.vertices.push_back(vertex(vec3(-0.5f * width, -0.5f * height, -0.5f * depth), vec4(1, 1, 1, 1), vec2(0.0f, 0.0f), vec3(0, 0, 0)));
	//mesh.vertices.push_back(vertex(vec3(-0.5f * width,  0.5f * height, -0.5f * depth), vec4(1, 1, 1, 1), vec2(0.0f, 1.0f), vec3(0, 0, 0)));
	//
	////right
	//mesh.vertices.push_back(vertex(vec3( 0.5f * width, -0.5f * height,  0.5f * depth), vec4(1, 1, 1, 1), vec2(0.0f, 0.0f), vec3(0, 0, 0)));
	//mesh.vertices.push_back(vertex(vec3( 0.5f * width,  0.5f * height,  0.5f * depth), vec4(1, 1, 1, 1), vec2(0.0f, 1.0f), vec3(0, 0, 0)));
	//mesh.vertices.push_back(vertex(vec3( 0.5f * width, -0.5f * height, -0.5f * depth), vec4(1, 1, 1, 1), vec2(1.0f, 0.0f), vec3(0, 0, 0)));
	//mesh.vertices.push_back(vertex(vec3( 0.5f * width,  0.5f * height, -0.5f * depth), vec4(1, 1, 1, 1), vec2(1.0f, 1.0f), vec3(0, 0, 0)));
	//
	////back
	//mesh.vertices.push_back(vertex(vec3(-0.5f * width, -0.5f * height, -0.5f * depth), vec4(1, 1, 1, 1), vec2(0.0f, 1.0f), vec3(0, 0, 0)));
	//mesh.vertices.push_back(vertex(vec3( 0.5f * width, -0.5f * height, -0.5f * depth), vec4(1, 1, 1, 1), vec2(1.0f, 1.0f), vec3(0, 0, 0)));
	//mesh.vertices.push_back(vertex(vec3( 0.5f * width,  0.5f * height, -0.5f * depth), vec4(1, 1, 1, 1), vec2(1.0f, 0.0f), vec3(0, 0, 0)));
	//mesh.vertices.push_back(vertex(vec3(-0.5f * width,  0.5f * height, -0.5f * depth), vec4(1, 1, 1, 1), vec2(0.0f, 0.0f), vec3(0, 0, 0)));


	//mesh.pos =
	//{
	//	//front
	//	-0.5f * width, -0.5f * height,  0.5f * depth,
	//	 0.5f * width, -0.5f * height,  0.5f * depth,
	//	 0.5f * width,  0.5f * height,  0.5f * depth,
	//	-0.5f * width,  0.5f * height,  0.5f * depth,
	//
	//	//bottom
	//	-0.5f * width, -0.5f * height,  0.5f * depth,
	//	 0.5f * width, -0.5f * height,  0.5f * depth,
	//	-0.5f * width, -0.5f * height, -0.5f * depth,
	//	 0.5f * width, -0.5f * height, -0.5f * depth,
	//
	//	 //top
	//	 0.5f * width,  0.5f * height,  0.5f * depth,
	//	-0.5f * width,  0.5f * height,  0.5f * depth,
	//	 0.5f * width,  0.5f * height, -0.5f * depth,
	//	-0.5f * width,  0.5f * height, -0.5f * depth,
	//
	//	//left
	//	-0.5f * width, -0.5f * height,  0.5f * depth,
	//	-0.5f * width,  0.5f * height,  0.5f * depth,
	//	-0.5f * width, -0.5f * height, -0.5f * depth,
	//	-0.5f * width,  0.5f * height, -0.5f * depth,
	//
	//	//right
	//	 0.5f * width, -0.5f * height,  0.5f * depth,
	//	 0.5f * width,  0.5f * height,  0.5f * depth,
	//	 0.5f * width, -0.5f * height, -0.5f * depth,
	//	 0.5f * width,  0.5f * height, -0.5f * depth,
	//
	//	//back
	//	-0.5f * width, -0.5f * height, -0.5f * depth,
	//	 0.5f * width, -0.5f * height, -0.5f * depth,
	//	 0.5f * width,  0.5f * height, -0.5f * depth,
	//	-0.5f * width,  0.5f * height, -0.5f * depth
	//};
	//
	//mesh.color =
	//{
	//	1, 0, 0, 1,
	//	0, 1, 0, 1,
	//	0, 0, 1, 1,
	//	1, 0, 1, 1,
	//	1, 0, 0, 1,
	//	0, 1, 0, 1,
	//	0, 0, 1, 1,
	//	1, 0, 1, 1
	//};
	//
	//mesh.texCoord =
	//{
	//	//front
	//	0.0f, 0.0f,
	//	1.0f, 0.0f,
	//	1.0f, 1.0f,
	//	0.0f, 1.0f,
	//	//bottom
	//	0.0f, 1.0f,
	//	1.0f, 1.0f,
	//	0.0f, 0.0f,
	//	0.0f, 1.0f,
	//	//top
	//	0.0f, 1.0f,
	//	0.0f, 0.0f,
	//	1.0f, 1.0f,
	//	0.0f, 1.0f,
	//	//left
	//	1.0f, 0.0f,
	//	1.0f, 1.0f,
	//	0.0f, 0.0f,
	//	0.0f, 1.0f,
	//	//right
	//	0.0f, 0.0f,
	//	0.0f, 1.0f,
	//	1.0f, 0.0f,
	//	1.0f, 1.0f,
	//	//back
	//	0.0f, 1.0f,
	//	1.0f, 1.0f,
	//	1.0f, 0.0f,
	//	0.0f, 0.0f,
	//};
	//
	mesh.ind =
	{
		0, 1, 2,
		2, 3, 0,
	
		4, 5, 6,
		6, 7, 5,
	
		8, 9, 10,
		10, 11, 9,
	
		12, 13, 14,
		14, 15, 13,
	
		16, 17, 18,
		18, 19, 17,
	
		20, 21, 22,
		22, 23, 20
	};
	return mesh;
}

MeshResource
MeshResource::CreateSphere(float radius, int resolution)
{
	MeshResource mesh;
	//
	//float PI = 3.14159;
	//
	//float phi, theta;
	//float x, y, z;
	//
	//float latStep = PI / resolution;
	//float longStep = 2 * PI / resolution;
	//
	//
	//for (int lat = 0; lat < resolution; ++lat)
	//{
	//	phi = PI / 2 - lat * latStep;
	//
	//	y = radius * sin(phi);
	//
	//	for (int longi = 0; longi < resolution; ++longi)
	//	{
	//		theta = longi * longStep;
	//
	//		x = radius * cos(phi) * cos(theta);
	//		z = radius * cos(phi) * sin(theta);
	//
	//		mesh.pos.push_back(x);
	//		mesh.pos.push_back(y);
	//		mesh.pos.push_back(z);
	//
	//		mesh.texCoord.push_back((float)longi / resolution);
	//		mesh.texCoord.push_back((float)lat / resolution);
	//	}
	//}
	//
	//int p1, p2;
	//
	//for (int lat = 0; lat < resolution; ++lat)
	//{
	//	p1 = lat * (resolution + 1);
	//	p2 = p1 + resolution + 1;
	//
	//	for (int longi = 0; longi < resolution; ++longi, ++p1, ++p2)
	//	{
	//		if (lat != 0)
	//		{
	//			mesh.ind.push_back(p1);
	//			mesh.ind.push_back(p2);
	//			mesh.ind.push_back(p1 + 1);
	//		}
	//		if (lat != resolution-1)
	//		{
	//			mesh.ind.push_back(p1+1);
	//			mesh.ind.push_back(p2);
	//			mesh.ind.push_back(p2 + 1);
	//		}
	//
	//		mesh.ind.push_back(p1);
	//		mesh.ind.push_back(p2);
	//		if (lat != 0)
	//		{
	//			mesh.ind.push_back(p1);
	//			mesh.ind.push_back(p1 + 1);
	//		}
	//	}
	//}
	//
	return mesh;
}

void split(std::string &str, char separator, std::vector<std::string> &out)
{
	// create a stream from the string  
	std::stringstream s(str);

	std::string s2;
	while (getline(s, s2, separator))
	{
		out.push_back(s2); // store the string in s2  
	}
}

MeshResource
MeshResource::LoadOBJ(std::string path)
{
	MeshResource mesh;

	std::ifstream stream(path);

	std::string line;

	std::vector<vec3> positions;
	std::vector<vec2> UVs;
	std::vector<vec3> normals;
	std::vector<GLuint> indPos;
	std::vector<GLuint> indUV;
	std::vector<GLuint> indNor;

	if (stream.good() == false)
	{
		std::cout << "Could not find file at " << path << std::endl;
		return mesh;
	}

	while (getline(stream, line))
	{
		std::string prefix;
		if (line.length() > 2)
			prefix = line.substr(0, 2);

		if (prefix[0] != '#')
		{

			if (prefix == "v ")
			{
				std::vector<std::string> out;

				split(line, ' ', out);
				vec3 position;

				for (int i = 1; i < 4; i++)
					position[i - 1] = std::stof(out[i]);

				positions.push_back(position);
			}

			if (prefix == "vt")
			{
				std::vector<std::string> out;

				split(line, ' ', out);
				vec2 UV = vec2(std::stof(out[1]), std::stof(out[2]));

				UVs.push_back(UV);
			}

			if (prefix == "vn")
			{
				std::vector<std::string> out;

				split(line, ' ', out);
				vec3 normal;

				for (int i = 1; i < 4; i++)
					normal[i - 1] = std::stof(out[i]);

				normals.push_back(normal);
			}

			if (prefix == "f ")
			{
				std::vector<std::string> out;

				split(line, ' ', out);

				for (int i = 1; i < 4; i++)
				{
					std::vector<std::string> out1; //splits indicies
					split(out[i], '/', out1);
					indPos.push_back((GLuint)std::stoi(out1[0]) - 1);
					indUV.push_back((GLuint)std::stoi(out1[1]) - 1);
					indNor.push_back((GLuint)std::stoi(out1[2]) - 1);
				}
			}
		}
	}

	std::vector<vertex> vertices;
	vertices.resize(indPos.size());

	for (int i = 0; i < indPos.size(); ++i)
	{
		vertices[i].position = positions[indPos[i]];
		vertices[i].UV = UVs[indUV[i]];
		vertices[i].normal = normals[indNor[i]];
	}

	bool found = false;
	for (int i = 0; i < indPos.size(); i++)
	{
		found = false;
		for (int j = 0; j < mesh.primitives[0].vertices.size(); j++)
		{
			if (vertices[i] == mesh.primitives[0].vertices[j])
			{
				mesh.ind.push_back(j);
				found = true;
			}
		}
		if (!found)
		{
			mesh.primitives[0].vertices.push_back(vertices[i]);
			mesh.ind.push_back(mesh.primitives[0].vertices.size() - 1);
		}
	}

	return mesh;
}

std::string GetTexPath(std::string mtlPath)
{
	std::ifstream stream(mtlPath);
	std::string line;

	if (stream.good() == false)
	{
		std::cout << "Could not find file at " << mtlPath << std::endl;
		return "";
	}

	while (getline(stream, line))
	{
		std::vector<std::string> lineContent;
		split(line, ' ', lineContent);

		if (lineContent.size() == 0)
			continue;

		if (lineContent[0] != "#")
		{
			if (lineContent[0] == "map_Kd")
				return lineContent[1];
		}
	}

	std::cout << "Could not find texture path at " << mtlPath << std::endl;
}

MeshResource
MeshResource::LoadOBJ(std::string path, std::string& outTexPath)
{
	MeshResource mesh;

	std::ifstream stream(path);

	std::string line;

	std::vector<vec3> positions;
	std::vector<vec2> UVs;
	std::vector<vec3> normals;
	std::vector<GLuint> indPos;
	std::vector<GLuint> indUV;
	std::vector<GLuint> indNor;

	if (stream.good() == false)
	{
		std::cout << "Could not find file at " << path << std::endl;
		return mesh;
	}

	while (getline(stream, line))
	{
		std::vector<std::string> lineContent;
		split(line, ' ', lineContent);

		if (lineContent.size() == 0)
			continue;

		if (lineContent[0] != "#")
		{
			
			if (lineContent[0] == "mtllib")
			{
				std::string mtlFileName = lineContent.back();
				

				std::string mtlPath;
				std::vector<std::string> out;
				split(path, '/', out);
				
				for (int i = 0; i < out.size() - 1; i++)
					mtlPath.append(out[i]+"/");
				
				outTexPath = mtlPath + GetTexPath(mtlPath + mtlFileName);
			}

			if (lineContent[0] == "v")
			{
				std::vector<std::string> out;

				split(line, ' ', out);
				vec3 position;

				for (int i = 1; i < 4; i++)
					position[i - 1] = std::stof(out[i]);

				positions.push_back(position);
			}

			if (lineContent[0] == "vt")
			{
				std::vector<std::string> out;
				
				split(line, ' ', out);
				vec2 UV = vec2(std::stof(out[1]), std::stof(out[2]));

				UVs.push_back(UV);
			}

			if (lineContent[0] == "vn")
			{
				std::vector<std::string> out;

				split(line, ' ', out);
				vec3 normal;

				for (int i = 1; i < 4; i++)
					normal[i - 1] = std::stof(out[i]);

				normals.push_back(normal);
			}

			if (lineContent[0] == "f")
			{
				std::vector<std::string> out;

				split(line, ' ', out);
				
				for (int i = 1; i < 4; i++)
				{
					std::vector<std::string> out1; //splits indicies
					split(out[i], '/', out1);
					indPos.push_back((GLuint) std::stoi(out1[0]) - 1);
					indUV.push_back( (GLuint) std::stoi(out1[1]) - 1);
					indNor.push_back((GLuint) std::stoi(out1[2]) - 1);
				}
			}
		}
	}

	std::vector<vertex> vertices;
	vertices.resize(indPos.size());

	for (int i = 0; i < indPos.size(); ++i)
	{
		vertices[i].position = positions[indPos[i]];
		vertices[i].UV = UVs[indUV[i]];
		vertices[i].normal = normals[indNor[i]];
	}

	bool found = false;
	for (int i = 0; i < indPos.size(); i++)
	{
		found = false;
		for (int j = 0; j < mesh.primitives[0].vertices.size(); j++)
		{
			if (vertices[i] == mesh.primitives[0].vertices[j])
			{
				mesh.ind.push_back(j);
				found = true;
			}
		}
		if (!found)
		{
			mesh.primitives[0].vertices.push_back(vertices[i]);
			mesh.ind.push_back(mesh.primitives[0].vertices.size() - 1);
		}
	}

	return mesh;
}

void MeshResource::Upload()
{
	/*////   Setup vbo     ////*/
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	
	


	// Upload vertex data

	for (int i = 0; i < this->primitives.size(); i++)
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * this->primitives[i].vertices.size(), this->primitives[i].vertices.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, position));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, UV));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, normal));
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, tangent));
	}


	/*////   Setup ibo     ////*/

	glGenBuffers(1, &this->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->ind.size() * sizeof(GLuint), this->ind.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//void MeshResource::UploadGLTF(GLTFinfo info)
//{
//	for (int i = 0; i < this->primitives.size(); i++)
//	{
//		this->primitives[i].vertices = info.primitives[i].vertices;
//		this->ind = info.indices;
//
//		this->primitives[i].material.ambient = vec3(1, 1, 1);
//		this->primitives[i].material.diffuse = vec3(1, 1, 1);
//		this->primitives[i].material.specular = vec3(1, 1, 1);
//		this->primitives[i].material.texture = std::make_shared<TextureResource>();
//		for (int j = 0; j < info.imageInfos.size(); j++)
//		{
//			if (!info.imageInfos[j].isEmbedded)
//			{
//				int index = info.imageInfos[j].type;
//
//				if (index >= 0)
//					this->primitives[i].material.texture->LoadFromFile(info.imageInfos[j].FilePath.c_str(), index);
//			}
//		}
//	}
//	Upload();
//}

void MeshResource::Bind()
{
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
}
