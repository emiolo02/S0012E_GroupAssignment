#pragma once

#include <vector>
class GameObj; //Forward declare

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

	std::vector<GameObj*> GetGameObjVec()
	{
		return gameObjects;
	}

private:
	static Scene* instance; //declare 
	std::vector<GameObj*> gameObjects; //GameOBJ Placeholder //Keep track of all the object in the game
	Scene() {}
	~Scene() {}
};

//only store all the gameobject in the world (list)
//NOTE: might need reference to the camera
// 1- constructor (take in a setup scene coordinates)