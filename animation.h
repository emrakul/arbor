#ifndef ANIMATION_H
#define ANIMATION_H

#include "raylib.h"
#include "raymath.h"



bool trasition33(Vector3 *from, const Vector3 *to, unsigned long time);
bool trasition22(Vector2 *from, const Vector2 *to, unsigned long time);
//float trasition11(float from, float to, unsigned long time);

// bool rotate332(Vector3 from, Vector3 to, Vector2 around, unsigned long time);
// bool rotate222(Vector2 from, Vector2 to, Vector2 around, unsigned long time);




#endif