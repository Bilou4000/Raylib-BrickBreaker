#pragma once

#include "raylib.h"

class Paddle
{
public:
	void Update();
	void Draw();

public:
	Rectangle paddleRec { (1600 / 2) - (256 / 2), 900 - 70, 256, 55 };

private:
	int speedPaddle = 8;
};

