#include "UserInterface.h"

// This is ugly iknow

void
UserInterface::Init(Sprite& gameover)
{
	for (int i = 0; i < 3; i++)
	{
		Sprite* sprite = new Number();
		sprite->Init(vec3(-0.5 + 0.077 * i, 0 - 0.01*i, -0.5));
		sprites.push_back(sprite);
	}
	this->gameOver = gameOver;
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

void
UserInterface::SetScore(int n, std::vector<Sprite*> spr)
{
	int tmp0 = n % 10;

	int tmp1 = (n / 10) % 10;

	int tmp2 = (n / 100) % 10;

	spr[0]->ChangeNum(tmp0);
	spr[1]->ChangeNum(tmp1);
	spr[2]->ChangeNum(tmp2);
}

void 
UserInterface::LoadHighscore()
{
	std::ifstream file;
	file.open("scores.txt");
	std::string line;

	while (std::getline(file, line)) // get top 3 scores
		scores.push_back(std::stoi(line));

	for (int i : scores)
	{
		if (i > first)
		{
			third = second;
			second = first;
			first = i;
		}
		else if (i > second)
		{
			third = second;
			second = i;
		}
		else if (i > third)
			third = i;	
	}

	file.close();

	if (highscoreSprites0.size() != 3)
	{
		for (int i = 0; i < 3; i++)
		{
			Sprite* sprite = new Number();
			sprite->Init(vec3(-0.5 + 0.25 * i, 0 - 0.01 * i, -0.5) + vec3(-0.75, 0, 0.2));
			sprite->scale = vec3(-0.2, 0.2, 0.2);
			highscoreSprites0.push_back(sprite);
		}
		for (int i = 0; i < 3; i++)
		{
			Sprite* sprite = new Number();
			sprite->Init(vec3(-0.5 + 0.25 * i, 0 - 0.01 * i, -0.5) + vec3(-0.75, 0, -0.2));
			sprite->scale = vec3(-0.2, 0.2, 0.2);
			highscoreSprites1.push_back(sprite);
		}
		for (int i = 0; i < 3; i++)
		{
			Sprite* sprite = new Number();
			sprite->Init(vec3(-0.5 + 0.25 * i, 0 - 0.01 * i, -0.5) + vec3(-0.75, 0, -0.6));
			sprite->scale = vec3(-0.2, 0.2, 0.2);
			highscoreSprites2.push_back(sprite);
		}
	}
	
	for (int i = 0; i < 3; i++)
		highscoreSprites0[i]->active = true;
	for (int i = 0; i < 3; i++)
		highscoreSprites1[i]->active = true;
	for (int i = 0; i < 3; i++)
		highscoreSprites2[i]->active = true;

	for (int i = 0; i < 3; i++)
	{
		sprites[i]->scale = vec3(-0.2, 0.2, 0.2);
		sprites[i]->screenPos += vec3(0.25*i, 0, 0);
		sprites[i]->screenPos += vec3(1.5, 0, 0);
	}

	SetScore(first, highscoreSprites0);
	SetScore(second, highscoreSprites1);
	SetScore(third, highscoreSprites2);
}

void 
UserInterface::DrawHighscore()
{
	auto cam = Scene::Instance()->GetMainCamera();
	for (auto s : sprites)
	{
		s->Update(1);
		s->Draw(*cam);
	}
	for (auto s : highscoreSprites0)
	{
		s->Update(1);
		s->Draw(*cam);
	}
	for (auto s : highscoreSprites1)
	{
		s->Update(1);
		s->Draw(*cam);
	}
	for (auto s : highscoreSprites2)
	{
		s->Update(1);
		s->Draw(*cam);
	}
}

void UserInterface::Reset()
{
	if (score > 0)
	scores.push_back(score);
	
	std::ofstream file;
	file.open("scores.txt");

	for (int i : scores)
		file << std::to_string(i) + "\n";

	file.close();
	scores.resize(0);
	first = 0;
	second = 0;
	third = 0;

	for (auto s : highscoreSprites0)
	{
		s->active = false;
	}
	for (auto s : highscoreSprites1)
	{
		s->active = false;
	}
	for (auto s : highscoreSprites2)
	{
		s->active = false;
	}

	score = 0;
	for (int i = 0; i < 3; i++)
		sprites[i]->Init(vec3(-0.5 + 0.077 * i, 0 - 0.01 * i, -0.5));
}
