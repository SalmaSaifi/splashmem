#include <stdlib.h>
#include <SDL2/SDL.h>
#include "player.h"
#include "param.h"

int start_pos_x[] = {MAP_SIZE/4, MAP_SIZE/4, MAP_SIZE*3/4, MAP_SIZE*3/4};
int start_pos_y[] = {MAP_SIZE/4, MAP_SIZE*3/4, MAP_SIZE/4, MAP_SIZE*3/4};

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void player_init(t_player* p_player, uint8_t num)
{
    p_player->id = num + 1;
    p_player->color = 0;
    p_player->x = start_pos_x[num];
    p_player->y = start_pos_y[num];
    p_player->credits = P_CREDITS;
    p_player->count = 0;
    p_player->bombs = BOMB_COUNTER;
    p_player->score = 0;
}

void bombs_init(t_bomb* b_bomb, uint8_t i, uint8_t j)
{
    b_bomb->id = i*BOMB_COUNTER + j + 1;
    b_bomb->player_id = i + 1;
    b_bomb->x = 0;
    b_bomb->y = 0;
    b_bomb->rounds = -1;
}