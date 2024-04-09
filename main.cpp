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
int screenHeight = 900;

//Score
int score = 0;

//EndOfGame
string textResult;
bool resultVisible = false;

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
            gameManager.Update();
        }
        break;
        case ENDING:
        {
            if (IsKeyPressed(KEY_R))
            {
                textResult = "";
                score = 0;

                currentScreen = GAMEPLAY;
            }

            if (IsKeyPressed(KEY_SEMICOLON))
            {
                textResult = "";
                score = 0;

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
            DrawText("BRICK BREAKER", 200, 150, 150, RED);
            DrawText("Press ENTER to PLAY", 350, 400, 80, LIGHTGRAY);
        }
        break;
        case GAMEPLAY:
        {
            gameManager.Draw();

            //DrawText(to_string(score).c_str(), 600, 50, 60, BLUE);
        }
        break;
        case ENDING:
        {
            DrawText(textResult.c_str(), 680, 200, 80, LIGHTGRAY);
            DrawText("Press R to PLAY AGAIN", 350, 400, 80, LIGHTGRAY);
            DrawText("Or Press M to go back to MENU", 150, 500, 80, LIGHTGRAY);
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


