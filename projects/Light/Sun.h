#pragma once
#include "core/math/mat4.h"
#include "../Resource/ShaderResource.h"
#include "GLFW/glfw3.h"
#include <string>
#include <memory>


class Sun
{
public:
	vec3 color;
	vec3 direction;
	float intensity;

	Sun();
	Sun(vec3 color, vec3 direction, float intensity);
	void Update(std::shared_ptr<ShaderResource> shader);
	void Disable(std::shared_ptr<ShaderResource> shader);
};