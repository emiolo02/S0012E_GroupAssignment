//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2022 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------

#include "config.h"
#include "game.h"
#include "Resource/GraphicsNode.h"
//#include "render/grid.h"
#include "Component/CameraComp.h"
#include "Light/PointLight.h"
#include "Light/Sun.h"
#include "Input/Input.h"

#include <chrono>

ShaderResource mainShader;
ShaderResource normalShader;

GraphicsNode plane;
//GraphicsNode monkey;
//GraphicsNode cube;
//GraphicsNode avocado;
//GraphicsNode helmet;
//std::vector<GraphicsNode> flight;

Camera camera;

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

	if (this->window->Open())
	{
		// INITIALIZE

		glClearColor(0.1f,0.1f,0.1f,0.1f);

		mainShader = ShaderResource("../projects/vert.glsl");
		//normalShader = ShaderResource("../projects/GLTFnormal/code/vertNormal.glsl");

		// Light 0
		lights.push_back(PointLight(vec3(0, 0, -2), vec3(1, 0.1, 0.1), 1, 0));

		// Light 1
		lights.push_back(PointLight(vec3(0, 0, 2), vec3(0.1, 0.1, 1), 2, 1));

		// Sun
		sun = Sun(vec3(1, 1, 1), vec3(1, -1, 0), 1);

		// Plane
		plane.SetResources(
			std::make_shared<ShaderResource>(mainShader),
			std::make_shared<MeshResource>(MeshResource::LoadOBJ("../assets/plane.obj")));

		//plane.shader->Bind(, "../projects/LightOBJ/code/frag.glsl");


		BlinnPhongMaterial planeMat;
		planeMat.LoadShader(mainShader.program);
		planeMat.SetProperties(vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1), "../assets/smile.png");
		
		plane.mesh->primitives[0].material = planeMat;

		plane.mesh->Upload();
		
		// Monkey
		/*
		monkey.shader = plane.shader;
		monkey.mesh.reset(new MeshResource(MeshResource::LoadOBJ("../projects/GLTFnormal/monke.mesh")));


		BlinnPhongMaterial monkeyMat;
		monkeyMat.shader = planeMat.shader;
		monkeyMat.SetProperties(vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1), "../projects/GLTFnormal/palette.png");

		monkey.mesh->material = monkeyMat;

		monkey.mesh->Upload();

		monkey.Translate(vec3(0, 0.4f, 0));
		monkey.RotateY(PI);
		monkey.RotateX(-PI / 4);

		// GLTF Cube
		cube.shader = plane.shader;
		cube.mesh.reset(new MeshResource());
		cube.mesh->primitives[0].material.shader = planeMat.shader;
		cube.mesh->UploadGLTF(GLTFinfo::Load("../projects/GLTFnormal/gltf/cube.gltf", 0));
		cube.Translate(vec3(2, 0, 2));


		// GLTF Avocado
		BlinnPhongNormalMaterial avocadoMat;
		avocadoMat.LoadShader(normalShader.program);
		avocado.shader = std::make_shared<ShaderResource>(normalShader);
		avocado.mesh.reset(new MeshResource());
		avocado.mesh->primitives[0].material = avocadoMat;
		avocado.mesh->UploadGLTF(GLTFinfo::Load("../projects/GLTFnormal/gltf/Avocado/Avocado.gltf", 0));

		avocado.Translate(vec3(-2, 0, 2));
		avocado.Scale(vec3(50, 50, 50));

		BlinnPhongNormalMaterial helmMat;
		helmMat.shader = avocadoMat.shader;
		helmet.shader = avocado.shader;
		helmet.mesh.reset(new MeshResource());
		helmet.mesh->primitives[0].material = helmMat;
		helmet.mesh->UploadGLTF(GLTFinfo::Load("../projects/GLTFnormal/gltf/DamagedHelmet/DamagedHelmet.gltf", 0));

		helmet.Translate(vec3(2, 0.5f, -2));

		BlinnPhongNormalMaterial flightMat;
		flightMat.shader = avocadoMat.shader;
		flight.resize(4);

		for (int i = 0; i < 4; i++)
		{
			flight[i].shader = avocado.shader;
			flight[i].mesh.reset(new MeshResource());
			flight[i].mesh->primitives[0].material = flightMat;
			flight[i].mesh->UploadGLTF(GLTFinfo::Load("../projects/GLTFnormal/gltf/FlightHelmet/FlightHelmet.gltf", i));
		}
		*/

		// Camera
		camera.position = vec3(-2, 2, -2);
		camera.view = lookat(camera.position, vec3(-2, 0, 2), camera.up);

		
		ShaderResource::LinkProgram(mainShader.program, mainShader.vertexShader, plane.mesh->primitives[0].material.shader);
		printf("Vertex errors:\n");
		ShaderResource::ErrorLog(mainShader.vertexShader);
		printf("Fragment errors:\n");
		ShaderResource::ErrorLog(plane.mesh->primitives[0].material.shader);

		//ShaderResource::LinkProgram(normalShader.program, normalShader.vertexShader, avocado.mesh->primitives[0].material.shader);
		//printf("Vertex errors:\n");
		//ShaderResource::ErrorLog(normalShader.vertexShader);
		//printf("Fragment errors:\n");
		//ShaderResource::ErrorLog(avocado.mesh->primitives[0].material.shader);


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

	float speed = 0.05;
	vec3 blockPos;

	bool useSun = false;

	while (this->window->IsOpen())
	{
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
			right = 1;
		}
		if (manager->keyboard.held[Input::Key::A])
		{
			right = -1;
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
			camera.FreeFly(vec3(right, up, forward), manager->mouse.dx, manager->mouse.dy, speed);
		
		if(manager->mouse.held[Input::MouseButton::left])
		{
			blockPos += vec3(-right, up, forward) * speed;
			//monkey.Translate(blockPos);
			//monkey.RotateY(manager->mouse.dx/100);
			//monkey.RotateX(manager->mouse.dy/100);
		}



		plane.Draw(camera);
		//monkey.Draw(camera);
		//cube.Draw(camera);
		//avocado.Draw(camera);
		//helmet.Draw(camera);

		//for (int i = 0; i < flight.size(); i++)
		//	flight[i].Draw(camera);

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

		int frameTime = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();
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
