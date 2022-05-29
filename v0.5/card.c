#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"card.h"
#include"game.h"


void build_pile(list *game){
    
    for(int i=0;i<4;i++){
        for(int j=0;j<13;j++){
            game->pile[i*13+j].suit = i;
            game->pile[i*13+j].face = j;
        }
    }
    
    srand(time(NULL));
    
    for (int i=0;i<CARD_NUM;i++){
        
        int rand_pos = rand()%52;
        card temp = game->pile[i];
        game->pile[i] = game->pile[rand_pos];
        game->pile[rand_pos] = temp;
    
    }
    game->pos = 0;
    return;
}

card darw(list *game){
    
    int ori_pos = game->pos;
    game->pos++;
    //delete game->card[top]
    //plater->hand add game->card[top]
    return game->pile[ori_pos];
}

void print_card(card crd){
    printf("Card: (%d,%d)\n",crd.suit,crd.face);
    return;
}
