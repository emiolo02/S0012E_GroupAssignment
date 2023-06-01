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
#include "World/UserInterface.h"

#include "Light/PointLight.h"
#include "Light/Sun.h"

#include "Input/Input.h"

#include <chrono>

//std::shared_ptr<ShaderResource> mainShader;

Camera camera;

Player* p1;

MapGen mapGenerator(50, 50);

UserInterface score;

GameOverScreen gameOver;

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


		// Sun
		sun = Sun(vec3(0.3, 0.4, 0.7), normalize(vec3(1, -1, 0)), .4);
		
		// Player
		SpawnGen::Instance()->SpawnInitPlayer(vec3(25, 0.5, 25));
		p1 = SpawnGen::Instance()->GetPlayer();
		score.Init(gameOver);
		gameOver.Init(vec3(0, 0, 0));

		//Map
		mapGenerator.CreateTileMap();

		//Enemy
		SpawnGen::Instance()->SpawnInitEnemy(3);


		// Camera
		camera.position = vec3(-2, 2, -2);
		camera.view = lookat(camera.position, vec3(-2, 0, 2), camera.up);
		Scene::Instance()->SetMainCamera(&camera);

		
		ShaderResource::LinkProgram(resMan->GetShader()->program, resMan->GetShader()->vertexShader, resMan->GetMaterial().shader);
		

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

	float deltaSeconds = 0;
	vec2 inputLstick;
	vec2 inputRstick;
	bool hasShot = false;

	auto resMan = ResourceManager::Instance();
	auto gameState = Scene::Instance()->GetGameState();

	sun.Update(resMan->GetShader());
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
			inputLstick.x = -1;
		}
		if (manager->keyboard.held[Input::Key::A])
		{
			inputLstick.x = 1;
		}


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ShaderResource::Vector3f("cameraPos", camera.position, resMan->GetShader()->program);

		//if (manager->mouse.held[Input::MouseButton::right])
		//	camera.FreeFly(vec3(right, up, forward), manager->mouse.dx, manager->mouse.dy, 0.05);
		float cutoffpX = camera.viewCut.pX + camera.position.x;
		float cutoffpY = camera.viewCut.pY + camera.position.z;
		float cutoffnX = camera.viewCut.nX + camera.position.x;
		float cutoffnY = camera.viewCut.nY + camera.position.z;

		switch (*gameState)
		{
			case GameState::Active:
				p1->MoveInput(inputLstick);
				p1->AimInput(inputRstick);


				if (manager->gamepad.bump.pressed)
				{
					p1->timer = 0;
					p1->shoot = true;
					if (p1->Shoot())
						score.IncScore();
				}
				else
					p1->shoot = false;
				//p1.Update(deltaSeconds);

				if (Scene::Instance()->GetEnemyVec().size() == 0)
					SpawnGen::Instance()->SpawnNextWave();

				

				for (auto& gm : Scene::Instance()->GetGameObjVec())
				{
					gm->Update(deltaSeconds);
					float posX = gm->position.x - camera.position.x;
					float posY = gm->position.z - camera.position.z;

					if (gm->position.x > cutoffpX ||
						gm->position.z > cutoffpY ||
						gm->position.x < cutoffnX ||
						gm->position.z < cutoffnY)
						continue;

					gm->renderableOBJ.Draw(camera);
				}

				camera.Follow(p1->position, vec3(0, 4, -1), deltaSeconds);

				if (p1->isDead)
				{
					Scene::Instance()->SetGameState(GameOver);
					score.LoadHighscore();
				}
			break;
			case GameState::GameOver:
				camera.position = vec3(0, 1, 0);
				//camera.view = lookat(camera.position, vec3(0, 0, 0), vec3(0, 0, 1));
				camera.Follow(vec3(0, -1, 0), vec3(0, 2, -.1), deltaSeconds);
				gameOver.Draw(camera);
				score.DrawHighscore();

				camera.ChangePerspective(Projection::ortho);

				if (manager->gamepad.Abtn.pressed)
				{
					auto scene = Scene::Instance();

					for (auto e : scene->GetEnemyVec())
					{
						e->Destroy();
					}

					scene->ResetWave();
					SpawnGen::Instance()->ResetSpawnCount();

					p1->position = vec3(25, 0.5, 25);
					p1->isDead = false;
					camera.ChangePerspective(Projection::persp);
					score.Reset();
					gameOver.Reset();
					mapGenerator.Reset();
					*gameState = GameState::Active;
				}
			break;
		default:
			break;
		}
		
		this->window->SwapBuffers();


		auto time2 = std::chrono::steady_clock::now();
		float lastDT = deltaSeconds;
		deltaSeconds = (float)std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count() / 1000000;

		float avgDT = (deltaSeconds + lastDT) / 2;
		//std::cout << deltaSeconds << " s" << std::endl;
		std::cout << 1/avgDT << " fps" << std::endl;
#ifdef CI_TEST
		// if we're running CI, we want to return and exit the application after one frame
		// break the loop and hopefully exit gracefully
		break;
#endif
	}
}

} // namespace Game
