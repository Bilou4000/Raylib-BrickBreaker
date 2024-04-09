#pragma once

#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

class GameManager
{
public:
	void Update();
	void Draw();

	bool Collision(Rectangle a, Rectangle b);

private:
	//Variable
	Ball ball {};
	Paddle paddle {};

	//Brick Wall
	Brick bricks[14][8];
	int startRowBricks = 5;
};

