#pragma once
#include "character/character.h"
#include "item/item.h"
#include "role/role.h"

typedef struct _sCard
{
    uint8_t suit; // size: 4 
    uint16_t value; // size: 13
    uint32_t item; //size: 22
}Card;