#pragma once

#include "raylib.h"

class Brick
{
public:
	Brick();

	void Draw();

public:
	Rectangle brickRec;

	float brickXPos = 10;
	float brickYPos = 10;
	float brickWidth = 200;
	float brickHeight = 60;

	int rowNumber = 0;
	int columnNumber = 0;

	bool isDestroyed = false;
};

