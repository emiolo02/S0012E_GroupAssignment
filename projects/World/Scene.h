#pragma once

#include "../Gameobject/GameObj.h"

//Singleton
class Scene
{
	static Scene instance; //declare 
	std::vector<GameObj*> gmObjPlaceholder; //GameOBJ Placeholder //Keep track of all the object in the game

	Scene() {}
	~Scene() {}

public:
	static Scene& Get() { return instance; }
	std::vector<GameObj*> GetGMVec() { return gmObjPlaceholder; }
};

Scene Scene::instance; //Define the instance

//only store all the gameobject in the world (list)
//NOTE: might need reference to the camera
// 1- constructor (take in a setup scene coordinates)