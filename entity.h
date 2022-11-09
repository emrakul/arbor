#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

typedef struct Entity {
    unsigned pos_x;
    unsigned pos_y;
    Rectangle tex_rect;
} Entity;

#endif