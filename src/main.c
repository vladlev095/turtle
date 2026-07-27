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
    const int screenWidth = 1200;
    const int screenHeight = 675;
    int currentFps = 60;
    float rotation = 0.0f;
    const float circleRadius = 5.0f;

    InitWindow(screenWidth, screenHeight, "raylib task - turtle");

    // The canvas to draw lines on
    RenderTexture canvas = LoadRenderTexture(screenWidth, screenHeight);

    Vector2 turtlePos = { 400, 250 };
    Vector2 prevTurtlePos = turtlePos; 

    //for the grid
    Camera2D camera = { 0 }; 
    camera.zoom = 1.0f;

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D turtleTex = LoadTexture("resources/turtlebwsm.png");

    int frameWidth = turtleTex.width;
    int frameHeight = turtleTex.height;

    // Source rectangle (part of the texture to use for drawing)
    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };

    // Destination rectangle (screen rectangle where drawing part of texture)
    Rectangle destRec = { turtlePos.x, turtlePos.y, (float)frameWidth, (float)frameHeight };

    BeginTextureMode(canvas);
        ClearBackground(RAYWHITE);
    EndTextureMode();

    SetTargetFPS(currentFps);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {   
        // bool isMoved = false;
        // if (IsKeyPressed(KEY_RIGHT)) turtlePos.x+=25, rotation = 90.0f, isMoved = true;
        // if (IsKeyPressed(KEY_LEFT)) turtlePos.x-=25, rotation = 270.0f, isMoved = true;
        // if (IsKeyPressed(KEY_UP)) turtlePos.y-=25, rotation = 0.0f, isMoved = true;
        // if (IsKeyPressed(KEY_DOWN)) turtlePos.y+=25, rotation = 180.0f, isMoved = true;
        
        // BeginTextureMode(canvas);
        //     if (isMoved) {
        //         DrawLineEx(prevTurtlePos, turtlePos, 2.0f, GREEN);
        //         prevTurtlePos.x = turtlePos.x;
        //         prevTurtlePos.y = turtlePos.y;
        //     }
        // EndTextureMode();

        for(int i = 0; i < 4; i++) {
            turtlePos.y -= 25;
            rotation = 90.0f;
            BeginTextureMode(canvas);
                DrawLineEx(prevTurtlePos, turtlePos, 2.0f, GREEN);
                prevTurtlePos.x = turtlePos.x;
                prevTurtlePos.y = turtlePos.y;
            EndTextureMode();
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            // Draw the render texture to the screen, flipped vertically to make it appear top-side up
            DrawTextureRec(canvas.texture, (Rectangle){ 0.0f, 0.0f, (float)canvas.texture.width,(float)-canvas.texture.height }, Vector2Zero(), WHITE);

            BeginMode2D(camera);
                // Draw the 3d grid, rotated 90 degrees and centered around 0,0
                rlPushMatrix();
                    rlTranslatef(0, 25*50, 0);
                    rlRotatef(90, 1, 0, 0);
                    DrawGrid(100, 25);
                rlPopMatrix();

            Vector2 origin = { turtleTex.width/2, turtleTex.height/2 };
            destRec.x = turtlePos.x;
            destRec.y = turtlePos.y;

            DrawTexturePro(turtleTex, sourceRec, destRec, origin, rotation, WHITE);
            DrawCircleV(turtlePos, circleRadius, GRAY);

            // Draw mouse reference
            DrawCircleV(GetMousePosition(), 4, DARKGRAY);
            DrawTextEx(GetFontDefault(), TextFormat("[%i, %i]", GetMouseX(), GetMouseY()),
            Vector2Add(GetMousePosition(), (Vector2){ -44, -24 }), 20, 2, BLACK);

            // printf("isMoved = %d, prevX = %d, prevY = %d, x = %d, y = %d\n", isMoved, prevX, prevY, x, y);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(turtleTex);
    UnloadRenderTexture(canvas);    // Unload the canvas render texture
    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}