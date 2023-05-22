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
	renderableOBJ.SetResources(shader,
		std::make_shared<MeshResource>(MeshResource::LoadOBJ(modelPath)));

	//Setup material
/*	playerMat.LoadShader(shader->program);*/
	playerMat.SetProperties(vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1), texturePath.c_str());

	renderableOBJ.mesh->primitives[0].material = playerMat;
	renderableOBJ.mesh->Upload();
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
	position += vec3(rightInput, 0, forwardInput) * speed * dt;

	renderableOBJ.Translate(position);
	vec3 aimDir = vec3(0, 0, 10);

	// TODO: Ugly ass code fix this garbage
	Physics::Ray ray = Physics::Ray(vec2(position.x, position.z), vec2(0, 10));
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

#ifdef DEBUG
	line.setLine(this->position, this->position+aimDir);
	mat4 view = Scene::Instance()->GetMainCamera().view;
	mat4 proj = Scene::Instance()->GetMainCamera().projection;

	if (isHit)
		line.setColor(vec3(1, 0, 0));
	else
		line.setColor(vec3(0, 1, 0));

	line.setMVP(proj * view);
	line.draw();
#endif // DEBUG

}

void 
Player::MoveRight(float value)
{
	rightInput = value;
}

void 
Player::MoveForward(float value)
{
	forwardInput = value;
}