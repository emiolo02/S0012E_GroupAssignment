#include "StaticObj.h"

StaticObj::StaticObj()
{

}

StaticObj::StaticObj(vec3 pos)
{
	this->position = pos;
}

void StaticObj::Init(
	std::string modelPath,
	std::string texturePath,
	std::shared_ptr<ShaderResource> shader,
	BlinnPhongMaterial& mat
)
{
	renderableOBJ.SetResources(shader,
		std::make_shared<MeshResource>(MeshResource::LoadOBJ(modelPath)));

	//Setup material
	mat.SetProperties(vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1), texturePath.c_str());

	renderableOBJ.mesh->primitives[0].material = mat;
	renderableOBJ.mesh->Upload();
	renderableOBJ.Translate(position);
	Scene::Instance()->AddObj(this);
}

void StaticObj::Init(
	std::string modelPath,
	std::shared_ptr<ShaderResource> shader,
	BlinnPhongMaterial& mat
)
{
	std::string texturePath;

	renderableOBJ.SetResources(shader,
		std::make_shared<MeshResource>(MeshResource::LoadOBJ(modelPath, texturePath)));

	//Setup material
	mat.SetProperties(vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1), texturePath.c_str());

	renderableOBJ.mesh->primitives[0].material = mat;
	renderableOBJ.mesh->Upload();
	renderableOBJ.Translate(position);
	Scene::Instance()->AddObj(this);
}