#ifndef TILE_H
#define TILE_H

#include "raylib.h"

typedef struct Tile {
    unsigned int type;
    Rectangle placeInAtlas;
    Texture2D *atlas;
    //Element, Attributes?
} Tile;

#endif