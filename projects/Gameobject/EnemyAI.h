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

	//Kepp track of the enemyinstance to remove when get hit
	std::vector<EnemyAI> enemyList;
	//offset between the enemies (future)

public:
	vec3 position;

	EnemyAI();
	EnemyAI(vec3 startPos);
	~EnemyAI(){} //deallocate enemy data of the selected enemy

	void Init(std::shared_ptr<ShaderResource> shader, BlinnPhongMaterial& playerMat);

	void Update(vec3& target, float dt);

	void MoveTo(vec3& target, float dt);
	//Check collision

	//Initialize amount of enemy to spawn
	//Testing
	void InitAmount(int amount);
	void InitEnemyList(std::shared_ptr<ShaderResource> shader, BlinnPhongMaterial& playerMat, int amount);

	std::vector<EnemyAI> GetEnemyList() { return enemyList; }
};
