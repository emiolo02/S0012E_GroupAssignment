#pragma once
#include "core/math/mat4.h"


class Camera
{
public:
	Camera();
	void FreeFly(vec3 input, float dMouseX, float dMouseY, float speed);
	void Orbit(float speed, float radius, float height, float time);

	vec3 up;
	vec3 right;
	vec3 direction;

	vec3 position;
	mat4 projection;
	mat4 view;

private:
	float dirx, diry;
};