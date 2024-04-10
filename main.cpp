#include "raylib.h"

#include "GameManager.h"

#include <iostream>
#include <string>

using namespace std;

typedef enum GameScreen { MENU, GAMEPLAY, ENDING } GameScreen;
GameScreen currentScreen;
GameManager gameManager;

//Screen
int screenWidth = 1600;
int screenHeight = 1000;

//EndOfGame
bool resultVisible = false;
bool ending = false;
int score = 0;
float gameTime = 0;

//Function
void Load();
void Update();
void Draw();
void Unload();


int main()
{
    Load();

    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }

    Unload();
    return 0;
}


void Load() 
{
    InitWindow(screenWidth, screenHeight, "BRICK BREAKER");
    currentScreen = MENU;
    SetTargetFPS(60);

    gameManager.Init();
}

void Update() 
{
    switch (currentScreen)
    {
        case MENU:
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = GAMEPLAY;
            }
        }
        break;
        case GAMEPLAY:
        {
            ending = gameManager.Update();
            score = gameManager.GetScore();
            gameTime = gameManager.GetTimer();

            if (ending)
            {
                currentScreen = ENDING;
            }
        }
        break;
        case ENDING:
        {
            gameManager.ResetScore();
            gameManager.ResetTimer();

            if (IsKeyPressed(KEY_R))
            {
                currentScreen = GAMEPLAY;
            }

            if (IsKeyPressed(KEY_SEMICOLON))
            {
                currentScreen = MENU;
            }
        }
        break;
        default: break;
    }
}

void Draw() 
{
    BeginDrawing();
    ClearBackground(BLACK);

    switch (currentScreen)
    {
        case MENU:
        {
            DrawText("BRICK BREAKER", (GetScreenWidth() / 2) - (MeasureText("BRICK BREAKER", 150) / 2), 150, 150, RED);
            DrawText("Press ENTER to PLAY", (GetScreenWidth() / 2) - (MeasureText("Press ENTER to PLAY", 80) / 2), 400, 80, LIGHTGRAY);
        }
        break;
        case GAMEPLAY:
        {
            DrawRectangle(0, 900, GetScreenWidth(), 100, { 255, 255, 255, 50 });
            gameManager.Draw();

            //DrawText(to_string(score).c_str(), 600, 50, 60, BLUE);
        }
        break;
        case ENDING:
        {
            DrawText("GAME OVER", (GetScreenWidth() / 2) - (MeasureText("GAME OVER", 150) / 2), 150, 150, RED);

            DrawText("SCORE :", (GetScreenWidth() / 2) - (MeasureText("SCORE :", 100) / 2), 350, 100, ORANGE);
            DrawText(TextFormat("%i", score), (GetScreenWidth() / 2) - (MeasureText(TextFormat("%i", score), 75) / 2), 450, 75, WHITE);

            DrawText("GAME TIME :", (GetScreenWidth() / 2) - (MeasureText("GAME TIME :", 100) / 2), 550, 100, ORANGE);
            DrawText(TextFormat("%fs", gameTime), (GetScreenWidth() / 2) - (MeasureText(TextFormat("%fs", gameTime), 75) / 2), 650, 75, WHITE);


            DrawText("Press R to PLAY AGAIN", (GetScreenWidth() / 2) - (MeasureText("Press R to PLAY AGAIN", 50) / 2), 800, 50, LIGHTGRAY);
            DrawText("Or Press M to go back to MENU", (GetScreenWidth() / 2) - (MeasureText("Or Press M to go back to MENU", 50) / 2), 900, 50, LIGHTGRAY);
        }
        break;
        default: break;
    }

    EndDrawing();
}

void Unload() 
{
    CloseWindow();
}


