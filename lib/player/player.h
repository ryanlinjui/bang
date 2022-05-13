#pragma once
#include "cstd.h"
#include "card/card.h"

typedef struct _player
{
    uint8_t hp;
    uint8_t role; //size: 4~7
    uint8_t character; //size: 16
    int8_t *distance;
    Card equip;
    Card card;
    char *nickname;
}Player;
