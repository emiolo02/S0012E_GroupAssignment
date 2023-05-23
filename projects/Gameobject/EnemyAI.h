#pragma once

//Move towards player position (update)
//Collider with environment & player

#include "GameObj.h"

class Player;

class EnemyAI : public GameObj
{

	//rotation (quaternion)
	const float speed = 1;

	std::string modelPath;
	std::string texturePath;

	//offset between the enemies (future)

public:
	//vec3 position;
	vec3* targetRef;
	Physics::CircleCollider collider;

	EnemyAI();
	EnemyAI(vec3 startPos,vec3& target);

	void Init(std::shared_ptr<ShaderResource> shader, BlinnPhongMaterial& playerMat);

	void Update(float dt) override;
	void Destroy() override; //deallocate enemy data of the selected enemy

	//void MoveTo(vec3& target, float dt);
	//Check collision

	//Initialize amount of enemy to spawn
	//Testing
	void InitEnemyList(std::shared_ptr<ShaderResource> shader, BlinnPhongMaterial& playerMat, int amount);
};
