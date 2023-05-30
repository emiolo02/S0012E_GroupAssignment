#pragma once
#include "../Gameobject/Sprite.h"


class UserInterface
{
	std::vector<Sprite*> sprites;

public:
	int score = 0;
	void Init();
	void IncScore();
};