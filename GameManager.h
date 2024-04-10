#pragma once

#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

class GameManager
{
public:
	void Init();
	void Update();
	void Draw();

	bool Collision(Rectangle a, Rectangle b);

private:
	//Variable
	Ball ball {};
	Paddle paddle {};

	//Brick Wall
	static const int maxBrickRows = 14;
	static const int maxBrickColumns = 8;
	Brick bricks[maxBrickRows][maxBrickColumns];
	int startRowBricks = 5;
};

