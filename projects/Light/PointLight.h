#pragma once
#include "core/math/mat4.h"
#include "../Resource/ShaderResource.h"
#include <string>
#include "GLFW/glfw3.h"

class PointLight
{
public:
	vec3 pos;
	vec3 color;
	float intensity;

	int index;

	PointLight();
	PointLight(vec3 pos, vec3 color, float intensity, int index);
	void Update(ShaderResource shader);
	void Disable(ShaderResource shader);
};