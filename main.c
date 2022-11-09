/*******************************************************************************************
*
*   raylib [core] example - Picking in 3d mode
*
*   Example originally created with raylib 1.3, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2022 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include "movement.h"
#include "cube.h"
#include "map.h"
#include <stdlib.h>


#define MAX_FONTS   5
#define MAX_INPUT_CHARS 32


int main(void)
{
    // Initialization
    
    const int screenWidth = 1600;
    const int screenHeight = 900;      
    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d picking");      // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 5.0f, 5.0f, 5.0f }; // Camera position
    camera.target = (Vector3){ 5.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy =  12.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_ORTHOGRAPHIC;                   // Camera mode type

    //Cubes cubes = malloc(sizeof(struct Cube)*100);
    Vector3 cubeSize = { 1.0f, 0.01f, 1.0f };
    Texture2D tex = LoadTexture("./res/hekut.png");
    Texture2D king = LoadTexture("./res/vragi.png");

    Map map = LoadMap("res/maps/map03.txt");
    
    Font fonts[MAX_FONTS] = { 0 };

    fonts[0] = LoadFont("res/fonts/custom_alagard.png");
    fonts[1] = LoadFont("res/fonts/dejavu.png");
    fonts[2] = LoadFont("res/fonts/custom_mecha.png");
    fonts[3] = LoadFont("res/fonts/custom_alagard.png");
    fonts[4] = LoadFont("res/fonts/custom_jupiter_crash.png");

    Rectangle chelik   = {32*6, 32*1, 32, 32}; //YHVH
    Rectangle input = {10.f, screenHeight-100.f, 100.f, 100.f};
    
    bool mouseOnText = false;
    int letterCount = 0;
    char name[MAX_INPUT_CHARS + 1] = "\0";
    Vector3 chelikPosition = {0, 0.6, 0};
    Vector2 chelikSize = {1, 1.2};

    struct Cube lastHitCube;
    int lastHitCubeIndex = -1;
    
    Ray ray = { 0 };                    // Picking line ray

    RayCollision collision = { 0 };
    SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode
    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    unsigned int frameCounter = 0;
    unsigned int turnCounter = 0;
    bool finished = true;
    bool clicked = false;
    bool typing = false;
    //Rectangle inputBox = { 100, 180, 50, 50 };
    // Main game loop
    while (!WindowShouldClose())      // Detect window close button or ESC key
    {
        // Update
        camera.position = chelikPosition;
        if (processMovement(&chelikPosition)) turnCounter++;
        camera.target = chelikPosition;
        UpdateCamera(&camera);
        ++frameCounter;

        if (IsKeyPressed(KEY_ENTER) && !typing)
        {
            finished = false;
            clicked = true;
            typing = true;
            printf("%s\n", "START TYPING!");
        }

        if (typing)
        {
            // Set the window's cursor to the I-Beam
            printf("%s\n", "HERE!");
            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();
            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    name[letterCount] = (char)key;
                    name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                }
                key = GetCharPressed();  // Check next character in the queue
            }
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
            if (IsKeyPressed(KEY_ENTER) && !clicked)
            {
                printf("%s\n", "Stopped typing!");
                finished = true;
                clicked=false;
                typing = false;
            }
        }
        clicked = false;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (!collision.hit)
            {
                ray = GetMouseRay(GetMousePosition(), camera);
                // Check collision between ray and box
                for (int i = 0; i < map.height*map.width; i+=1) {
                    Vector3 cubePosition =  map.cubes[i].position;
                    collision = GetRayCollisionBox(ray,
                                (BoundingBox){(Vector3){ cubePosition.x - cubeSize.x/2, cubePosition.y - cubeSize.y/4, cubePosition.z - cubeSize.z/2 },
                                              (Vector3){ cubePosition.x + cubeSize.x/2, cubePosition.y + cubeSize.y/4, cubePosition.z + cubeSize.z/2 }});
                    if(collision.hit) {
                        lastHitCube.position = cubePosition;
                        lastHitCube.size = cubeSize;
                        lastHitCubeIndex = i;
                        break;
                    }
                }
            }
            else collision.hit = false;
        }
        
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode3D(camera);
            

                DrawMapTex(&map, &tex);
                if (collision.hit) {
                    //DrawCubeTextureRec(tex, wall_rec, lastHitCube.position, cubeSize.x, cubeSize.y, cubeSize.z, WHITE);
                    //BeginBlendMode(BLEND_ALPHA);
                    float mo = sin(frameCounter/4)*122+122; 
                    DrawCube(map.cubes[lastHitCubeIndex].position, cubeSize.x, cubeSize.y, cubeSize.z, BLUE);
                    DrawCube(map.cubes[lastHitCubeIndex].position, cubeSize.x, cubeSize.y + 0.1f, cubeSize.z, CLITERAL(Color){ 250, 152, 6, (int)mo });
                    //EndBlendMode();
                }
                

                DrawRay(ray, MAROON);
                DrawGrid(10, 1.0f);
                BeginBlendMode(BLEND_ALPHA);
                DrawBillboardRec(camera, king, chelik, chelikPosition, chelikSize, Fade((Color){255,255,255}, 1.0));
                EndBlendMode();

            EndMode3D();
            //Vector2 font_position = {20, 20};
            //Vector2 turn_position = {20, 240};
            //char* turnText;

            //DrawTextEx(fonts[2], "Seek BENCH", font_position, 50, 2, WHITE);
            //BeginBlendMode(BLEND_ALPHA);
            DrawRectangle(10, screenHeight-110, screenWidth-20, 100, BLACK);
            //EndBlendMode();
            DrawText(name, (int)input.x + 5, (int)input.y + 5, 20, GRAY);
            //3sprintf(turnText, "Turn: %d", turnCounter);
            //DrawTextEx(fonts[2], turnText, font_position, 50, 2, WHITE);
            //Vector2 message_position = {(screenWidth - MeasureText("SKAMEYKA SELECTED", 40)) / 2, (int)(screenHeight * 0.05f)};
            //if (collision.hit) DrawTextEx(fonts[2], "BENCH SELECTED", message_position, 50, 10, MAGENTA);
            DrawFPS(10, 10);

        EndDrawing();
        
    }

    // De-Initialization
    //UnloadMap(&map);
    UnloadTexture(tex);
    CloseWindow();        // Close window and OpenGL context
    return 0;
}
