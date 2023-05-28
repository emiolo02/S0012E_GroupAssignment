#pragma once
#include "../Resource/GraphicsNode.h"
#include <unordered_map>

class ResourceManager
{
public:
	static ResourceManager* Instance()
	{
		static ResourceManager instance;
		return &instance;
	}

	void Init()
	{
		shader = std::make_shared<ShaderResource>("../projects/vert.glsl");
		material.LoadShader(shader->program);
		material.ambient = vec3(1, 1, 1);
		material.diffuse = vec3(1, 1, 1);
		material.specular = vec3(1, 1, 1);
	}

	void AddMesh(std::string path)
	{
		MeshResource meshRes = MeshResource::LoadOBJ(path);
		meshRes.Upload();
		mesh[path] = std::make_shared<MeshResource>(meshRes);
	}

	void AddMesh(std::string path, std::string& outTexPath)
	{
		if (mesh.find(path) != mesh.end())
		{
			outTexPath = meshTex[path];
			return; // Ignore if mesh already loaded
		}

		MeshResource meshRes;
		meshRes = MeshResource::LoadOBJ(path, outTexPath);
		AddTexture(outTexPath);

		meshRes.Upload();
		mesh[path] = std::make_shared<MeshResource>(meshRes);
		meshTex[path] = outTexPath;
	}

	std::shared_ptr<MeshResource> GetMesh(std::string path)
	{
		if (mesh.find(path) != mesh.end())
			return mesh[path];
	}

	void AddTexture(std::string path)
	{
		if (texture.find(path) != texture.end()) 
			return; // Ignore if texture already loaded
		material.texture = std::make_shared<TextureResource>();
		material.texture->LoadFromFile(path.c_str(), 0);
		texture[path] = material.texture;
	}

	std::shared_ptr<TextureResource> GetTexture(std::string path)
	{
		if (texture.find(path) != texture.end())
			return texture[path];
	}

	std::shared_ptr<ShaderResource> GetShader()
	{
		return shader;
	}

	BlinnPhongMaterial& GetMaterial()
	{
		return material;
	}

private:
	ResourceManager()
	{
	}

	static ResourceManager* instance;

	std::unordered_map<std::string, std::shared_ptr<MeshResource>> mesh;
	std::unordered_map<std::string, std::shared_ptr<TextureResource>> texture;
	std::unordered_map<std::string, std::string> meshTex;
	std::shared_ptr<ShaderResource> shader;
	BlinnPhongMaterial material;
};