#include "GameManager.h"

#include <corecrt_math.h>
#include <stdio.h>

float brickCount = 0;
bool endOfGame = false;

void GameManager::Init()
{
    ball.ballRec.x = paddle.paddleRec.x + paddle.paddleRec.width / 2;
    ball.ballRec.y = paddle.paddleRec.y - paddle.paddleRec.height - 10;

    ball.isLocked = true;

    Color colors[] { MAROON, RED, ORANGE, GOLD, DARKGREEN, LIME, DARKBLUE, BLUE, DARKPURPLE, VIOLET, BROWN, BEIGE, GRAY, LIGHTGRAY};

    float brickXPos = 0;
    float brickYPos = 0;

    if (startRowBricks < 14)
    {
        endOfGame = false;
    }
    else
    {
        endOfGame = true;
    }

    for (int row = 0; row < startRowBricks; row++)
    {
        for (int column = 0; column < 8; column++)
        {
            Brick& brick = bricks[row][column];
            brick.SetRowAndColumn(row, column);
            brick.isDestroyed = false;
            brick.brickColor = colors[row];

            brickCount++;
        }
    }
}

void GameManager::Update()
{
    ball.Update(paddle);
    paddle.Update();

    //COLLISION with paddle
    if (Collision(paddle.paddleRec, ball.ballRec))
    {
        ball.BounceOnPaddle(paddle);
    }

    int ballRow = floorf(ball.ballRec.y / Brick::brickHeight);
    int ballColumn = floorf(ball.ballRec.x / Brick::brickWidth);


    bool hasCollided = false;
    for (int offsetRow = -1; offsetRow <= 1; offsetRow++)
    {
        for (int offsetColumn = -1; offsetColumn <= 1; offsetColumn++)
        {
            if (ballRow + offsetRow < maxBrickRows && ballColumn + offsetColumn < maxBrickColumns 
                && ballRow + offsetRow >= 0 && ballColumn + offsetColumn >= 0)
            {
                Brick& brick = bricks[ballRow + offsetRow][ballColumn + offsetColumn];

                if (brick.isDestroyed)
                {
                    continue;
                }

                if (Collision(brick.brickRec, ball.ballRec))
                {
                    ball.BounceOnBrick();
                    hasCollided = true;
                    brick.isDestroyed = true;

                    brickCount--;
                    if (brickCount <= 0)
                    {
                        if (endOfGame)
                        {
                            //return end of game
                            //need to swithc to current screen ending
                        }

                        startRowBricks += 3;
                        return Init();
                    }

                    break;
                }
            }
        }

        if (hasCollided) break;
    }


    //COLLISION with bricks

}

void GameManager::Draw()
{
    ball.Draw();
    paddle.Draw();

    for (int row = 0; row <= startRowBricks; row++)
    {
        for (int column = 0; column <= 8; column++)
        {
            bricks[row][column].Draw();
        }
    }
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
