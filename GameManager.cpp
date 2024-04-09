#include "GameManager.h"

void GameManager::Update()
{
    ball.Update();
    paddle.Update();

    int brickXPos = 0;
    int brickYPos = 0;

    for (int row = 0; row <= startRowBricks; row++)
    {
        for (int column = 0; column <= 10; column++)
        {
            Brick brick {};
            brick.brickXPos = brickXPos;
            brick.brickYPos = brickYPos;


            brick.Draw();
            //bricks[brick.rowNumber][brick.columnNumber];
            //brick.brickXPos
        }
    }

    //COLLISION with paddle
    if (Collision(paddle.paddleRec, ball.ballRec))
    {
        ball.BounceOnPaddle(paddle.paddleRec);
    }

    //COLLISION with bricks
    //if (Collision(brick.brickRec, ball.ballRec))
    //{
    //    ball.BounceOnBrick();
    //}
}

void GameManager::Draw()
{
    ball.Draw();
    paddle.Draw();
    //brick.Draw();
}

bool GameManager::Collision(Rectangle a, Rectangle b)
{
    int xMinA = a.x;
    int yMinA = a.y;
    int xMaxA = a.x + a.width;
    int yMaxA = a.y + a.height;

    int xMinB = b.x;
    int yMinB = b.y;
    int xMaxB = b.x + b.width;
    int yMaxB = b.y + b.height;

    return (!(xMinB > xMaxA || yMinB > yMaxA
        || xMaxB < xMinA || yMaxB < yMinA));
}
