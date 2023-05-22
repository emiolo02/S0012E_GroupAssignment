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

#ifdef DEBUG
	line.setLine(this->position, this->position+vec3(rightInput, 0, forwardInput) * speed);
	mat4 view = Scene::Instance()->GetMainCamera().view;
	mat4 proj = Scene::Instance()->GetMainCamera().projection;

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