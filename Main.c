#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>
#include "raylib.h"
#include "raymath.h"
#include "ig.h"  // Your game logic header

#define PLAYER_HEIGHT 1.8f
#define MOVE_SPEED 5.0f
#define GRAVITY 20.0f
#define JUMP_VELOCITY 7.0f
#define FLOOR_Y 0.0f
#define PARTICLE_COUNT 20

long double totalBitsForRebirth = 0.0L;

typedef struct {
    long double rebirth_multiplier;
    int rebirths;
} RebirthSystem;

RebirthSystem rebirth = {1.0L, 0};

int screenWidth = 1024;
int screenHeight = 768;

Color cornerColors[4] = {
    (Color){220, 50, 50, 255},   // Red
    (Color){50, 220, 50, 255},   // Green
    (Color){50, 50, 220, 255},   // Blue
    (Color){220, 150, 50, 255}   // Orange
};

float pcScales[4] = {0.8f, 1.0f, 1.2f, 1.5f};

typedef struct Particle {
    float angle;
    float speed;
    float radiusX;
    float radiusY;
    Color color;
    float size;
} Particle;

Particle particles[PARTICLE_COUNT];
float bootAnimAngle = 0.0f;
bool inIdleGame = false;
bool showNumberPrompt = false;
int numberInput = 0;
bool in3DMode = true;

GameState clicker;

const char *upgradeNames[15] = {
    "Memory Module", "Array", "Cache",
    "Register", "Processor", "Bus",
    "Clock", "Core", "Thread",
    "Stack", "Heap", "Buffer",
    "Page Table", "DMA Controller", "GPU"
};

void InitParticles(void) {
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        particles[i].angle = (2 * PI / PARTICLE_COUNT) * i;
        particles[i].speed = 0.5f + 0.5f * ((float)rand() / RAND_MAX);
        particles[i].radiusX = 150 + 20 * ((float)rand() / RAND_MAX);
        particles[i].radiusY = 80 + 20 * ((float)rand() / RAND_MAX);
        particles[i].size = 4 + 2 * ((float)rand() / RAND_MAX);
        particles[i].color = (i % 2 == 0)
            ? (Color){102, 255, 102, 255}
            : (Color){170, 102, 255, 255};
    }
}

void DrawBootAnimation(float centerX, float centerY, float deltaTime) {
    bootAnimAngle += deltaTime * 0.5f;
    DrawCircleGradient(centerX, centerY, 60, Fade(WHITE, 0.3f), BLANK);

    for (int i = 0; i < PARTICLE_COUNT; i++) {
        Particle *p = &particles[i];
        p->angle += p->speed * deltaTime;
        if (p->angle > 2*PI) p->angle -= 2*PI;

        float x = centerX + p->radiusX * cosf(p->angle + bootAnimAngle);
        float y = centerY + p->radiusY * sinf(p->angle + bootAnimAngle);

        float glowAlpha = 0.5f + 0.5f * sinf(GetTime() * 5 + p->angle);
        DrawCircleV((Vector2){x, y}, p->size*3, Fade(p->color, glowAlpha*0.6f));
        DrawCircleV((Vector2){x, y}, p->size, Fade(p->color, glowAlpha));
    }

    int sides = 6;
    float radius = 90;
    Vector2 prevPoint = {0};
    for (int i = 0; i <= sides; i++) {
        float angle = bootAnimAngle + i * 2 * PI / sides;
        Vector2 point = {
            centerX + radius * cosf(angle),
            centerY + radius * sinf(angle)
        };
        if (i > 0)
            DrawLineEx(prevPoint, point, 3, (Color){170,102,255,180});
        prevPoint = point;
    }
}

void CheckAndHandleRebirth(GameState *game) {
    long double bits = (long double)game->bits;
    totalBitsForRebirth += bits;
    if (bits >= 670000.0L && IsKeyPressed(KEY_R)) {
        long double gain = log10l(bits) / 10.0L;
        if (gain < 0.1L) gain = 0.1L;
        rebirth.rebirth_multiplier += gain;
        rebirth.rebirths++;
        ResetGame(game);
    }
}

void HandleNumberPopup() {
    int key = GetKeyPressed();
    if (key >= KEY_ZERO && key <= KEY_NINE) {
        numberInput = numberInput * 10 + (key - KEY_ZERO);
    }
    if (IsKeyPressed(KEY_ENTER)) {
        showNumberPrompt = false;
        TraceLog(LOG_INFO, TextFormat("Entered number: %d", numberInput));
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
        numberInput /= 10;
    }
}

int main(void) {
    InitWindow(screenWidth, screenHeight, "4-Corner OS & Clicker Game Demo");
    SetTargetFPS(60);

    InitParticles();
    InitGame(&clicker);

    Vector3 playerPosition = {0};
    Camera3D camera = {0};
    camera.position = (Vector3){10.0f, 10.0f, 10.0f};
    camera.target = playerPosition;
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (IsKeyPressed(KEY_TAB)) in3DMode = !in3DMode;

        if (in3DMode) {
            Vector3 move = {0};
            if (IsKeyDown(KEY_W)) move.z -= 1.0f;
            if (IsKeyDown(KEY_S)) move.z += 1.0f;
            if (IsKeyDown(KEY_A)) move.x -= 1.0f;
            if (IsKeyDown(KEY_D)) move.x += 1.0f;

            float len = sqrtf(move.x*move.x + move.z*move.z);
            if (len > 0.0f) {
                move.x /= len;
                move.z /= len;
            }

            playerPosition.x += move.x * MOVE_SPEED * dt;
            playerPosition.z += move.z * MOVE_SPEED * dt;

            camera.position.x = playerPosition.x + 10.0f;
            camera.position.y = 10.0f;
            camera.position.z = playerPosition.z + 10.0f;
            camera.target = playerPosition;

            BeginDrawing();
            ClearBackground((Color){200, 200, 200, 255});
            BeginMode3D(camera);
            DrawCube(playerPosition, 1.0f, 2.0f, 1.0f, (Color){100, 100, 100, 255});
            DrawCubeWires(playerPosition, 1.0f, 2.0f, 1.0f, (Color){70, 70, 70, 255});
            EndMode3D();
            DrawText("3D Isometric Mode - Press TAB to toggle", 10, 10, 20, BLACK);
            EndDrawing();

        } else if (!inIdleGame) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("WASD to move, SPACE to jump, E to enter computer", 10, 10, 20, DARKGRAY);
            DrawGameUI(&clicker, dt);
            EndDrawing();

            if (IsKeyPressed(KEY_E)) {
                inIdleGame = true;
                showNumberPrompt = true;
                numberInput = 0;
            }

        } else {
            if (IsKeyPressed(KEY_TAB)) inIdleGame = false;

            UpdateGame(&clicker, dt);
            CheckAndHandleRebirth(&clicker);

            BeginDrawing();
            ClearBackground(BLACK);

            DrawBootAnimation(screenWidth / 2, screenHeight / 2, dt);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) Click(&clicker);

            for (int i = 0; i < 15; i++) {
                int key = (i < 9) ? (KEY_ONE + i) : (KEY_A + (i - 9));
                if (IsKeyPressed(key)) {
                    BuyUpgrade(&clicker, i);
                }
            }

            if (showNumberPrompt) {
                HandleNumberPopup();
                DrawText("Enter your ID (0-9, ENTER to confirm):", 100, 50, 20, GREEN);
                DrawText(TextFormat("%d", numberInput), 100, 80, 40, LIME);
            }

            DrawText(TextFormat("Bits: %d", clicker.bits), 20, 120, 20, LIME);
            DrawText(TextFormat("[Click] Left mouse: +%d bits", clicker.bitsPerClick), 20, 150, 20, LIGHTGRAY);
            DrawText("Buy Upgrades (keys 1-9, A-F):", 20, 180, 20, GRAY);

            for (int i = 0; i < 15; i++) {
                DrawText(TextFormat("%2d) %s: %d", i + 1, upgradeNames[i], clicker.upgraderCounts[i]),
                         20, 210 + i * 22, 16, GRAY);
            }

            DrawText("Booting OS... Press TAB to exit", screenWidth / 2 - 150, screenHeight - 50, 20, LIGHTGRAY);
            DrawText(TextFormat("Rebirths: %d | Multiplier: %.2Lf (Press R to rebirth)",
                        rebirth.rebirths, rebirth.rebirth_multiplier), 20, screenHeight - 80, 20, SKYBLUE);
            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}

