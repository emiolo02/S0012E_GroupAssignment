#pragma once

#include "GameObj.h"

class Sprite : public GameObj
{
protected:
	vec3 screenPos;
public:
	Sprite() {}
	virtual void Init(vec3 pos, std::shared_ptr<ShaderResource> shader, BlinnPhongMaterial &mat) {}
	virtual void ChangeNum(int index) {}
};

class Number : public Sprite
{
	std::vector<std::shared_ptr<TextureResource>> textures;
public:
	void Init(vec3 pos, std::shared_ptr<ShaderResource> shader, BlinnPhongMaterial& mat) override;
	void ChangeNum(int index) override;
	void Update(float dt) override;
};

class GameOverScreen : public Sprite
{
public:
	void Init(vec3 pos, std::shared_ptr<ShaderResource> shader, BlinnPhongMaterial& mat) override;
	void Reset();
};