#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"game.h"


// building list from dummy head
/*
	   dummy
	     |
   player->sheriff->player
      \             /  
       player<-player
*/
// list function   ||     
//                 ||    
//                 \/     
//=============================


// delete a player and free that player
void delete_player(list *game,player *bot){
    
    if(bot == game->next){
        game->next = bot->next;
        printf("you delete sheriff\n");
    }
    
    player *current = game->next;
    while(current->next != bot){
        current = current->next;
    }
    player *temp = current->next;
    current->next = temp->next;
    free(temp);
    return;
}

// just free list
void free_list(list *game){
    player *current = game->next;
    player *temp;
    for(int i=0;i<(game->players_num);i++){
        temp = current;
        current = current->next;
        free(temp);
    }
    return;
}

void build_list(list *game,player bot){
    
    player *new;
    new = (player*)malloc(sizeof(player));
    
    *new = bot;

    if((game->next) == NULL){
        game->next = new;
        new->next = new;
        return;
    }
    
    player *sheriff = game->next;
    player *current = sheriff;
    
    while(current->next != sheriff){
        current = current->next;
    }
    current->next = new;
    new->next = sheriff;

    return;
}


// game function   ||     
//                 ||    
//                 \/     
//=============================


int play_card(list *game,player *bot){
    printf("%s\n",bot->user_name);
    print_player_hand(bot);
    printf("%d) end turn\n",bot->cards_num+1);
    printf("please select a card:");
    int sel=0;
    scanf("%d",&sel);
    sel--;
    if(sel == (bot->cards_num)){
        return 1;
    }
    if(bot->hand_card[sel].ability(game,bot)){
        printf("fill play\n");
        return 0;
    }
    
    for(int i=sel;i<(bot->cards_num);i++){
        bot->hand_card[i] = bot->hand_card[i+1];
    }
    bot->cards_num--;
    
    memset(&(bot->hand_card[bot->cards_num]),0,sizeof(card));
    return 0;
}


card *draw(list *game){
    int ori_pos = game->pos;
    game->pos++;
    return &game->pile[ori_pos];
}

void get_card(card *new_card,player *bot){
    bot->hand_card[bot->cards_num] = *new_card;
    bot->cards_num++;
    new_card->is_available = 0;
    return;
}

void set_player(list *game,player *bot){
    printf("please enter user name : ");
    char name[16];
    scanf("%s",name);
    strcpy(bot->user_name,name);

    bot->charater_ID = 401;
    bot->bullets = (bot->charater_ID)/100;
    
    for(int i=0;i<(bot->bullets);i++){
        get_card(draw(game),bot);
    }
    return;
}


// just get distance
int get_distance(player *bot1,player *bot2){

    int left = 0;
    int right = 0;
    
    player *current = bot1;
    
    while(current != bot2){
        current = current->next;
        left++;
    }
    
    while(current != bot1){
        current = current->next;
        right++;
    }
    
    if(right>left) return left;
    return right;
}

// frist list all player, then select a number, return that player ptr
player *select_player(list *game){
    player *sheriff = game->next;
    print_list(game);
    printf("please select a player:");
    int sel = 0;
    scanf("%d",&sel);
    
    player *current = sheriff;
    
    for(int i=0;i<sel-1;i++){
        current = current->next;
    }
    return current;
}

player *select_other_player(list *game,player *bot){
    player *current = bot;
    current = current->next;
    
    int count = 1;
    while(current != bot){
        printf("%d) ",count);
        print_player(current);
        current = current->next;
        count++;
    }
    
    printf("please select a player:");
    int sel = 0;
    scanf("%d",&sel);
    
    for(int i=0;i<sel;i++){
        current = current->next;
    }
    return current;
}

player *get_sheriff(list *game){
    player *sheriff = game->next;
    
    while(sheriff->role_ID != SHERIFF){
        sheriff = sheriff->next;
    }
    return sheriff;
}

// print function  ||     
//                 ||    
//                 \/     
//=============================


void print_list(list *game){
    
    if(game->next == NULL){
        printf("It's empty\n");
        return;
    }
    
    player *sheriff = game->next;
    player *current = sheriff;
    int count = 1;
    do{
        printf("%d) ",count);
        print_player(current);
        
        current = current->next;
        count++;
    }while(current != sheriff);
    
    return;
}

char *role_name(int role_ID){
    char *name[4] = {"Sheriff","Deputy_sheriff","Outlaw","Renegade"};
    return name[role_ID-1];
}

char *card_name(int card_ID){
    char *name[3] = {"Bang!","Miss","beer"};
    return name[(card_ID%100)-1];
} 


//print player user_name bullets
void print_player(player *bot){
    printf("%16s: ",bot->user_name);
    printf("bullet: %d card_num[%d] role:%s\n",bot->bullets,bot->cards_num,role_name(bot->role_ID));
    return;   
}

void print_card(card crd){
    printf("Card: %s(%d,%d)\n",crd.name,crd.suit,crd.face);
    return;
}

void print_player_hand(player *bot){
    for(int i=0;i<(bot->cards_num);i++){
        printf("%d) ",i+1);
        print_card(bot->hand_card[i]);
    }
    return;
}

// pile function  ||     
//                ||    
//                \/     
//=============================


void build_pile(list *game){
    
    card pile[12] = {{"Bang!"        ,101,&Bang},
                    {"Miss"          ,102,&Miss},
                    {"Beer"          ,103,&Beer},
                    {"Cat_Balou"     ,104,&Duel},
                    {"Panic"         ,105,&Panic},
                    {"Duel"          ,106,&Duel},
                    {"General_Store" ,107,&General_Store},
                    {"Indians"       ,108,&Indians},
                    {"Gatling"       ,109,&Gatling},
                    {"Salon"         ,110,&Salon},
                    {"Wells_Fargo"   ,111,&Wells_Fargo},
                    {"Stagecoach"    ,112,&Stagecoach}
                    };
    int every_card_num[12] = {25,12,6,4,4,3,2,2,1,1,1,2};
    
    int count=0;
    for(int i=0;i<12;i++){
        for(int j=0;j<every_card_num[i];j++){
            game->pile[count] = pile[i];
            count++;
        }
    }
    
    srand(time(NULL));
    
    for(int i=0;i<CARD_NUM;i++){
        game->pile[i].suit = rand()%4+1;
        game->pile[i].face = rand()%13+1;
    }
    
    for (int i=0;i<CARD_NUM;i++){
        int rand_pos = rand()%CARD_NUM;
        card temp = game->pile[i];
        game->pile[i] = game->pile[rand_pos];
        game->pile[rand_pos] = temp;
    }
    game->pos = 0;
    return;
}

// card ability   ||     
//                ||    
//                \/     
//=============================

void heal(player *bot){
    if(bot->bullets < (bot->charater_ID/100)){
        bot->bullets++;
    }
    return;
}

void die(list *game,player *bot){
    printf("%s Has been slain!!!\n",bot->user_name);
    delete_player(game,bot);
    game->players_num--;
    
    //win check
    int sheriff_flag = 0;
    int outlaw_flag = 0;
    int renegade_flag = 0;

    player *current = game->next;
    if(current->role_ID == SHERIFF){
        sheriff_flag = 1;
    }
    current = current->next;
    for(int i=0;i<(game->players_num);i++){
        if(current->role_ID == OUTLAW){
            outlaw_flag = 1;
        }
        if(current->role_ID == RENEGADE){
            renegade_flag = 1;
        }
    }
    if(!(outlaw_flag || renegade_flag)){
        game->win_role = SHERIFF;
        return;
    }
    if(!sheriff_flag){
        game->win_role = OUTLAW;
        return;
    }
    if(!(outlaw_flag || sheriff_flag)){
        game->win_role = RENEGADE;
        return;
    }
    return;
}

void damg(list *game,player *bot){

    bot->bullets--;
    if(bot->bullets <= 0){
        player *current = bot->next;
        for(int i=0;i<((game->players_num)-1);i++){
            printf("%s is dying do you want ",bot->user_name);
            if(play_specify_card(game,current,103)){
                heal(bot);
            }
            if(bot->bullets > 0){
                break;
            }
            current=current->next;
        }
    }
    if(bot->bullets <= 0){
        die(game,bot);
    }
    return;
}

int play_specify_card(list *game,player *bot,int card_id){
    
    printf("play %s\n",card_name(card_id));
    
    print_player_hand(bot);
    printf("please select a card:");
    int sel=0;
    scanf("%d",&sel);
    sel--;
    if(bot->hand_card[sel].card_ID != card_id){
        return 0;
    }
    
    for(int i=sel;i<(bot->cards_num);i++){
        bot->hand_card[i] = bot->hand_card[i+1];
    }
    bot->cards_num--;
    memset(&(bot->hand_card[bot->cards_num]),0,sizeof(card));
    return 1;
}

card *discard(player *bot){
    srand(time(NULL));
    int random_card = rand()%(bot->cards_num); 
    
    card *discard_card = &bot->hand_card[random_card];
    
    for(int i=random_card;i<(bot->cards_num);i++){
        bot->hand_card[i] = bot->hand_card[i+1];
    }
    
    bot->cards_num--;
    memset(&(bot->hand_card[bot->cards_num]),0,sizeof(card));
    return discard_card;
}



// card function  ||     
//                ||    
//                \/     
//=============================


int Wells_Fargo(list *game,player *bot){
    get_card(draw(game),bot);
    get_card(draw(game),bot);
    get_card(draw(game),bot);
    return 0;
}

int Stagecoach(list *game,player *bot){
    get_card(draw(game),bot);
    get_card(draw(game),bot);
    return 0;
}

int Salon(list *game,player *bot){
    player *current = bot;
    do{
        heal(current);
        current=current->next;
    }while((current) != bot);
    return 0;
}


int Bang(list *game,player *bot){

    if(game->bang_play != 0){
        printf("you already play bang\n");
        return 1;
    }
    printf("Bang! select a target\n");
    player *target = select_other_player(game,bot);
    if(!play_specify_card(game,target,102)){
        damg(game,target);
    }
    game->bang_play++;
    return 0;
}

int Miss(list *game,player *bot){
    printf("you can't player miss\n");
    return 1;
}

int Beer(list *game,player *bot){
    if(game->players_num != 2){
        heal(bot);
    }
    return 0;
}

int Panic(list *game,player *bot){
    player *target = select_other_player(game,bot);
    get_card(discard(target),bot);
    return 0;
}

int General_Store(list *game,player *bot){
    card *store[game->players_num];
    for(int i=0;i<(game->players_num);i++){
        store[i] = draw(game);
    }
    player *current = bot;
    for(int i=0;i<(game->players_num)-1;i++){
        //list card
        for(int j=0;j<(game->players_num)-i;j++){
            printf("%d) ",j+1);
            print_card(*store[j]);
        }
        printf("please select a card(General_Store): ");
        int sel = 0;
        scanf("%d",&sel);
        sel--;
        get_card(store[sel],current);
        
        for(int j=sel;j<(game->players_num)-i;j++){
            store[j] = store[j+1];
        }
        current=current->next;
    }
    get_card(store[0],current);
    return 0;
}

int Duel(list *game,player *bot){
    player *target = select_other_player(game,bot);
    player *current = target;
    
    while(1){
        if(!play_specify_card(game,current,101)){
            damg(game,current);
            break;
        }
        if(current==bot){
            current=target;
        }
        else{
            current=bot;
        }
    }
    return 0;
}

int Gatling(list *game,player *bot){
    player *current = bot;
    current = current->next;
    
    while(current != bot){
        if(!play_specify_card(game,current,102)){
            damg(game,current);
        }
        current=current->next;
    }
    return 0;
}

int Indians(list *game,player *bot){
    player *current = bot;
    current = current->next;
    
    while(current != bot){
        if(!play_specify_card(game,current,101)){
            damg(game,current);
        }
        current=current->next;
    }
    return 0;
}




/*
int Cat_Balou(list *game,player *bot){

1) random handcard
2) gun if thy have one
x)...list target gear

need card_name function

char* (int card_ID){

}

    player *target = select_player(game);
    int count = 0;
    
    int card_flag = 0;
    int gun_flag = 0;
    int gear_flag = 0;
    
    if(bot->cards_num){
        count++;
        card_flag++;
        printf("%d) discard %s random hand card\n",count,bot->user_name);
    }
    if(bot->gun){
        count++;
        gun_flag++;
        printf("%d) discard %s gun\n",count,bot->user_name);
    }
    for(int i=0;i<bot->gear_num;i++){
        count++;
        gear_flag++;
        printf("%d) discard %s %s\n",count,bot->user_name,card_name(bot->gear[i]));
    }
    printf("Please enter selection : ");
    int sel = 0 ;
    scanf("%d",&sel);
    
    if(sel == card_flag){
    
    }
    if(sel == gun_flag){
    
    }
    discard_random(target);
}
*/


// gear function  ||     
//                ||    
//                \/     
//=============================



// roop function  ||     
//                ||    
//                \/     
//=============================







