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
void
EnemyAI::Destroy()
{
	Scene::Instance()->DestroyObj(this);
	Scene::Instance()->DestroyEnemy(this);
	Scene::Instance()->DestroyCollider(&this->collider);
}

//Init data for the GraphicsNode 
void EnemyAI::Init(std::shared_ptr<ShaderResource> shader, BlinnPhongMaterial& enemyMat)
{
	auto manager = ResourceManager::Instance();
	manager->AddMesh(modelPath);
	manager->AddTexture(texturePath);

	renderableOBJ.SetResources(manager->GetShader(), manager->GetMesh(modelPath));

	//Setup material loader

	renderableOBJ.mesh->primitives[0].material = manager->GetMaterial();
	renderableOBJ.mesh->primitives[0].material.texture = manager->GetTexture(texturePath);

	renderableOBJ.Translate(position);

	collider = Physics::CircleCollider(vec2(position.x, position.z), 1, this);

	//Push it up to the gameobj list
	Scene::Instance()->AddObj(this);
	Scene::Instance()->AddEnemies(this);
	Scene::Instance()->AddCollider(&collider);
}

void EnemyAI::Update(float dt) 
{
	vec3 dir = normalize(*targetRef - this->position);
	this->position += dir * speed * dt;

	collider.position = vec2(position.x, position.z);

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
	initSpawnCount = amount;
	for (int i = 0; i < initSpawnCount; i++)
	{	
		EnemyAI* newEnemy = new EnemyAI(vec3(rand()%5, 0, rand()%10), *targetRef);
		newEnemy->Init(shader, enemyMat);
	}
}

void EnemyAI::SetMaterial(BlinnPhongMaterial* mat)
{
	this->material = *mat;
}

void EnemyAI::NextWave(std::shared_ptr<ShaderResource> shader)
{
	int cur_Wave = Scene::Instance()->GetWaveCount();
	initSpawnCount += cur_Wave;

	InitEnemyList(shader, material, initSpawnCount);
	
}