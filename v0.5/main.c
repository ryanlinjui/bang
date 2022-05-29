#include<stdio.h>
#include<string.h>
#include"game.h"
#include"card.h"

int main(){

    int player_num = 3;

    list game;
    
    memset(&game,0,sizeof(list));
    game.next = NULL;
    game.players_num = player_num;
    
    build_pile(&game);
    
    player bot[player_num];
    bot[0].bullets = 2;
    bot[1].bullets = 4;
    bot[2].bullets = 4;
    
    strcpy(bot[0].user_name,"Alice");
    strcpy(bot[1].user_name,"Bill");
    strcpy(bot[2].user_name,"Carl");
    
    for(int i=0;i<player_num;i++){
        build_list(&game,bot[i]);
    }
    
    print_card( darw(&game) );
    print_card( darw(&game) );
    print_card( darw(&game) );
    print_card( darw(&game) );
    print_card( darw(&game) );
    print_card( darw(&game) );
    
    //print_list(&game);
    
    free_list(&game);

    return 0;
}
