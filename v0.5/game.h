
#pragma once
#define CARD_NUM 52
#define MAX_CARD_HOLD 10

typedef struct _card{
    int suit;
    int face;
    //char name[40];
    //int (*skill)(void *this);
}card;


typedef struct _player{
    char user_name[32];
    int bullets;
    int cards_num;
    card hand_card[MAX_CARD_HOLD];
    struct _player *next;
}player;


typedef struct _list{
    int players_num;
    
    int pos;
    card pile[CARD_NUM];
    player *next;
}list;

void build_list(list *game,player bot);
void print_list(list *game);
void print_player(player *bot);
player *select_player(list *game);
int get_distance(player *bot1,player *bot2);
void free_list(list *game);
void delete_player(list *game,player *bot);
