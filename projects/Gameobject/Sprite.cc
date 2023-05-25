#include "Sprite.h"

void
Sprite::Init(vec3 pos, std::shared_ptr<ShaderResource> shader, BlinnPhongMaterial &mat)
{
	this->screenPos = pos;

	this->renderableOBJ.SetResources(shader, 
		std::make_shared<MeshResource>(MeshResource::LoadOBJ("../assets/plane.obj")));

	textures.push_back(std::make_shared<TextureResource>("../assets/Numbers/0.png"));
	textures.push_back(std::make_shared<TextureResource>("../assets/Numbers/1.png"));
	textures.push_back(std::make_shared<TextureResource>("../assets/Numbers/2.png"));
	textures.push_back(std::make_shared<TextureResource>("../assets/Numbers/3.png"));
	textures.push_back(std::make_shared<TextureResource>("../assets/Numbers/4.png"));
	textures.push_back(std::make_shared<TextureResource>("../assets/Numbers/5.png"));
	textures.push_back(std::make_shared<TextureResource>("../assets/Numbers/6.png"));
	textures.push_back(std::make_shared<TextureResource>("../assets/Numbers/7.png"));
	textures.push_back(std::make_shared<TextureResource>("../assets/Numbers/8.png"));
	textures.push_back(std::make_shared<TextureResource>("../assets/Numbers/9.png"));



	mat.SetProperties(vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1), "../assets/Numbers/0.png");
	renderableOBJ.mesh->primitives[0].material = mat;
	renderableOBJ.mesh->Upload();
	renderableOBJ.Scale(vec3(.07, .07, .07));
	renderableOBJ.RotateZ(PI);
	Scene::Instance()->AddObj(this);
}

void
Sprite::Update(float dt)
{
	Camera cam = Scene::Instance()->GetMainCamera();
	this->position = cam.position + cam.direction + screenPos;

	renderableOBJ.Translate(this->position);
}

void 
Sprite::ChangeTexture(int index)
{
	this->renderableOBJ.mesh->primitives[0].material.texture = textures[index%10];
}