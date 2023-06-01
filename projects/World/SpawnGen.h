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

	void ResetSpawnCount()
	{
		e_spawnCount = 2;
	}

	void SpawnInitEnemy(int count)
	{
		e_spawnCount = count;
		auto mapCol = Scene::Instance()->GetMapColliders();
		auto mapDim = Scene::Instance()->GetMapDimensions();
		for(int i= 0; i < e_spawnCount; i++)
		{
			float denominator = float(e_spawnCount) / 2.0f;
			vec2 v0 = normalize(vec2(sin(i * PI / denominator), cos(i * PI / denominator)));
			v0 *= 7;
			vec2i vi;
			vi.x = v0.x + p_Ref->position.x;
			vi.y = v0.y + p_Ref->position.z;
			while (mapCol[vi.x + vi.y * mapDim.y])
			{
				vi.x += rand() % 3 - 1;
				vi.y += rand() % 3 - 1;
			}

			if (vi.x > mapDim.x - 2)
				vi.x = mapDim.x - 2;
			if (vi.x < 0)
				vi.x = 1;

			if (vi.y > mapDim.y - 2)
				vi.y = mapDim.y - 2;
			if (vi.y <= 0)
				vi.y = 1;
			EnemyAI* enemy = new EnemyAI(vec3(vi.x, 0.5, vi.y), p_Ref->position);
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

