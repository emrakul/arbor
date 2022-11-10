#include "movement.h"

void processMovement(Vector3* chelikPosition) 
{
    if(IsKeyPressed(KEY_KP_4) || IsKeyPressed(KEY_LEFT)) {
        chelikPosition->x -= 1;
        chelikPosition->z += 1;
        return;
    }
    if(IsKeyPressed(KEY_KP_8) || IsKeyPressed(KEY_UP)) {
        chelikPosition->x -= 1;
        chelikPosition->z -= 1;
        return;

    }
    if(IsKeyPressed(KEY_KP_9)) {
        chelikPosition->z -= 1;
        return;
    }
    if(IsKeyPressed(KEY_KP_6) || IsKeyPressed(KEY_RIGHT)) {
        chelikPosition->x += 1;
        chelikPosition->z -= 1;
        return;
    }
    if(IsKeyPressed(KEY_KP_3)) {
        chelikPosition->x += 1;
        return;
    }
    if(IsKeyPressed(KEY_KP_2) || IsKeyPressed(KEY_DOWN)) {
        chelikPosition->x += 1;
        chelikPosition->z += 1;
        return;
    }
    if(IsKeyPressed(KEY_KP_1)) {
        chelikPosition->z += 1;
        return;
    }
    if(IsKeyPressed(KEY_KP_7)) {
        chelikPosition->x -= 1;
        return;
    }
    if(IsKeyPressed(KEY_KP_5)) {
        return;
    }
    return;
}