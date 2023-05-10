#include "Sun.h"

Sun::Sun()
{
	// Empty
}

Sun::Sun(vec3 color, vec3 direction, float intensity)
{
	this->color = color;
	this->direction = direction;
	this->intensity = intensity;
}

void
Sun::Update(ShaderResource shader)
{
	glUseProgram(shader.program);
	shader.Vector3f("sun.color", this->color, shader.program);
	shader.Vector3f("sun.direction", this->direction, shader.program);
	shader.uFloat("sun.intensity", this->intensity, shader.program);
}

void
Sun::Disable(ShaderResource shader)
{
	glUseProgram(shader.program);
	shader.Vector3f("sun.color", vec3(), shader.program);
	shader.Vector3f("sun.direction", vec3(), shader.program);
	shader.uFloat("sun.intensity", 0, shader.program);
}