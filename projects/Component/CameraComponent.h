#pragma once
#include "Component.h"

class CameraComp : public Component
{
	//facing direction
	vec3 upVec;
	vec3 rVec;
	vec3 direction;

	//location & vision
	vec3 position;
	mat4 projection;
	mat4 view;

	//For now
	float dirX, diry;

public:
	CameraComp() //Note: can initialize memeber using the init list 
	{
		this->projection = perspective(90 * PI / 180, 1024.0f / 768, 0.1f, 100);
		this->view = mat4();
		this->upVec = vec3(0, 1, 0);
		this->rVec = vec3(1, 0, 0);
	}

	void Start() override
	{
	}

	void Update(float dt) override{}

	//Getter & Setter
	vec3 GetUpVec() { return upVec; }
	vec3 GetRightVec() { return rVec; }
	vec3 GetDirection() { return direction; }
	mat4 GetProjection() { return projection; }
	mat4 GetViewMat() { return view; }


	void FreeFly(vec3 input, float dMouseX, float dMouseY, float speed);
};

inline void CameraComp::FreeFly(vec3 input, float dMouseX, float dMouseY, float speed)
{
	this->dirX -= dMouseX / 100;
	this->diry -= dMouseY / 100;

	// Lock y direction so it doesnt loop around
	if (this->diry > (PI / 2) - 0.1f)
		this->diry = (PI / 2) - 0.1f;
	if (this->diry < -(PI / 2) + 0.1f)
		this->diry = -(PI / 2) + 0.1f;

	this->direction = normalize(vec3(sin(dirX), tan(diry), cos(dirX)));

	//move
	this->position +=
		//forward
		this->direction * input.z * speed
		//right
		+ normalize(cross(this->direction, this->upVec)) * input.x * speed
		//up
		+ this->upVec * input.y * speed;

	this->view = lookat(this->position, this->position + this->direction, this->upVec);
}
