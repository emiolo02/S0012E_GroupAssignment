#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "../Resource/GraphicsNode.h"
#include "../Physics/Physics.h"
#include "../World/Scene.h"
#include "../Gameobject/Camera.h"

//testing
class GameObj
{
	//FUTURE IMPROVEMENT (IF EVERYTHING CRASH)
	/*int ID; 
	std::string tagName;
	static int IDcount;*/

public:
	GraphicsNode renderableOBJ;
	vec3 position;

	GameObj() {};
	//FUTURE IMPROVEMENT (IF EVERYTHING CRASH)
	/*GameObj(std::string tag)
	{
		tagName = tag;
		ID = ++IDcount;
	}
	int GetInstanceID() { std::cout << "InstanceID: " << ID; };
	std::string GetName();*/

	void Draw(Camera cam) { renderableOBJ.Draw(cam); }

};