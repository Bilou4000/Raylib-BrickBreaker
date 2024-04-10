#include "GameManager.h"

#include <corecrt_math.h>
#include <stdio.h>

float brickCount = 0;
bool endOfGame = false;

void GameManager::Init()
{
    //ball start pos
    ball.ballRec.x = paddle.paddleRec.x + paddle.paddleRec.width / 2;
    ball.ballRec.y = paddle.paddleRec.y - paddle.paddleRec.height - 10;

    ball.isLocked = true;

    //all colors available for the bricks
    Color colors[] { MAROON, RED, ORANGE, GOLD, DARKGREEN, LIME, DARKBLUE, BLUE, DARKPURPLE, VIOLET, BROWN, BEIGE, GRAY, LIGHTGRAY};

    float brickXPos = 0;
    float brickYPos = 0;

    //end of game logic
    if (startRowBricks < 14)
    {
        endOfGame = false;
    }
    else
    {
        endOfGame = true;
    }

    //update pos of every brock in row and colum
    for (int row = 0; row < startRowBricks; row++)
    {
        for (int column = 0; column < maxBrickColumns; column++)
        {
            Brick& brick = bricks[row][column];
            brick.SetRowAndColumn(row, column);
            brick.isDestroyed = false;
            brick.brickColor = colors[row];

            brickCount++;
        }
    }
}

bool GameManager::Update()
{
    ball.Update(paddle);
    paddle.Update();

    timer += GetFrameTime();

    //COLLISION with paddle
    if (Collision(paddle.paddleRec, ball.ballRec))
    {
        ball.BounceOnPaddle(paddle);
    }

    int ballRow = floorf(ball.ballRec.y / Brick::brickHeight);
    int ballColumn = floorf(ball.ballRec.x / Brick::brickWidth);

    //COLLISION with bricks
    bool hasCollided = false;
    for (int offsetRow = -1; offsetRow <= 1; offsetRow++)
    {
        for (int offsetColumn = -1; offsetColumn <= 1; offsetColumn++)
        {
            //check if ball is on same pos as brick and check the 8 around it
            if (ballRow + offsetRow < maxBrickRows && ballColumn + offsetColumn < maxBrickColumns 
                && ballRow + offsetRow >= 0 && ballColumn + offsetColumn >= 0)
            {
                Brick& brick = bricks[ballRow + offsetRow][ballColumn + offsetColumn];

                //if brick is already destroyed, pass
                if (brick.isDestroyed)
                {
                    continue;
                }

                //if brick isn't destroy, destroy it
                if (Collision(brick.brickRec, ball.ballRec))
                {
                    ball.BounceOnBrick();
                    hasCollided = true;
                    brick.isDestroyed = true;

                    score += 10;
                    brickCount--;

                    //check if every brick has been destroy
                    if (brickCount <= 0)
                    {
                        if (endOfGame)
                        {
                            EndOfGame();
                            return true;
                        }

                        startRowBricks += 3;
                        Init();
                    }

                    break;
                }
            }
        }

        if (hasCollided) break;
    }

    //Lose life when ball get out screen
    if (ball.ballRec.y + ball.ballRec.height > GetScreenHeight() + 50)
    {
        ball.ballRec.x = paddle.paddleRec.x + (paddle.paddleRec.width / 2) - (ball.ballRec.width / 2);
        ball.ballRec.y = paddle.paddleRec.y - paddle.paddleRec.height - 10;
        ball.isLocked = true;

        life--;

        if (life < 0)
        {
            EndOfGame();
            return true;
        }
    }

    return false;
}

void GameManager::Draw()
{
    ball.Draw();
    paddle.Draw();
    DrawText(TextFormat("Score : %i", score), 20, 925, 50, WHITE);

    //draw all bricks
    for (int row = 0; row <= startRowBricks; row++)
    {
        for (int column = 0; column <= 8; column++)
        {
            bricks[row][column].Draw();
        }
    }

    //draw life
    int offset = 0;
    int size = 40;
    for (int i = 0; i < life; i++)
    {
        DrawRectangle(GetScreenWidth() - size*2 - offset, 925, size, size, ball.ballColor);
        offset += size * 2;
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

void GameManager::EndOfGame()
{
    startRowBricks = startGameRow;
    life = maxLife;
    brickCount = 0;

    for (int row = 0; row < maxBrickRows; row++)
    {
        for (int column = 0; column < maxBrickColumns; column++)
        {
            Brick& brick = bricks[row][column];
            brick.isDestroyed = true;
        }
    }

    Init();
}

int GameManager::GetScore()
{
    return score;
}

float GameManager::GetTimer()
{
    return timer;
}

void GameManager::ResetTimer()
{
    timer = 0;
}

void GameManager::ResetScore()
{
    score = 0;
}


