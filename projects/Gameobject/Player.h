#pragma once

#include "GameObj.h"

class Player : public GameObj
{
public:
	Player();
	Player(vec3 pos);

	void Init(std::shared_ptr<ShaderResource> shader, BlinnPhongMaterial& playerMat);

	void Update(float dt);

	void MoveRight(float value);
	void MoveForward(float value);

	void Collision();
	void Shoot();
private:
	//model
	std::string modelPath;
	//Material
	//BlinnPhongMaterial mat;
	std::string texturePath;

	Debug::Line line;
	float speed = 4;
	//input Gamepad
	float rightInput = 0.0f;
	float forwardInput = 0.0f;
};