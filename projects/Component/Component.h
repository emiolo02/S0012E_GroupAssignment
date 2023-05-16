#pragma once
//#include "../Gameobject/GameObj.h"
#include "core/math/mat4.h"

class Component
{
	//GameObj* gameObj; //What was this for???
	//Component() {};

public:
	virtual void Start(){}
	virtual void Update(float dt){}
};
