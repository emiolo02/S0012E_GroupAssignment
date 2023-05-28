#pragma once
#include "core/math/mat4.h"
#include <iostream>
#include "../Gameobject/Player.h"
#include "../Gameobject/EnemyAI.h"

//singleton
class SpawnGen
{
public:

	static SpawnGen* Instance()
	{
		static SpawnGen instance;
		return &instance;
	}

	static void SetProperties() // remove
	{
		//SpawnGen::Instance()->shaderPGR = shader;
		//SpawnGen::Instance()->entity_mat = *mat; 
	}

	void SpawnInitEnemy(int count)
	{
		e_spawnCount = count;
		for(int i= 0; i < e_spawnCount; i++)
		{
			EnemyAI* enemy = new EnemyAI(vec3(rand() % 5, 0, rand() % 10), p_Ref->position);
			enemy->Init(shaderPGR, entity_mat);
		}
	}

	void SpawnNextWave()
	{
		//Spawn in next wave
		e_spawnCount += Scene::Instance()->GetWaveCount();
		SpawnInitEnemy(e_spawnCount);
		Scene::Instance()->incrementWave();
	}

	void SpawnInitPlayer(vec3 startPos)
	{
		//Init player and set starting positon
		Player* p1 = new Player(startPos);
		p1->Init(shaderPGR, entity_mat);
		p_Ref = p1;
	}
	
	Player* GetPlayer() { return p_Ref; }
	EnemyAI* GetEnemy() { return e_Ref; }

private:
	Player* p_Ref;
	EnemyAI* e_Ref;

	BlinnPhongMaterial entity_mat;
	std::shared_ptr<ShaderResource> shaderPGR;
	int e_spawnCount;
	static SpawnGen* instance;
	~SpawnGen() {};
};

