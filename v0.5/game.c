#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"game.h"


// building list from dummy head
/*
	   dummy
	     |
   player->sheriff->player
      \             /  
       player<-player

*/

void build_list(list *game,player bot){
    
    player *new;
    new = (player*)malloc(sizeof(player));
    
    // copy from bot
    new->bullets = bot.bullets;
    strcpy(new->user_name,bot.user_name);
    //end copy
    
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


// print value in each player struct

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

/*
now it print:
    user_name
    bullets
*/
void print_player(player *bot){
    printf("%s:\n",bot->user_name);
    printf("bullet: %d\n",bot->bullets);
    return;   
}



// frist list all player, then select a number, return that player ptr

player *select_player(list *game){
    player *sheriff = game->next;
    print_list(game);
    int sel = 0;
    scanf("%d",&sel);
    
    player *current = sheriff;
    
    for(int i=0;i<sel-1;i++){
        current = current->next;
    }
    return current;
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

// just free list
void free_list(list *game){
    
    player *current = game->next;
    player *temp;
    for(int i=0;i<game->players_num;i++){
        
        temp = current;
        current = current->next;
        free(temp);
        
    }
    return;
}

// delete a player and free that player
void delete_player(list *game,player *bot){
    
    if(bot == game->next){
        printf("you can't delete this\n");
        return;
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
