#include "PointLight.h"

PointLight::PointLight()
{
	// Empty
}

PointLight::PointLight(vec3 pos, vec3 color, float intensity, int index)
{
	this->pos = pos;
	this->color = color;
	this->intensity = intensity;

	this->index = index;
}

void PointLight::Update(std::shared_ptr<ShaderResource> shader)
{
	std::string posName = "pointLights[" + std::to_string(this->index) + "].position";
	std::string colName = "pointLights[" + std::to_string(this->index) + "].color";
	std::string intName = "pointLights[" + std::to_string(this->index) + "].intensity";

	glUseProgram(shader->program);
	shader->Vector3f(posName.c_str(), this->pos, shader->program);
	shader->Vector3f(colName.c_str(), this->color, shader->program);
	shader->uFloat  (intName.c_str(), this->intensity, shader->program);
}

void 
PointLight::Disable(std::shared_ptr<ShaderResource> shader)
{
	std::string colName = "pointLights[" + std::to_string(this->index) + "].color";
	std::string intName = "pointLights[" + std::to_string(this->index) + "].intensity";

	glUseProgram(shader->program);
	shader->Vector3f(colName.c_str(), vec3(), shader->program);
	shader->uFloat(intName.c_str(), 0, shader->program);
}