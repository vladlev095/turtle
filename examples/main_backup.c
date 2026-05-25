/*******************************************************************************************
*
*   raylib project - turtle
*
*   Created with raylib 6.0
*
*   Licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
********************************************************************************************/

#include "raylib.h"

#include "rlgl.h"
#include "raymath.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib task - turtle");

    Camera2D camera = { 0 }; //for the grid?
    camera.zoom = 1.0f;

    int currentFps = 60;

    // Store the position for the circle
    Vector2 deltaCircle = { GetScreenWidth()/2, 300 }; //doesn't move when you change the screen

    // const float speed = 10.0f;
    const float circleRadius = 5.0f;

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D texture = LoadTexture("resources/turtlebwsm.png");        // Texture loading

    SetTargetFPS(currentFps);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Vector2 delta = GetMouseDelta();
        // delta = Vector2Scale(delta, -1.0f/camera.zoom);
        // camera.target = Vector2Add(camera.target, delta);

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);
                // Draw the 3d grid, rotated 90 degrees and centered around 0,0
                // just so we have something in the XY plane
                rlPushMatrix();
                    rlTranslatef(0, 25*50, 0);
                    rlRotatef(90, 1, 0, 0);
                    DrawGrid(100, 25);
                rlPopMatrix();

                // Draw a reference circle
                DrawCircle(GetScreenWidth()/2, GetScreenHeight()/2, 8, MAROON); //moves with the screen
            EndMode2D();

            DrawCircleV(deltaCircle, circleRadius, GRAY);

            DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}