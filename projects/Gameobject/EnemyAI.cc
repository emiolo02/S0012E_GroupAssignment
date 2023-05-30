#include "EnemyAI.h"
//#define DEBUG

//Create enemy at world origin
EnemyAI::EnemyAI()
{
	texturePath = "../assets/angrysmile.png";
	modelPath = "../assets/cylinder.obj";
}

//Create enemy at specified position
EnemyAI::EnemyAI(vec3 startPos, vec3& target)
{
	this->position = startPos;
	targetRef = &target;
	texturePath = "../assets/angrysmile.png";
	modelPath = "../assets/cylinder.obj";
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

	collider = Physics::CircleCollider(vec2(position.x, position.z), 0.5f, this);

	//Push it up to the gameobj list
	Scene::Instance()->AddObj(this);
	Scene::Instance()->AddEnemies(this);
	Scene::Instance()->AddCollider(&collider);

#ifdef DEBUG
	line = Debug::Line(vec3(), vec3());
	line.setColor(vec3(1, 0, 0));
#endif // DEBUG

}

void EnemyAI::Update(float dt) 
{
	vec3 dir = normalize(*targetRef - this->position);
	this->predictedPosition = vec2(this->position.x, this->position.z) + vec2(dir.x, dir.z) * speed * dt;
	tilePos = vec2i(this->position.x, this->position.z);
	Collision();

	this->position = vec3(predictedPosition.x, this->position.y, predictedPosition.y);
	collider.position = vec2(position.x, position.z);
	renderableOBJ.Translate(this->position);

#ifdef DEBUG
	Debug::DrawCircle(line, this-> position, collider.radius);
#endif // DEBUG

}

void EnemyAI::Collision()
{
	auto mapDim = Scene::Instance()->GetMapDimensions();
	auto& mapCol = Scene::Instance()->GetMapColliders();
#ifdef DEBUG
	mat4 view = Scene::Instance()->GetMainCamera().view;
	mat4 proj = Scene::Instance()->GetMainCamera().projection;
	line.setMVP(proj * view);
#endif // DEBUG

	for (int x = -2; x < 2; x++)
	{
		for (int y = -2; y < 2; y++)
		{
			vec2i cell = vec2i(tilePos.x + x, tilePos.y + y);
			if (cell.x < 0 || cell.x >= mapDim.x || cell.y < 0 || cell.y >= mapDim.y)
				continue;

			if (mapCol[cell.x + cell.y * mapDim.x])
			{
				vec2 nearestPoint;
				nearestPoint.x = std::max(float(cell.x) - 0.5f, std::min(predictedPosition.x, float(cell.x) - 0.5f + 1.0f));
				nearestPoint.y = std::max(float(cell.y) - 0.5f, std::min(predictedPosition.y, float(cell.y) - 0.5f + 1.0f));

				vec2 rayToNearest = nearestPoint - predictedPosition;

#ifdef DEBUG
				line.setLine(vec3(predictedPosition.x, 0.5, predictedPosition.y), vec3(nearestPoint.x, 0.5, nearestPoint.y));
				line.draw();
#endif // DEBUG



				float overlap = collider.radius/2 - length(rayToNearest);

				if (length(rayToNearest) == 0)
					overlap = 0;

				if (overlap > 0)
					predictedPosition = predictedPosition - normalize(rayToNearest) * overlap;
			}
		}
	}
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