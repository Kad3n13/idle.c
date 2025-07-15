#include "map.h"

void InitMap(Map *map) {
    // Setup sizes
    map->mainAreaSize = 175.0f;
    map->houseSize = 5.0f;
    map->housePos = (Vector3){0.0f, map->houseSize / 2.0f, 0.0f};

    // Define plots (x,z positions; y=0 ground level)
    map->plots[0] = (Plot) {
        .position = (Vector3){-map->mainAreaSize/2 + 5.0f/2, 0.1f, -map->mainAreaSize/2 + 5.0f/2},
        .sizeX = 5.0f,
        .sizeZ = 5.0f,
        .color = (Color){200, 100, 100, 255}  // red-ish
    };
    map->plots[1] = (Plot) {
        .position = (Vector3){map->mainAreaSize/2 - 15.0f/2, 0.1f, -map->mainAreaSize/2 + 15.0f/2},
        .sizeX = 15.0f,
        .sizeZ = 15.0f,
        .color = (Color){100, 100, 200, 255}  // blue-ish
    };
    map->plots[2] = (Plot) {
        .position = (Vector3){-map->mainAreaSize/2 + 25.0f/2, 0.1f, map->mainAreaSize/2 - 25.0f/2},
        .sizeX = 25.0f,
        .sizeZ = 25.0f,
        .color = (Color){100, 200, 100, 255}  // green-ish
    };
    map->plots[3] = (Plot) {
        .position = (Vector3){map->mainAreaSize/2 - 35.0f/2, 0.1f, map->mainAreaSize/2 - 35.0f/2},
        .sizeX = 35.0f,
        .sizeZ = 35.0f,
        .color = (Color){200, 200, 100, 255}  // yellow-ish
    };
}

void DrawMap(const Map *map) {
    // Draw main ground area as a thin cube
    DrawCube((Vector3){0, 0.0f, 0}, map->mainAreaSize, 0.2f, map->mainAreaSize, (Color){100, 200, 100, 255});
    DrawCubeWires((Vector3){0, 0.0f, 0}, map->mainAreaSize, 0.2f, map->mainAreaSize, DARKGRAY);

    // Draw the house (brown cube)
    DrawCube(map->housePos, map->houseSize, map->houseSize, map->houseSize, (Color){150, 75, 0, 255});
    DrawCubeWires(map->housePos, map->houseSize, map->houseSize, map->houseSize, BLACK);

    // Draw each plot as a thin colored cube with wireframe
    for (int i = 0; i < 4; i++) {
        Plot p = map->plots[i];
        DrawCube(p.position, p.sizeX, 0.2f, p.sizeZ, p.color);
        DrawCubeWires(p.position, p.sizeX, 0.2f, p.sizeZ, BLACK);
    }
}

