#pragma once
#include "core/math/mat4.h"
#include "../Resource/ShaderResource.h"
#include <string>
#include "GLFW/glfw3.h"

class Sun
{
public:
	vec3 color;
	vec3 direction;
	float intensity;

	Sun();
	Sun(vec3 color, vec3 direction, float intensity);
	void Update(ShaderResource shader);
	void Disable(ShaderResource shader);
};