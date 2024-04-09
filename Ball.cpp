#include "Ball.h"

void Ball::Update()
{
    ballRec.x += speedXBall;
    ballRec.y += speedYBall;

    if (ballRec.y < 0)
    {
        speedYBall = -speedYBall;
        ballRec.y = 0;
    }
    if (ballRec.x < 0)
    {
        speedXBall = -speedXBall;
        ballRec.x = 0;
    }
    if (ballRec.x + ballRec.width > GetScreenWidth())
    {
        speedXBall = -speedXBall;
        ballRec.x = GetScreenWidth() - ballRec.width;
    }

    //defeat
    if (ballRec.y + ballRec.height > GetScreenHeight())
    {
        //++leftScore;
        //PlaceBall(false);

        //if (score <= 0)
        //{
        //    textResult = "DEFEAT";
        //    currentScreen = ENDING;
        //}
    }
}

void Ball::Draw()
{
    DrawRectangleRec(ballRec, WHITE);
}

void Ball::BounceOnPaddle()
{
    speedYBall = -speedYBall;
}
