#pragma once

#include "raylib.h"

class Brick
{
public:
	Brick();
	Brick(float xPos, float yPos);

	void SetRowAndColumn(int row, int column);

	void Draw();

public:
	Rectangle brickRec;
	Color brickColor = WHITE;

	int rowNumber = 0;
	int columnNumber = 0;

	bool isDestroyed = true;

public:
	static const int brickWidth = 200;
	static const int brickHeight = 50;
};

