#ifndef MAP_H
#define MAP_H

#include "tile.h"
#include "util.h"
#include "cube.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

#define MAX_HEIGHT 32
#define MAX_WIDTH  32
#define MAX_TYPES 8

// #define WATER   CLITERLAL (Pair){0, 0}
// #define EARTH   CLITERLAL (Pair){0, 1}

typedef struct Map {
    Rectangle tiles[MAX_TYPES];
    Cube* cubes;
    unsigned int *tileType;
    unsigned int height;
    unsigned int width;
    //short int depth[MAX_HEIGHT*MAX_WIDTH];
} Map;

Map WriteMap(const char *location);
Map LoadMap(const char *location);
Map GenerateMap();
void DrawMapTex(Map *map, Texture2D *atlas);
void UnloadMap(Map *map);


#endif