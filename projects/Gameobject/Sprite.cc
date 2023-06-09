#include "Sprite.h"

void
Number::Update(float dt)
{
	if (!active)
		return;

	Camera* cam = Scene::Instance()->GetMainCamera();
	this->position = cam->position + cam->direction + screenPos;

	renderableOBJ.SetModel(this->position, vec3(), scale);
}

void 
Number::ChangeNum(int index)
{
	this->renderableOBJ.mesh->primitives[0].material.texture = textures[index%10];
}

void Number::Init(vec3 pos)
{
	this->screenPos = pos;
	auto resMan = ResourceManager::Instance();
	resMan->AddMesh("../assets/plane.obj");

	this->renderableOBJ.SetResources(resMan->GetShader(), resMan->GetMesh("../assets/plane.obj"));

	for (int i = 0; i < 10; i++)
		resMan->AddTexture("../assets/Numbers/" + std::to_string(i) + ".png");
	for (int i = 0; i < 10; i++)
		textures.push_back(resMan->GetTexture("../assets/Numbers/" + std::to_string(i) + ".png"));

	renderableOBJ.mesh->primitives[0].material = resMan->GetMaterial();
	renderableOBJ.mesh->primitives[0].material.texture = textures[0];

	this->scale = vec3(-.07, .07, .07);
	renderableOBJ.RotateZ(PI);
	Scene::Instance()->AddObj(this);
}

void GameOverScreen::Init(vec3 pos)
{
	this->position = pos;
	auto resMan = ResourceManager::Instance();
	resMan->AddMesh("../assets/plane.obj");

	this->renderableOBJ.SetResources(resMan->GetShader(), resMan->GetMesh("../assets/plane.obj")); 
	
	resMan->AddTexture("../assets/GameOver.png");
	renderableOBJ.mesh->primitives[0].material = resMan->GetMaterial();
	renderableOBJ.mesh->primitives[0].material.texture = resMan->GetTexture("../assets/GameOver.png");
	renderableOBJ.SetModel(vec3(0, -1, 0), vec3(0, PI, 0), vec3(4, 1, -3));
}

void GameOverScreen::Reset()
{
}
