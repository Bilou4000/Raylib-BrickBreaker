#include "Paddle.h"

void Paddle::Update()
{
    //move paddle
    if (IsKeyDown(KEY_A))
    {
        paddleRec.x -= speedPaddle;
        direction = 0;
    }
    else if (IsKeyDown(KEY_D))
    {
        paddleRec.x += speedPaddle;
        direction = 1;
    }

    //stop paddle on the border of the screen
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
