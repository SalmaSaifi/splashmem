#ifndef __WORLD__
#define __WORLD__

#include "param.h"
#include "player.h" 

extern uint8_t mapmem[];
extern t_player *players[];
extern t_bomb *bombs[];

void world_paint_spot(uint32_t x, uint32_t y, uint32_t num);
void world_do_player_action(t_player* p_player);
void world_set_players();
void world_create_players();
int world_get_winner();
void world_create_bombs();
void world_set_bomb(t_player *p_player);
void world_bomb_explosion(t_bomb *p_bomb);
void bombs_init(t_bomb* b_bomb, uint8_t i, uint8_t j);
void world_set_game_finish();

#endif 