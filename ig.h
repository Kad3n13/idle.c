#ifndef IG_H
#define IG_H

#include <stdbool.h>

typedef struct {
    int bits;
    int bitsPerClick;
    int upgraderCounts[15];
} GameState;

void InitGame(GameState *game);
void UpdateGame(GameState *game, float dt);
void DrawGameUI(GameState *game, float dt);
void Click(GameState *game);
bool BuyUpgrade(GameState *game, int upgradeIndex);
void ResetGame(GameState *game);

#endif // IG_H

