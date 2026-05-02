/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include "screens.h"
#include <stdlib.h>
#include <stdio.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;


//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;

    // random targets:
    for (int i = 0; i < targetCount; i++)
    {
        int target_x = rand() % GetScreenWidth();
        int target_y = rand() % GetScreenHeight();
        Vector2 target_position = {target_x, target_y};
        int target_radius = rand() % 100;
        targets[i].position = target_position;
        targets[i].radius   = target_radius;
        targets[i].hit      = false;
        targets[i].type     = TargetCircle;
        if (i == 9 || i == 19)
        {
            targets[i].color = GREEN;
        }
        else
        {
            targets[i].color = RED;
        }
    }
}


void spawn_target(); // targets and remember them in code to calculate hit distance
void target_hit(); // calc closest target being hit, remove target // save each hit in database lol, id ist uhrzeit + datum
void resultScreen(); //calc accurarcy in result screen
// TODO wrong targets which should not be clicked

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        //PlaySound(fxCoin);
        //printf("%d", GetMouseX());
        for (int i = 0; i < targetCount; i++)
        {
            if (!targets[i].hit)
            {
                bool collision = CheckCollisionPointCircle(GetMousePosition(), targets[i].position, targets[i].radius);
                if (collision)
                {
                    if (targets[i].color.a == 255
                        && targets[i].color.b == 48
                        && targets[i].color.g == 228
                        && targets[i].color.r == 0 )
                    {
                        finishScreen = 1;
                        return;
                    }
                    targets[i].hit = true;
                    targets[i].hitDistance = Vector2Distance(GetMousePosition(), targets[i].position);
                }
            }
        }
    }

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER)) //|| IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "GAMEPLAY SCREEN", pos, font.baseSize*3.0f, 4, MAROON);
    DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
    // draw targets:
    for (int i = 0; i < targetCount; i++)
    {
        if (!targets[i].hit)
        {
            if (targets[i].type == TargetCircle)
            {
                DrawCircle(targets[i].position.x, targets[i].position.y, targets[i].radius, targets[i].color);
                DrawCircle(targets[i].position.x, targets[i].position.y, 2, BLACK);
            }
        }
    }
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}
