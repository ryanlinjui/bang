#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"game.h"

int main(){

    int player_num = 4;
    list game;
    memset(&game,0,sizeof(list));
    game.next = NULL;
    game.players_num = player_num;
    
    build_pile(&game);
    
    player bot[player_num];
    //get_role
    int role_list[8] = {SHERIFF,
                        RENEGADE,
                        OUTLAW,
                        OUTLAW,
                        DEPUTY_SHERIFF,
                        OUTLAW,
                        DEPUTY_SHERIFF,
                        RENEGADE};
    srand(time(NULL));
    for(int i=0;i<player_num;i++){
        int rand_pos = rand()%player_num;
        int temp = role_list[i];
        role_list[i] = role_list[rand_pos];
        role_list[rand_pos] = temp;
    }
    
    //player_info
    for(int i=0;i<player_num;i++){
        memset(&bot[i],0,sizeof(player));
        set_player(&game,&bot[i]);
        bot[i].role_ID = role_list[i];
        build_list(&game,bot[i]);
    }
    game.next = get_sheriff(&game);
    player *current = game.next;
    while(1){
        //stage 1 : draw 2 cards
        get_card(draw(&game),current);
        get_card(draw(&game),current);
        
        //stage 2 : use cards
        while(1){
            if(play_card(&game,current)){
                break;
            }
        }
        //win check
        if(game.win_role != 0){
            break;
        }
        
        //stage 3 : discard
        current = current->next;
        game.bang_play = 0;
    }
    
    printf("win role is %s\n",role_name(game.win_role));
    
    printf("\n after play \n");
    print_list(&game);
    free_list(&game);
    return 0;
}
