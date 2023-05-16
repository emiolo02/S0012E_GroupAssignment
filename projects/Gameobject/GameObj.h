#pragma once

#include <string>
#include <vector>
#include "core/math/mat4.h"

#include <iostream>

//#include "../Component/Component.h"

#include "../Resource/GraphicsNode.h"
#include "../Component/CameraComp.h"
#include "../World/Scene.h"

//include all component h file here


//testing
class GameObj
{
	//FUTURE IMPROVEMENT (IF EVERYTHING CRASH)
	/*int ID; 
	std::string tagName;
	static int IDcount;*/

public:
	GraphicsNode renderableOBJ;

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