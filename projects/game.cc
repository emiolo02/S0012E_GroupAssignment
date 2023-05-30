//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2022 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------

#include "config.h"
#include "game.h"

#include "Gameobject/Camera.h"
#include "Gameobject/Player.h" 
#include "Gameobject/StaticObj.h"
#include "Gameobject/MapGen.h"

#include "World/SpawnGen.h"
//Testing
#include "World/Pathfinding.h"

#include "Light/PointLight.h"
#include "Light/Sun.h"

#include "Input/Input.h"

#include <chrono>

//std::shared_ptr<ShaderResource> mainShader;

Camera camera;

Player* p1;

//MapGen mapGenerator(50, 50); changed Mapgen to singleton


std::vector<PointLight> lights;

Sun sun;

Input::InputManager* manager = manager->Instance();

using namespace Display;
namespace Game
{

//------------------------------------------------------------------------------
/**
*/
GameApp::GameApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
GameApp::~GameApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
bool
GameApp::Open()
{
	App::Open();
	this->window = new Display::Window;
	window->SetKeyPressFunction([this](int32 key, int32, int32 action, int32)
	{
        manager->HandleKeyEvent(key, action);
		if (key == GLFW_KEY_ESCAPE)
			this->window->Close();
	});

	window->SetMouseMoveFunction([this](float64 x, float64 y)
	{
			int width, height;
			window->GetSize(width, height);
			manager->HandleMousePosition(x-width/2, y-height/2);
	});

	window->SetMousePressFunction([this](int32 button, int32 action, int32)
	{
			manager->HandleMouseButton(button, action);
	});

	window->JoystickConnected([this](int jid, int action) //callback not working
	{
		if (action == GLFW_CONNECTED)
			std::cout << "Joystick Connected" << std::endl;

		else if (action == GLFW_DISCONNECTED)
			std::cout << "Joystick disconnected" << std::endl;
	});

	if (this->window->Open())
	{
		// INITIALIZE
		auto time1 = std::chrono::steady_clock::now();

		glClearColor(0.1f,0.1f,0.1f,0.1f);

		auto resMan = ResourceManager::Instance();
		resMan->Init();
		//mainShader = std::make_shared<ShaderResource>("../projects/vert.glsl");
		//normalShader = ShaderResource("../projects/GLTFnormal/code/vertNormal.glsl");

		// Light 0
		lights.push_back(PointLight(vec3(0, 0, -2), vec3(1, 0.1, 0.1), 1, 0));

		// Light 1
		lights.push_back(PointLight(vec3(0, 0, 2), vec3(0.1, 0.1, 1), 2, 1));

		// Sun
		sun = Sun(vec3(0.2, 0.3, 0.5), normalize(vec3(1, -1, 0)), .25);

		//BlinnPhongMaterial material;
		//material.LoadShader(mainShader->program);

		//Spawn Genereator
		SpawnGen::SetProperties();
		
		// Player
		SpawnGen::Instance()->SpawnInitPlayer(vec3(3, 0, 1));
		p1 = SpawnGen::Instance()->GetPlayer();

		//Enemy
		SpawnGen::Instance()->SpawnInitEnemy(3);

		//Map
		//mapGenerator.CreateTileMap();
		MapGen::Instance()->CreateTileMap(50, 50);
		Astar::Instance()->FindPath(p1->position, MapGen::Instance()->GetMapElement(100).position);
		
		// Camera
		camera.position = vec3(-2, 2, -2);
		camera.view = lookat(camera.position, vec3(-2, 0, 2), camera.up);
		Scene::Instance()->SetMainCamera(&camera);
		
		ShaderResource::LinkProgram(resMan->GetShader()->program, resMan->GetShader()->vertexShader, resMan->GetMaterial().shader);
		//for (auto& gm : Scene::Instance()->GetGameObjVec())
		//{
		//}

		printf("Vertex errors:\n");
		ShaderResource::ErrorLog(resMan->GetShader()->vertexShader);
		printf("Fragment errors:\n");
		ShaderResource::ErrorLog(resMan->GetMaterial().shader);

		auto time2 = std::chrono::steady_clock::now();
		auto deltaSeconds = (float)std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() / 1000000;
		std::cout << deltaSeconds << " s loading" << std::endl;
		return true;
	}
	return false;
}

//------------------------------------------------------------------------------
/**
*/
void
GameApp::Close()
{
	if (this->window->IsOpen())
		this->window->Close();

	Core::App::Close();
}

//------------------------------------------------------------------------------
/**
*/
void
GameApp::Run()
{
	glEnable(GL_DEPTH_TEST);
	glfwSwapInterval(0);

	bool useSun = false;
	float deltaSeconds = 0;
	vec2 inputLstick;
	vec2 inputRstick;
	bool hasShot = false;

	auto resMan = ResourceManager::Instance();

	while (this->window->IsOpen())
	{
		// Calculate dt
		auto time1 = std::chrono::steady_clock::now();
		
		//Gamepad logic
		manager->gamepad.Update();
		inputLstick = -manager->gamepad.leftStick;
		inputRstick = -manager->gamepad.rightStick;

		//Keyboard logic
		manager->BeginFrame();
		manager->mouse.dx = 0;
		manager->mouse.dy = 0;
		
		
		this->window->Update();
		if (manager->keyboard.held[Input::Key::W])
		{
			inputLstick.y = 1;
		}
		if (manager->keyboard.held[Input::Key::S])
		{
			inputLstick.y = -1;
		}
		if (manager->keyboard.held[Input::Key::D])
		{
			inputLstick.x =-1;
		}
		if (manager->keyboard.held[Input::Key::A])
		{
			inputLstick.x = 1;
		}


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (manager->keyboard.pressed[Input::Key::Return])
		{
			useSun = !useSun;
		}
		

		//if (manager->mouse.held[Input::MouseButton::right])
		//	camera.FreeFly(vec3(right, up, forward), manager->mouse.dx, manager->mouse.dy, 0.05);
		
		p1->MoveInput(inputLstick);
		p1->AimInput(inputRstick);

		if (manager->gamepad.trigger && !hasShot)
			p1->Shoot();
		hasShot = manager->gamepad.trigger;
		//p1.Update(deltaSeconds);
		
		if (Scene::Instance()->GetEnemyVec().size() == 0)
			SpawnGen::Instance()->SpawnNextWave();

		for(auto& gm : Scene::Instance()->GetGameObjVec())
		{
			gm->Update(deltaSeconds);
			gm->renderableOBJ.Draw(camera);
		}
		
		camera.Follow(p1->position, deltaSeconds);

		if (!useSun)
		{
			sun.Disable(resMan->GetShader());
			//sun.Disable(normalShader);

			for (auto light : lights)
			{
				light.pos = vec3(2*cos(glfwGetTime() + PI * light.index), .5f, 2*sin(glfwGetTime() + PI * light.index));
				light.Update(resMan->GetShader());
				//light.Update(normalShader);
			}
		}
		else
		{
			for (auto light : lights)
			{
				light.Disable(resMan->GetShader());
				//light.Disable(normalShader);
			}

			if (manager->keyboard.pressed[Input::Key::Up])
				sun.intensity++;
			if (manager->keyboard.pressed[Input::Key::Down])
				sun.intensity--;

			sun.Update(resMan->GetShader());
			//sun.Update(normalShader);
		}
		this->window->SwapBuffers();

		
		auto time2 = std::chrono::steady_clock::now();
		float lastDT = deltaSeconds;
		deltaSeconds = (float)std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count()/1000000;
		
		float avgDT = (deltaSeconds + lastDT) / 2;
		//std::cout << deltaSeconds << " s" << std::endl;
		//std::cout << 1/avgDT << " fps" << std::endl;
#ifdef CI_TEST
		// if we're running CI, we want to return and exit the application after one frame
		// break the loop and hopefully exit gracefully
		break;
#endif
	}
}

} // namespace Game
