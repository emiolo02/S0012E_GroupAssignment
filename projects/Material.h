#pragma once

#include "Resource/TextureResource.h"
#include "Resource/ShaderResource.h"
#include <memory>

class Material
{
public:
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	std::shared_ptr<TextureResource> texture;
	std::shared_ptr<TextureResource> normalMap;

	GLuint shader;

	virtual void Apply(GLuint program)
	{
		ShaderResource::Vector3f("material.ambient", this->ambient, program);
		ShaderResource::Vector3f("material.diffuse", this->diffuse, program);
		ShaderResource::Vector3f("material.specular", this->specular, program);
	}
};

class BlinnPhongMaterial : public Material
{
public:
	void LoadShader(GLuint program)
	{
		std::string shaderString;
		ShaderResource::ParseShader("../projects/BlinnPhong.glsl", GL_FRAGMENT_SHADER, shaderString);
		ShaderResource::CreateShader(
			shaderString,
			this->Material::shader,
			GL_FRAGMENT_SHADER,
			program
		);
	}

	void SetProperties(vec3 ambient, vec3 diffuse, vec3 specular, const char* texturePath)
	{
		this->Material::ambient = ambient;
		this->Material::diffuse = diffuse;
		this->Material::specular = specular;

		this->Material::texture.reset(new TextureResource());
		this->Material::texture->LoadFromFile(texturePath, 0);
	}

	void Apply(GLuint program)
	{
		ShaderResource::Vector3f("material.ambient" , this->Material::ambient , program);
		ShaderResource::Vector3f("material.diffuse" , this->Material::diffuse , program);
		ShaderResource::Vector3f("material.specular", this->Material::specular, program);
	}
};

class BlinnPhongNormalMaterial : public Material
{
public:
	void LoadShader(GLuint program)
	{
		std::string shaderString;
		ShaderResource::ParseShader("../projects/GLTFnormal/code/BlinnPhongNormal.glsl", GL_FRAGMENT_SHADER, shaderString);
		ShaderResource::CreateShader(
			shaderString,
			this->Material::shader,
			GL_FRAGMENT_SHADER,
			program
		);
	}

	void SetProperties(vec3 ambient, vec3 diffuse, vec3 specular, const char* texturePath, const char* normalPath)
	{
		this->Material::ambient = ambient;
		this->Material::diffuse = diffuse;
		this->Material::specular = specular;

		this->Material::texture.reset(new TextureResource());
		this->Material::texture->LoadFromFile(texturePath, 0);

		this->Material::normalMap.reset(new TextureResource());
		this->Material::normalMap->LoadFromFile(normalPath, 1);
	}

	void Apply(GLuint program)
	{
		ShaderResource::Vector3f("material.ambient", this->Material::ambient, program);
		ShaderResource::Vector3f("material.diffuse", this->Material::diffuse, program);
		ShaderResource::Vector3f("material.specular", this->Material::specular, program);
	}
};
