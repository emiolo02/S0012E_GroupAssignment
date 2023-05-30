#pragma once

#include "GameObj.h"
#include "../Light/PointLight.h"

class Gun : public GameObj
{
	std::string modelPath;
	std::string texturePath;
public:
	float rotY;
	Gun();

	void Init();
	void Update(float dt) override;
	PointLight flash;
};

class Player : public GameObj
{
public:

	Player();
	Player(vec3 pos);

	void Init(std::shared_ptr<ShaderResource> shader, BlinnPhongMaterial& playerMat);

	void Update(float dt) override;

	void MoveInput(vec2 value);
	void AimInput(vec2 value);

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
	vec2 moveInput;
	vec2 aimInput;
	
	vec2i tilePos;
	vec2 predictedPosition;

	Gun* gun;
};