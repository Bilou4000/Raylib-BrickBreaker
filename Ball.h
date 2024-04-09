#pragma once

#include "raylib.h"

class Ball
{
public:
	void Update();
	void Draw();

	void BounceOnPaddle();

public:
	Rectangle ballRec { 100, 150, 64, 64 };

private:

	int speedXBall = 6;
	int speedYBall = -6;
};

