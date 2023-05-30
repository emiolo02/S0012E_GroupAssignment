#include "Player.h"

#define DEBUG

//Creates player at world origin
Player::Player()
{
	texturePath = "../assets/smile.png";
	modelPath = "../assets/cylinder.obj";
}

//Creates player at specified position
Player::Player(vec3 pos)
{
	position = pos;
	texturePath = "../assets/smile.png";
	modelPath = "../assets/cylinder.obj";
}

//Sets the values for the GraphicsNode
void 
Player::Init(std::shared_ptr<ShaderResource> shader, BlinnPhongMaterial& playerMat)
{
	auto manager = ResourceManager::Instance();
	manager->AddMesh(modelPath);
	manager->AddTexture(texturePath);

	renderableOBJ.SetResources(manager->GetShader(), manager->GetMesh(modelPath));

	//Setup material loader

	renderableOBJ.mesh->primitives[0].material = manager->GetMaterial();
	renderableOBJ.mesh->primitives[0].material.texture = manager->GetTexture(texturePath);

	Scene::Instance()->AddObj(this);

	this->gun = new Gun();
	gun->Init();

#ifdef DEBUG
	line = Debug::Line(vec3(), vec3());
	line.setColor(vec3(0, 1, 0));
#endif // DEBUG
}

//Runs every frame
void
Player::Update(float dt)
{
	tilePos = vec2i(this->position.x, this->position.z);

	predictedPosition = vec2(position.x, position.z) + moveInput * speed * dt;

	Collision();
	this->position = vec3(predictedPosition.x, position.y, predictedPosition.y);

	renderableOBJ.Translate(position);
	vec3 aimDir = vec3(aimInput.x, 0, aimInput.y)*10;

	gun->position = this->position + vec3(aimInput.x, 0.3, aimInput.y)*0.5;
	gun->rotY = atan2(aimInput.x, aimInput.y)*180/PI+90;

#ifdef DEBUG
	// Draw debug line

	line.setLine(this->position+vec3(0, 0.5, 0), this->position + aimDir + vec3(0, 0.5, 0));
	
	mat4 view = Scene::Instance()->GetMainCamera().view;
	mat4 proj = Scene::Instance()->GetMainCamera().projection;

	line.setMVP(proj * view);
	line.draw();
#endif // DEBUG
}

void 
Player::MoveInput(vec2 value)
{
	moveInput = normalize(value);
}

void 
Player::AimInput(vec2 value)
{
	if (length(value) > 0)
	aimInput = normalize(value);
}

void Player::Collision()
{
	auto mapDim = Scene::Instance()->GetMapDimensions();
	auto& mapCol = Scene::Instance()->GetMapColliders();
#ifdef DEBUG
	mat4 view = Scene::Instance()->GetMainCamera().view;
	mat4 proj = Scene::Instance()->GetMainCamera().projection;
	line.setMVP(proj * view);
#endif // DEBUG

	for (int x = -2; x < 2; x++)
	{
		for (int y = -2; y < 2; y++)
		{
			vec2i cell = vec2i(tilePos.x + x, tilePos.y + y);
			if (cell.x < 0 || cell.x >= mapDim.x || cell.y < 0 || cell.y >= mapDim.y)
				continue;

			if (mapCol[cell.x + cell.y * mapDim.x])
			{
				vec2 nearestPoint;
				nearestPoint.x = std::max(float(cell.x) - 0.5f, std::min(predictedPosition.x, float(cell.x) - 0.5f + 1.0f));
				nearestPoint.y = std::max(float(cell.y) - 0.5f, std::min(predictedPosition.y, float(cell.y) - 0.5f + 1.0f));

				vec2 rayToNearest = nearestPoint - predictedPosition;

#ifdef DEBUG
				line.setLine(vec3(predictedPosition.x, 0.5, predictedPosition.y), vec3(nearestPoint.x, 0.5, nearestPoint.y));
				line.draw();
#endif // DEBUG



				float overlap = 0.25 - length(rayToNearest);

				if (length(rayToNearest) == 0)
					overlap = 0;

				if (overlap > 0)
					predictedPosition = predictedPosition - normalize(rayToNearest) * overlap;
			}
		}
	}
}

void
Player::Shoot()
{
	// Use DDA algorithm to find if ray collides with wall
	vec2 rayStart = vec2(this->position.x, this->position.z);

	vec2 rayStepSize = vec2(
		sqrt(1 + (aimInput.y / aimInput.x) * (aimInput.y / aimInput.x)), 
		sqrt(1 + (aimInput.x / aimInput.y)* (aimInput.x / aimInput.y)));
	vec2 rayLength;
	vec2i mapCheck = tilePos;
	vec2i step;

	if (aimInput.x < 0)
	{
		step.x = -1;
		rayLength.x = (rayStart.x - float(mapCheck.x) + 0.5f) * rayStepSize.x;
	}
	else
	{
		step.x = 1;
		rayLength.x = (float(mapCheck.x + 1) - rayStart.x - 0.5f) * rayStepSize.x;
	}

	if (aimInput.y < 0)
	{
		step.y = -1;
		rayLength.y = (rayStart.y - float(mapCheck.y) + 0.5f) * rayStepSize.y;
	}
	else
	{
		step.y = 1;
		rayLength.y = (float(mapCheck.y + 1) - rayStart.y - 0.5f) * rayStepSize.y;
	}
	
	const float maxDist = 20.0f;
	float dist = 0.0f;
	bool hitWall = false;
	auto mapCol = Scene::Instance()->GetMapColliders();
	auto mapDim = Scene::Instance()->GetMapDimensions();

	while (!hitWall && dist < maxDist)
	{
		if (rayLength.x < rayLength.y)
		{
			mapCheck.x += step.x;
			dist = rayLength.x;
			rayLength.x += rayStepSize.x;
		}
		else
		{
			mapCheck.y += step.y;
			dist = rayLength.y;
			rayLength.y += rayStepSize.y;
		}

		if (mapCheck.x >= 0 && mapCheck.x < mapDim.x && mapCheck.y >= 0 && mapCheck.y < mapDim.y)
		if (mapCol[mapCheck.x + mapCheck.y * mapDim.y])
		{
			hitWall = true;
		}
	}

	// Test ray against enemies
	Physics::Ray ray = Physics::Ray(vec2(position.x, position.z), aimInput);
	Physics::HitResult closest;
	closest.t = dist;
	bool isHit = false;
	for (auto& col : Scene::Instance()->GetColliders())
	{
		auto hit = col->RayIntersect(ray, closest.t);
		if (hit.object != nullptr && hit.object != this)
		{
			if(hit.t < closest.t);
			closest = hit;
			isHit = true;
		}
	}
	if (isHit)
		closest.object->Destroy();
}

Gun::Gun()
{
	modelPath = "../assets/gun.obj";
	texturePath = "../assets/black.png";
	flash = PointLight();
	flash.color = vec3(1, 1, 0);
	flash.intensity = 1;
	flash.index = 2;
}

void Gun::Init()
{
	auto manager = ResourceManager::Instance();
	manager->AddMesh(modelPath);
	manager->AddTexture(texturePath);

	renderableOBJ.SetResources(manager->GetShader(), manager->GetMesh(modelPath));

	//Setup material loader

	renderableOBJ.mesh->primitives[0].material = manager->GetMaterial();
	renderableOBJ.mesh->primitives[0].material.texture = manager->GetTexture(texturePath);
	Scene::Instance()->AddObj(this);
}

void Gun::Update(float dt)
{
	flash.pos = this->position;
	flash.Update(ResourceManager::Instance()->GetShader());
	renderableOBJ.Translate(position);
	renderableOBJ.SetRotationY(rotY);
}
