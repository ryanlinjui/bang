#pragma once

#define CARD_NUM 63
#define MAX_CARD_HOLD 10
#define MAX_GEAR_EQUIP 6
#define RANDOM 0

#define SHERIFF        1
#define DEPUTY_SHERIFF 2
#define OUTLAW         3
#define RENEGADE       4

typedef struct _player player;
typedef struct _list list;

typedef struct _card{
    char name[32];
    int card_ID;
    int (*ability)(list*,player*);
    int suit;
    int face;
    int is_available;
}card;


typedef struct _player{
    char user_name[16];
    int bullets;
    int cards_num;
    card hand_card[MAX_CARD_HOLD];
    
    card gun;
    int gear_num;
    int gear[MAX_GEAR_EQUIP];
    
    int role_ID;
    int charater_ID;
    
    int self_to_player;
    int player_to_self;
    
    struct _player *next;
}player;


typedef struct _list{
    int players_num;
    
    int bang_play;
    
    int win_role;
    
    int pos;
    card pile[CARD_NUM];
    
    player *next;
}list;


// list function
void delete_player(list *game,player *bot);
void free_list(list *game);
void build_list(list *game,player bot);


// game function
int play_card(list *game,player *bot);
card *draw(list *game);
void get_card(card *new_card,player *bot);
void set_player(list *game,player *bot);
int get_distance(player *bot1,player *bot2);
player *select_player(list *game);
player *get_sheriff(list *game);
player *select_other_player(list *game,player *bot);


// print function
void print_list(list *game);
void print_player(player *bot);
void print_card(card crd);
void print_player_hand(player *bot);
char *role_name(int role_ID);

// pile function
void build_pile(list *game);

//card ability
int play_specify_card(list *game,player *bot,int card_id);
card *discard(player *bot);


// card function
int Wells_Fargo(list *game,player *bot);
int Stagecoach(list *game,player *bot);
int Salon(list *game,player *bot);
int Bang(list *game,player *bot);
int Miss(list *game,player *bot);
int Beer(list *game,player *bot);
int Panic(list *game,player *bot);
int General_Store(list *game,player *bot);
int Duel(list *game,player *bot);
int Indians(list *game,player *bot);
int Gatling(list *game,player *bot);

// roop function



