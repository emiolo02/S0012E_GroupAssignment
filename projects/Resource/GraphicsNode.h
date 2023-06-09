#pragma once
#include "ShaderResource.h"
#include "MeshResource.h"
#include "../Gameobject/Camera.h"


class GraphicsNode
{
public:
	GraphicsNode();

	std::shared_ptr<ShaderResource> shader;
	std::shared_ptr<MeshResource> mesh;
	//std::shared_ptr<TextureResource> texture;

	void SetResources(
		std::shared_ptr<ShaderResource> shader,
		std::shared_ptr<MeshResource> mesh
		/*TextureResource* texture*/);

	void Draw(Camera cam);

	void RotateX(float rad);
	void RotateY(float rad);
	void RotateZ(float rad);

	void SetRotationX(float deg);
	void SetRotationY(float deg);
	void SetRotationZ(float deg);
	void SetRotMat(const mat4& m);

	void SetModel(vec3 pos, vec3 rot, vec3 scale);

	void RotateAxis(vec3 v, float rad);

	void Translate(const vec3& v);

	void Scale(const vec3& v);
private:
	mat4 scale;
	mat4 rotation;
	mat4 translation;
	mat4 model;
};
