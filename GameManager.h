#pragma once

#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

class GameManager
{
public:
	void Init();
	bool Update();
	void Draw();

	bool Collision(Rectangle a, Rectangle b);
	void EndOfGame();

	int GetScore();
	void ResetScore();

	float GetTimer();
	void ResetTimer();

private:
	//Variable
	Ball ball {};
	Paddle paddle {};

	//Brick Wall
	static const int maxBrickRows = 14;
	static const int maxBrickColumns = 8;
	Brick bricks[maxBrickRows][maxBrickColumns];

	int startGameRow = 5;
	int startRowBricks = startGameRow;
	int maxLife = 1;
	int life = maxLife;

	int score = 0;
	float timer = 0;
};

