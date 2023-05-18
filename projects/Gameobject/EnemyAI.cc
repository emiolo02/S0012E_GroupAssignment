#include "EnemyAI.h"

//Create enemy at world origin
EnemyAI::EnemyAI()
{
	texturePath = "../assets/angrysmile.png";
	modelPath = "../assets/cube.obj";
}


//Create enemy at specified position
EnemyAI::EnemyAI(vec3 startPos)
{
	position = startPos;
	texturePath = "../assets/angrysmile.png";
	modelPath = "../assets/cube.obj";
}

//Upcoming feature: Create enemy at random position


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
}

void EnemyAI::Update(vec3& target, float dt)
{
	MoveTo(target, dt);
}

//can change it by getting reference to the player
void EnemyAI::MoveTo(vec3& target, float dt) 
{
	this->position = Lerp(this->position, target, dt);

	renderableOBJ.Translate(this->position);
}


//WORKING PROGRESS

void EnemyAI::InitEnemyList(std::shared_ptr<ShaderResource> shader, BlinnPhongMaterial& enemyMat, int amount)
{
	//Scuffed implementation
	//Testing phase //Everything spawns at same position
	for (int i = 1; i <= amount; ++i)
	{	
		EnemyAI* newEnemy = new EnemyAI(vec3(3*i,0,1 *i));

		renderableOBJ.SetResources(shader,
			std::make_shared<MeshResource>(MeshResource::LoadOBJ(modelPath)));

		//Setup material loader
		enemyMat.SetProperties(vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1), texturePath.c_str());

		renderableOBJ.mesh->primitives[0].material = enemyMat;
		renderableOBJ.mesh->Upload();
		
		renderableOBJ.Translate(newEnemy->position);
		//this->position = newEnemy->position;
		//Push it up to the gameobj list
		Scene::Instance()->AddObj(this);
		//delete newEnemy;
	}
}
