#include "Brick.h"

Brick::Brick()
{
	brickRec = { 0, 0, brickWidth, brickHeight };
}

Brick::Brick(float xPos, float yPos)
{
	brickRec = { xPos, yPos, brickWidth, brickHeight };
}

void Brick::SetRowAndColumn(int row, int column)
{
	rowNumber = row;
	columnNumber = column;

	brickRec.x = column * brickWidth;
	brickRec.y = row * brickHeight;
}

void Brick::Draw()
{
	const float padding = 4.0f;
	if (!isDestroyed)
	{
		DrawRectangle(brickRec.x + padding, brickRec.y + padding, brickRec.width - padding * 2, brickRec.height - padding * 2, brickColor);
	}
}
