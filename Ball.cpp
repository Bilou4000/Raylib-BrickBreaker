#include "Ball.h"

#include <cmath>

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

void Ball::BounceOnPaddle(Rectangle paddleRec)
{
    speedYBall = -speedYBall;

    if (ballRec.x + ballRec.width / 2 > paddleRec.x + paddleRec.width / 2)
    {
        speedXBall = maxXSpeed * Distance(ballRec.x + ballRec.width / 2, ballRec.y + ballRec.height / 2,
            paddleRec.x + paddleRec.width / 2, paddleRec.y + paddleRec.height / 2) / (paddleRec.width / 2);
    }
    else
    {
        speedXBall = -maxXSpeed * Distance(ballRec.x + ballRec.width / 2, ballRec.y + ballRec.height / 2,
            paddleRec.x + paddleRec.width / 2, paddleRec.y + paddleRec.height / 2) / (paddleRec.width / 2);
    }
}

void Ball::BounceOnBrick()
{
    speedYBall = -speedYBall;
}

float Ball::Distance(float x1, float y1, float x2, float y2)
{
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

