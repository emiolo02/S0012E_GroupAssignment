#include "Player.h"

#define DEBUG

//Creates player at world origin
Player::Player()
{
	texturePath = "../assets/smile.png";
	modelPath = "../assets/cube.obj";
}

//Creates player at specified position
Player::Player(vec3 pos)
{
	position = pos;
	texturePath = "../assets/smile.png";
	modelPath = "../assets/cube.obj";
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

#ifdef DEBUG
	line = Debug::Line(vec3(), vec3());
	line.setColor(vec3(0, 1, 0));
#endif // DEBUG
}

//Runs every frame
void
Player::Update(float dt)
{
	position += vec3(moveInput.x, 0, moveInput.y) * speed * dt;

	renderableOBJ.Translate(position);
	vec3 aimDir = vec3(aimInput.x, 0, aimInput.y)*10;

#ifdef DEBUG
	// Draw debug line

	vec3 rayDir = vec3(aimInput.x, 0, aimInput.y);
	line.setLine(this->position, this->position + aimDir);
	mat4 view = Scene::Instance()->GetMainCamera().view;
	mat4 proj = Scene::Instance()->GetMainCamera().projection;


	line.setMVP(proj * view);
	line.draw();
#endif // DEBUG
}

void 
Player::MoveInput(vec2 value)
{
	moveInput = value;
}

void 
Player::AimInput(vec2 value)
{
	if (length(value) > 0)
	aimInput = normalize(value);
}

void
Player::Shoot()
{
	// TODO: Ugly ass code fix this garbage
	Physics::Ray ray = Physics::Ray(vec2(position.x, position.z), aimInput);
	Physics::HitResult hit;
	Physics::HitResult closest;
	bool isHit = false;
	for (auto& col : Scene::Instance()->GetColliders())
	{
		auto hit = col->RayIntersect(ray, closest.t);
		if (hit.object != nullptr)
		{
			//if(hit.t < closest.t);
			closest = hit;
			isHit = true;
		}
	}
	if (isHit)
		closest.object->Destroy();
}