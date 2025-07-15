#include "ig.h"
#include <math.h>
#include <stdio.h>

static const int baseCosts[15] = {
    10, 50, 100,
    500, 1000, 2500,
    5000, 10000, 20000,
    40000, 80000, 160000,
    320000, 640000, 1280000
};

static const int bitsPerClickAdd[15] = {
    1, 2, 4,
    8, 16, 32,
    64, 128, 256,
    512, 1024, 2048,
    4096, 8192, 16384
};

// Initialize game state
void InitGame(GameState *game) {
    game->bits = 0;
    game->bitsPerClick = 1;
    for (int i = 0; i < 15; i++) {
        game->upgraderCounts[i] = 0;
    }
}

// Calculate upgrade cost (scales exponentially)
int GetUpgradeCost(int baseCost, int count) {
    return (int)(baseCost * powf(1.15f, count));
}

// Update game logic (passive income or similar if needed)
void UpdateGame(GameState *game, float dt) {
    // Could add passive bits gain here if desired
    (void)game;
    (void)dt;
}

// Draw game UI elements (bits, upgrades, etc)
void DrawGameUI(GameState *game, float dt) {
    (void)dt;
    // This is handled in main.c so keep empty or extend as needed
}

// Handle click: add bits according to bitsPerClick
void Click(GameState *game) {
    game->bits += game->bitsPerClick;
}

// Try to buy an upgrade
bool BuyUpgrade(GameState *game, int upgradeIndex) {
    if (upgradeIndex < 0 || upgradeIndex >= 15) return false;

    int cost = GetUpgradeCost(baseCosts[upgradeIndex], game->upgraderCounts[upgradeIndex]);
    if (game->bits >= cost) {
        game->bits -= cost;
        game->upgraderCounts[upgradeIndex]++;
        // Increase bitsPerClick accordingly
        game->bitsPerClick += bitsPerClickAdd[upgradeIndex];
        return true;
    }
    return false;
}

// Reset the game on rebirth but keep rebirth multiplier logic in main.c
void ResetGame(GameState *game) {
    game->bits = 0;
    game->bitsPerClick = 1;
    for (int i = 0; i < 15; i++) {
        game->upgraderCounts[i] = 0;
    }
}

