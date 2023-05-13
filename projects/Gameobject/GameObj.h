#pragma once

#include <string>
#include <vector>
#include "core/math/mat4.h"

#include "../Component/Component.h"


//Base class 
class GameObj
{
	//may need to adjust this to ID 
	std::string tag = ""; //object tag name

public:
	std::vector<Component*> components; //list of components
	std::vector<GameObj*> childObj; //inherent gameObjects
	mat4 transform;
	GameObj() {};
	~GameObj() {};

	void Start()
	{
		if (components.empty())
			return;

		for (auto& comp : components)
			comp->Start();
	}
	void Update(float dt)
	{
		if (components.empty())
			return;

		for(auto& comp : components)
			comp->Update(dt);
	}
	
	template <class Type> //??? need to look at template syntax
	Component* getComponent(Type comp) 
	{
		for(auto& component : components)
		{
			if(typeid(component) == typeid(comp))
				return component;	
		}
		return NULL;
	}

	void AddComponent(Component comp)
	{
		components.push_back(&comp);
	}

	void SetTag(std::string tagname) { tag = tagname; }
};