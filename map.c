#include "map.h"



#define CUBE_SIZE CLITERLAL (Vector3) {1.f, 0.1f, 1.f}



Map LoadMap(const char* location) {
    Map map;
    map.tileType = malloc(sizeof(unsigned int)*MAX_HEIGHT*MAX_WIDTH);
    
    FILE* fd = fopen(location, "r");
    unsigned int counter = 0;
    unsigned int height  = 0;
    unsigned int width   = 0;
    int c = 0;
    while (c != EOF) {
        c = fgetc(fd);
        //printf("%d %d \n", counter,  atoi(&c));
        if (c != (int)'\n') {
            width += 1;
            counter += 1;
            map.tileType[counter] = atoi(&c);
        }
        else {
            height += 1;
            map.width = width;
            width = 0;
        }
    }
    map.height = height+1;
    printf("%d %d", map.height, map.width);
    map.cubes = malloc(sizeof(Cube)*width*height);
    for (int i = 0; i < 32*32; ++i){
        Vector3 cubePosition = { i%32-16, 0, i/32-16 };
        map.cubes[i].position = cubePosition;
    }
    fclose(fd);
    return map;
}

void DrawMapTex(Map *map, Texture2D *atlas) {
    //map->height = 32;
    //map->width = 32;
    Vector3 cubeSize = {1.f, 0.1f, 1.f};
    Vector3 cubeSize2 = {1.f, 1.f, 1.f};
    
    for (unsigned j = 0; j < map->height; ++j) {
        for (unsigned i = 0; i < map->width; ++i) {
            unsigned index = j*map->width+i;
            int currentType = map->tileType[j*map->width+i];
            srand(i+j);
            Rectangle currentTile = {32*(rand()%4), 32*currentType+32*0, 32,32};
            //DrawCube(map->cubes[index].position, cubeSize2.x, cubeSize2.y, cubeSize2.z, WHITE);
            Vector3 currentPosition = map->cubes[index].position;
            if (currentType == 1) {
                currentPosition.y += 0.5f;
                DrawCubeTextureRec(*atlas, currentTile, currentPosition, cubeSize.x, cubeSize.y*10, cubeSize.z, WHITE);
            } 
            else {
                DrawCubeTextureRec(*atlas, currentTile, map->cubes[index].position, cubeSize.x, cubeSize.y, cubeSize.z, WHITE);
            }
        }
    }
}
    
void UnloadMap(Map *map) {
    free(map); 
}