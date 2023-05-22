#pragma once

#include <vector>
class GameObj; //Forward declare

class Player;
class EnemyAI;

//Singleton
class Scene
{
public:
	
	static Scene* Instance() 
	{ 
		static Scene instance;
		return &instance; 
	}

	void AddObj(GameObj* gm) 
	{ 
		gameObjects.push_back(gm); 
	}

	void AddEnemies(EnemyAI* agent)
	{
		enemies.push_back(agent);
	}

	std::vector<GameObj*> GetGameObjVec()
	{
		return gameObjects;
	}

	std::vector<EnemyAI*> GetEnemyVec()
	{
		return enemies;
	}


private:
	static Scene* instance; //declare 
	std::vector<GameObj*> gameObjects; //GameOBJ Placeholder //Keep track of all the object in the game
	std::vector<EnemyAI*> enemies;
	//Player* player;
	Scene() {}
	~Scene() {}
};

//only store all the gameobject in the world (list)
//NOTE: might need reference to the camera
// 1- constructor (take in a setup scene coordinates)