#pragma once
#include "core/math/mat4.h"
enum Projection
{
	persp,
	ortho
};

class Camera
{
public:
	Camera();
	void FreeFly(vec3 input, float dMouseX, float dMouseY, float speed);
	void Orbit(float speed, float radius, float height, float time);
	void Follow(vec3 target, vec3 offset, float dt);
	void ChangePerspective(Projection proj);
	vec3 up;
	vec3 right;
	vec3 direction;

	vec3 position;
	mat4 projection;
	mat4 view;

	mat4 projView;
	
	struct ViewCutoff
	{
		float nX;
		float pX;
		float nY;
		float pY;
	};
	ViewCutoff viewCut;
private:	
	float dirx, diry;
};