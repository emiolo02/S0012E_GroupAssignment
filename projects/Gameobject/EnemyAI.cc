#include "EnemyAI.h"

//Create enemy at world origin
EnemyAI::EnemyAI()
{
	texturePath = "../assets/angrysmile.png";
	modelPath = "../assets/cube.obj";
}

//Create enemy at specified position
EnemyAI::EnemyAI(vec3 startPos, vec3& target)
{
	this->position = startPos;
	targetRef = &target;
	texturePath = "../assets/angrysmile.png";
	modelPath = "../assets/cube.obj";
}

//Init data for the GraphicsNode 
void EnemyAI::Init(std::shared_ptr<ShaderResource> shader, BlinnPhongMaterial& enemyMat)
{
	renderableOBJ.SetResources(shader,
		std::make_shared<MeshResource>(MeshResource::LoadOBJ(modelPath)));

	//Setup material loader
	enemyMat.SetProperties(vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1), texturePath.c_str());

	renderableOBJ.mesh->primitives[0].material = enemyMat;
	renderableOBJ.mesh->Upload();

	renderableOBJ.Translate(position);
	//Push it up to the gameobj list
	Scene::Instance()->AddObj(this);
	Scene::Instance()->AddEnemies(this);

}

void EnemyAI::Update(float dt) 
{
	vec3 dir = normalize(*targetRef - this->position);
	this->position += dir * speed * dt;

	renderableOBJ.Translate(this->position);
}

//cleaner
//void EnemyAI::MoveTo(vec3& target, float dt) 
//{
//vec3 dir = normalize(*targetRef - this->position);
//this->position += dir * speed * dt;
//
//renderableOBJ.Translate(this->position);
//}

//Init Multiple enemies
void EnemyAI::InitEnemyList(std::shared_ptr<ShaderResource> shader, BlinnPhongMaterial& enemyMat, int amount)
{
	for (int i = 0; i < amount; i++)
	{	
		EnemyAI* newEnemy = new EnemyAI(vec3(rand()%5, 0, rand()%10), *targetRef);
		newEnemy->Init(shader, enemyMat);
	}
}
