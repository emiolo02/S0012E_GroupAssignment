#pragma once
#include "../Gameobject/Sprite.h"
#include <fstream>

class UserInterface
{
	Sprite* gameOver;

	std::vector<Sprite*> sprites;

	std::vector<Sprite*> highscoreSprites0;
	std::vector<Sprite*> highscoreSprites1;
	std::vector<Sprite*> highscoreSprites2;

	int first = 0, second = 0, third = 0;
	std::vector<int> scores;
	void SetScore(int n, std::vector<Sprite*> spr);
public:
	int score = 0;

	void Init(Sprite& gameover);
	void IncScore();
	void LoadHighscore();
	void DrawHighscore();
	void Reset();
};