#pragma once

#include "GameObj.h"

class Player : public GameObj
{
	mat4 transform;
	//model
	std::string modelPath = "../assets/plane.obj";

	//Material
	const char* texturePath = "../assets/smile.png";
	//input Gamepad

public:

	Player() : transform(mat4())
	{
	}


	Player(vec3 pos)
	{
		renderableOBJ.Translate(pos);
	}
	void Init(std::shared_ptr<ShaderResource> shader, BlinnPhongMaterial& playerMat)
	{
		renderableOBJ.SetResources(shader,
			std::make_shared<MeshResource>(MeshResource::LoadOBJ(modelPath)));

		//Setup material
	/*	playerMat.LoadShader(shader->program);*/
		playerMat.SetProperties(vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1), texturePath);

		renderableOBJ.mesh->primitives[0].material = playerMat;
		renderableOBJ.mesh->Upload();
		sceneInstance.AddObj(this);
	}

	void Update(float dt);

	void MoveRight();
	void MoveUp();

	void Collision();
	void Shoot();
	void Draw(Camera cam) { renderableOBJ.Draw(cam); };

};