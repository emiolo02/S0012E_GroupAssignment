#pragma once

#include "GameObj.h"

class Sprite : public GameObj
{
protected:
	vec3 screenPos;
public:
	Sprite() {}
	virtual void Init(vec3 pos) {}
	virtual void ChangeNum(int index) {}
};

class Number : public Sprite
{
	std::vector<std::shared_ptr<TextureResource>> textures;
public:
	void Init(vec3 pos) override;
	void ChangeNum(int index) override;
	void Update(float dt) override;
};

class GameOverScreen : public Sprite
{
public:
	void Init(vec3 pos) override;
	void Reset();
};