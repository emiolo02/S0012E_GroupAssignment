//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2022 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------

#include "config.h"
#include "game.h"
#include "Resource/GraphicsNode.h"

#include "Gameobject/Camera.h"
#include "Gameobject/Player.h" 
#include "Gameobject/StaticObj.h"

#include "Light/PointLight.h"
#include "Light/Sun.h"

#include "Input/Input.h"

#include <chrono>

std::shared_ptr<ShaderResource> mainShader;

GraphicsNode plane;

Camera camera;

//testing
Player p1(vec3(0, 1, 0));




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

		glClearColor(0.1f,0.1f,0.1f,0.1f);

		mainShader = std::make_shared<ShaderResource>("../projects/vert.glsl");
		//normalShader = ShaderResource("../projects/GLTFnormal/code/vertNormal.glsl");

		// Light 0
		lights.push_back(PointLight(vec3(0, 0, -2), vec3(1, 0.1, 0.1), 1, 0));

		// Light 1
		lights.push_back(PointLight(vec3(0, 0, 2), vec3(0.1, 0.1, 1), 2, 1));

		// Sun
		sun = Sun(vec3(0.2, 0.3, 0.5), normalize(vec3(1, -1, 0)), .25);

		BlinnPhongMaterial material;
		material.LoadShader(mainShader->program);

		// Player
		p1.Init(mainShader, material);

		// Debug ground
		//BlinnPhongMaterial dbgMat;
		//dbgMat.LoadShader(mainShader->program);

		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				StaticObj* groundTile = new StaticObj(vec3(-x, 0, y));
				groundTile->Init(
					"../assets/Kenney/grass.obj",
					mainShader,
					material
				);
			}
		}


		// Camera
		camera.position = vec3(-2, 2, -2);
		camera.view = lookat(camera.position, vec3(-2, 0, 2), camera.up);
		
		for (auto& gm : Scene::Instance()->GetGameObjVec())
		{
			ShaderResource::LinkProgram(
				mainShader->program, 
				mainShader->vertexShader, 
				gm->renderableOBJ.mesh->primitives[0].material.shader
			);
		}

		printf("Vertex errors:\n");
		ShaderResource::ErrorLog(mainShader->vertexShader);
		printf("Fragment errors:\n");
		ShaderResource::ErrorLog(p1.renderableOBJ.mesh->primitives[0].material.shader);

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
	//glfwSwapInterval(0);

	bool useSun = false;
	float deltaSeconds = 0;

	while (this->window->IsOpen())
	{
		//test joystick
		//Gamepad logic
		manager->gamepad.Update();

		auto time1 = std::chrono::steady_clock::now();

		manager->BeginFrame();
		manager->mouse.dx = 0;
		manager->mouse.dy = 0;
		this->window->Update();
		// UPDATE

		float right = 0, up = 0, forward = 0;
		if (manager->keyboard.held[Input::Key::W])
		{
			forward = 1;
		}
		if (manager->keyboard.held[Input::Key::S])
		{
			forward = -1;
		}
		if (manager->keyboard.held[Input::Key::D])
		{
			right =-1;
		}
		if (manager->keyboard.held[Input::Key::A])
		{
			right = 1;
		}
		if (manager->keyboard.held[Input::Key::Space])
		{
			up = 1;
		}
		if (manager->keyboard.held[Input::Key::LeftShift])
		{
			up = -1;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (manager->keyboard.pressed[Input::Key::Return])
		{
			useSun = !useSun;
		}
		

		if (manager->mouse.held[Input::MouseButton::right])
			camera.FreeFly(vec3(right, up, forward), manager->mouse.dx, manager->mouse.dy, 0.05);
		

		p1.MoveForward(forward);
		p1.MoveRight(right);
		p1.Update(deltaSeconds);
		for(auto& gm : Scene::Instance()->GetGameObjVec())
		{
			gm->renderableOBJ.Draw(camera);
		}

		camera.Follow(p1.position, deltaSeconds);

		if (!useSun)
		{
			sun.Disable(mainShader);
			//sun.Disable(normalShader);

			for (auto light : lights)
			{
				light.pos = vec3(2*cos(glfwGetTime() + PI * light.index), .5f, 2*sin(glfwGetTime() + PI * light.index));
				light.Update(mainShader);
				//light.Update(normalShader);
			}
		}
		else
		{
			for (auto light : lights)
			{
				light.Disable(mainShader);
				//light.Disable(normalShader);
			}

			if (manager->keyboard.pressed[Input::Key::Up])
				sun.intensity++;
			if (manager->keyboard.pressed[Input::Key::Down])
				sun.intensity--;

			sun.Update(mainShader);
			//sun.Update(normalShader);
		}
		this->window->SwapBuffers();

		auto time2 = std::chrono::steady_clock::now();
		deltaSeconds = (float)std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count()/1000000;
		//std::cout << frameTime/1000 << " ms" << std::endl;
		//std::cout << 1000000/frameTime << " fps" << std::endl;
#ifdef CI_TEST
		// if we're running CI, we want to return and exit the application after one frame
		// break the loop and hopefully exit gracefully
		break;
#endif
	}
}

} // namespace Game
