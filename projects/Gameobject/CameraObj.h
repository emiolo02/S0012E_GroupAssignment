#pragma once
#include "GameObj.h"
#include "../Component/CameraComponent.h"
class CameraObj : public GameObj
{
	CameraComp* c_Comp;

public:
	vec3 position;
	mat4 view , projection; 
//	vec3 upVec, rVec, direction;

	CameraObj()
	{
		
		CameraComp* temp = new CameraComp(); 
//		this->upVec = c_Comp.GetUpVec();
//		this->rVec = c_Comp.GetRightVec();
//		this->direction = c_Comp.GetDirection();
//		this->projection = c_Comp.GetProjection();
//		this->view = c_Comp.GetViewMat();
		c_Comp = temp;
		components.push_back(c_Comp);
		delete temp;
	}

	//NOTE: child need to execute parent start function

	void SetCamPos(vec3 pos)
	{
		this->position = pos;
	}

	void GetView()
	{
		this->projection = c_Comp->GetProjection();
		this->view = lookat(this->position, vec3(-2, 0, 2), c_Comp->GetUpVec());
	}

	//Follow Camera execution
};