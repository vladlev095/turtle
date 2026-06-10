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

/* tasks:
1 - turn the texture 90 degrees
2 - show movement (picture drawn in frames, line is drawn dot by dot?) and slow down
3 - removing what's drawn (not necessary)
*/

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

    Camera2D camera = { 0 }; //for the grid
    camera.zoom = 1.0f;

    int currentFps = 60;

    int x = 400;
    int y = 250;
    float rotation = 0.0f;

    // const float speed = 10.0f;
    const float circleRadius = 5.0f;

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D turtle = LoadTexture("resources/turtlebwsm.png");

    int frameWidth = turtle.width;
    int frameHeight = turtle.height;

    // Source rectangle (part of the texture to use for drawing)
    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };

    // Destination rectangle (screen rectangle where drawing part of texture)
    Rectangle destRec = { screenWidth/2, screenHeight/2, (float)frameWidth, (float)frameHeight };

    Vector2 origin = { turtle.width/2, turtle.height/2 };

    SetTargetFPS(currentFps);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Vector2 delta = GetMouseDelta();
        // delta = Vector2Scale(delta, -1.0f/camera.zoom);
        // camera.target = Vector2Add(camera.target, delta);

            // Clear the canvas to the background color
        // BeginTextureMode(canvas);
        // ClearBackground(RAYWHITE);
        // EndTextureMode();
            
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

            if (IsKeyDown(KEY_RIGHT)) x+=25, rotation = 90.0f ;
            if (IsKeyDown(KEY_LEFT)) x-=25, rotation = 270.0f ;
            if (IsKeyDown(KEY_UP)) y-=25, rotation = 0.0f ;
            if (IsKeyDown(KEY_DOWN)) y+=25, rotation = 180.0f ;

            Vector2 circleCoord = { x, y };

            DrawTexturePro(turtle, sourceRec, destRec, origin, rotation, WHITE);
            DrawCircleV(circleCoord, circleRadius, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(turtle);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}