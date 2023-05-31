#include "config.h"
#include "render/window.h"
#include "GraphicsNode.h"

GraphicsNode::GraphicsNode()
{
	
}

void
GraphicsNode::SetResources(
	std::shared_ptr<ShaderResource> shader,
	std::shared_ptr<MeshResource> mesh)

{
	this->shader = shader;
	this->mesh = mesh;
	//this->texture.reset(texture);
}

void GraphicsNode::Draw(Camera cam)
{
	glUseProgram(this->shader->program);

	this->mesh->Bind();

	for (auto& primitive : this->mesh->primitives)
		primitive.material.Apply(this->shader->program);

	//this->model = this->rotation * this->scale;
	mat4 MVP = cam.projView * this->model;
	ShaderResource::Matrix4fv("MVP", MVP, this->shader->program);
	ShaderResource::Matrix4fv("model", this->model, this->shader->program);


	for (auto& primitive : this->mesh->primitives)
		primitive.material.texture->BindTexture();

	glDrawElements(GL_TRIANGLES, this->mesh->ind.size(), GL_UNSIGNED_INT, NULL);

	//for (auto& primitive : this->mesh->primitives)
		//primitive.material.texture->UnbindTexture();

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void
GraphicsNode::RotateX(float rad)
{
	this->rotation = this->rotation * rotationx(rad);
}

void
GraphicsNode::RotateY(float rad)
{
	this->rotation = this->rotation * rotationy(rad);
}

void
GraphicsNode::RotateZ(float rad)
{
	this->rotation = this->rotation * rotationz(rad);
}

void
GraphicsNode::SetRotationX(float deg)
{
	this->rotation = rotationx(deg*PI/180);
}

void
GraphicsNode::SetRotationY(float deg)
{
	this->rotation = rotationy(deg * PI / 180);
}

void
GraphicsNode::SetRotationZ(float deg)
{
	this->rotation = rotationz(deg * PI / 180);
}

void
GraphicsNode::SetRotMat(const mat4& m)
{
	this->rotation = m;
}

void GraphicsNode::SetModel(vec3 pos, vec3 rot, vec3 scale)
{
	// Only able to rotate along y axis
	this->model = mat4(
		vec4(scale.x * cos(rot.y), 0, -sin(rot.y) * scale.x, 0),
		vec4(0, scale.y, 0, 0),
		vec4(sin(rot.y)*scale.z, 0, scale.z * cos(rot.y), 0),
		vec4(pos.x, pos.y, pos.z, 1)) ;
}

void
GraphicsNode::RotateAxis(vec3 v, float rad)
{
	this->rotation = this->rotation * rotationaxis(v, rad);
}

void
GraphicsNode::Translate(const vec3& v)
{
	this->translation = mat4(
		vec4(1, 0, 0, 0),
		vec4(0, 1, 0, 0),
		vec4(0, 0, 1, 0),
		vec4(v.x, v.y, v.z, 1)
	);
}

void GraphicsNode::Scale(const vec3& v)
{
	this->scale = mat4(
		vec4(v.x, 0, 0, 0),
		vec4(0, v.y, 0, 0),
		vec4(0, 0, v.z, 0),
		vec4(0,   0, 0, 1)
	);
}