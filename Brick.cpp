#include "Brick.h"

Brick::Brick()
{
	brickRec = { brickXPos, brickYPos, brickWidth, brickHeight };
}

void Brick::Draw()
{
	DrawRectangleRec(brickRec, WHITE);
}
