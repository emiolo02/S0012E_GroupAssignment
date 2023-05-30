#include "UserInterface.h"

void
UserInterface::Init()
{
	auto resMan = ResourceManager::Instance();
	for (int i = 0; i < 3; i++)
	{
		Sprite* sprite = new Number();
		sprite->Init(vec3(-0.5 + 0.077 * i, 0 - 0.01*i, -0.5));
		sprites.push_back(sprite);
	}
}

void 
UserInterface::IncScore()
{
	score++;
	int tmp0 = score % 10;

	int tmp1 = (score / 10) % 10;

	int tmp2 = (score / 100) % 10;

	sprites[0]->ChangeNum(tmp0);
	sprites[1]->ChangeNum(tmp1);
	sprites[2]->ChangeNum(tmp2);
}