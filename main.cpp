#include "raylib.h"

#include "GameManager.h"

#include <iostream>
#include <string>

using namespace std;

typedef enum GameScreen { MENU, GAMEPLAY, ENDING } GameScreen;
GameScreen currentScreen;
GameManager gameManager;

Music startMusic;
Music mainMusic;
Music endMusic;

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

    InitAudioDevice();
    gameManager.Init();

    startMusic = LoadMusicStream("resources/Rising_Up.mp3");
    mainMusic = LoadMusicStream("resources/Dragon_Roost_Island.mp3");
    endMusic = LoadMusicStream("resources/Goodbye_my_Princess.mp3");

}

void Update() 
{
    switch (currentScreen)
    {
        case MENU:
        {
            StopMusicStream(endMusic);

            PlayMusicStream(startMusic);
            UpdateMusicStream(startMusic);

            if (IsKeyPressed(KEY_ENTER))
            {
                currentScreen = GAMEPLAY;
            }
        }
        break;
        case GAMEPLAY:
        {
            StopMusicStream(startMusic);
            StopMusicStream(endMusic);

            PlayMusicStream(mainMusic);
            UpdateMusicStream(mainMusic);

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
            StopMusicStream(mainMusic);

            PlayMusicStream(endMusic);
            UpdateMusicStream(endMusic);

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
            DrawText("BRICK BREAKER", (GetScreenWidth() / 2) - (MeasureText("BRICK BREAKER", 100) / 2), 350, 100, RED);
            DrawText("Press ENTER to PLAY", (GetScreenWidth() / 2) - (MeasureText("Press ENTER to PLAY", 50) / 2), 500, 50, LIGHTGRAY);
        }
        break;
        case GAMEPLAY:
        {
            DrawRectangle(0, 900, GetScreenWidth(), 100, { 255, 255, 255, 50 });
            gameManager.Draw();
        }
        break;
        case ENDING:
        {
            DrawText("GAME OVER", (GetScreenWidth() / 2) - (MeasureText("GAME OVER", 150) / 2), 100, 150, RED);

            DrawText("SCORE", (GetScreenWidth() / 2) - (MeasureText("SCORE", 100) / 2), 300, 100, ORANGE);
            DrawText(TextFormat("%i", score), (GetScreenWidth() / 2) - (MeasureText(TextFormat("%i", score), 75) / 2), 400, 75, WHITE);

            DrawText("TIME", (GetScreenWidth() / 2) - (MeasureText("TIME", 100) / 2), 530, 100, ORANGE);
            DrawText(TextFormat("%.2fs", gameTime), (GetScreenWidth() / 2) - (MeasureText(TextFormat("%.2fs", gameTime), 75) / 2), 630, 75, WHITE);


            DrawText("Press R to PLAY AGAIN", (GetScreenWidth() / 2) - (MeasureText("Press R to PLAY AGAIN", 40) / 2), 830, 40, LIGHTGRAY);
            DrawText("Or Press M to go back to MENU", (GetScreenWidth() / 2) - (MeasureText("Or Press M to go back to MENU", 40) / 2), 900, 40, LIGHTGRAY);
        }
        break;
        default: break;
    }

    EndDrawing();
}

void Unload() 
{
    CloseAudioDevice();
    CloseWindow();     
}


