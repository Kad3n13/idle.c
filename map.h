#ifndef MAP_H
#define MAP_H

#include "raylib.h"

typedef struct {
    Vector3 position;
    float sizeX;
    float sizeZ;
    Color color;
} Plot;

typedef struct {
    float mainAreaSize;
    float houseSize;
    Vector3 housePos;
    Plot plots[4];
} Map;

void InitMap(Map *map);
void DrawMap(const Map *map);

#endif // MAP_H

