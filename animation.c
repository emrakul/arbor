#include "animation.h"

bool trasition22(Vector2* from, const Vector2* to, unsigned long time) 
{
    static int timer = 0;
    timer++;
    double fraction = timer/time;
    *from = Vector2Lerp(*from, *to, fraction);
    if (fraction > 1.f) {
        return true;
    }
    else {
        return false;
    }

}