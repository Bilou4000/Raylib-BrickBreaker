#pragma once

#include "raylib.h"

#include "Paddle.h"

class Ball
{
public:
	void Update(Paddle paddle);
	void Draw();

	void BounceOnPaddle(Paddle paddle);
	void BounceOnBrick();
	float Distance(float x1, float y1, float x2, float y2);

public:
	Rectangle ballRec { 0, 0, 64, 64};
	Color ballColor = PURPLE;
	bool isLocked = true;

private:
	int speedXBall = 6;
	int speedYBall = -6;
	int maxXSpeed = 10;
};

