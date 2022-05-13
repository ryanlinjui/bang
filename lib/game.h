#pragma once
#include "cstd.h"
#include "player.h"
#include "card.h"

struct GameVariable
{
    struct Order
    {
        char **queue;
        uint8_t turn;
    };
    Card *card_pile;
    Player *player;
    uint8_t total_player;
};

void game_settings(void);
void game_init(void);

