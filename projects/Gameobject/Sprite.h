#pragma once

#include "GameObj.h"

class Sprite : public GameObj
{
	vec3 screenPos;
	std::vector<std::shared_ptr<TextureResource>> textures;
public:
	Sprite() {}
	void Init(vec3 pos, std::shared_ptr<ShaderResource> shader, BlinnPhongMaterial &mat);
	void Update(float dt) override;
	void ChangeTexture(int index);
};