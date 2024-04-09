#include "Paddle.h"

void Paddle::Update()
{
    if (IsKeyDown(KEY_A))
    {
        paddleRec.x -= speedPaddle;
    }
    else if (IsKeyDown(KEY_D))
    {
        paddleRec.x += speedPaddle;
    }

    if (paddleRec.x < 0)
    {
        paddleRec.x = 0;
    }
    if (paddleRec.x + paddleRec.width > GetScreenWidth())
    {
        paddleRec.x = GetScreenWidth() - paddleRec.width;
    }
}

void Paddle::Draw()
{
    DrawRectangleRec(paddleRec, WHITE);
}
