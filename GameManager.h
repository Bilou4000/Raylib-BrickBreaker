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
	int score = 0;
	int maxLife = 3;
	int life = maxLife;
};

