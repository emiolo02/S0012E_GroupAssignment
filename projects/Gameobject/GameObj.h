#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "../Physics/Physics.h"
#include "../World/Scene.h"

//testing
class GameObj
{
	//FUTURE IMPROVEMENT (IF EVERYTHING CRASH)
	/*int ID; 
	std::string tagName;
	static int IDcount;*/

public:
	GraphicsNode renderableOBJ;
	vec3 position = vec3(0, 0, 0);
	vec3 rotation = vec3(0, 0, 0);
	vec3 scale = vec3(1, 1, 1);

	GameObj() {}
	//FUTURE IMPROVEMENT (IF EVERYTHING CRASH)
	/*GameObj(std::string tag)
	{
		tagName = tag;
		ID = ++IDcount;
	}
	int GetInstanceID() { std::cout << "InstanceID: " << ID; };
	std::string GetName();*/

	void Draw(Camera cam) { renderableOBJ.Draw(cam); }

	virtual void Update(float dt){}
	virtual void Destroy(){}
};