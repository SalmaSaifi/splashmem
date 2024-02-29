#ifndef __PLAYER__
#define __PLAYER__

#include <stdlib.h>
#include <stdint.h>

extern int start_pos_x[];
extern int start_pos_y[];

typedef struct s_player
{
    /* data */
    uint32_t id;
    uint32_t color;
    uint8_t* data;
    uint32_t x;
    uint32_t y;
    int32_t credits;
    uint32_t count;
    uint32_t bombs;
    uint8_t color_r;
    uint8_t color_g;
    uint8_t color_b;
    uint32_t score;
    char (*get_action)(); 
} t_player;

typedef struct s_bomb
{
    uint32_t id;
    uint32_t player_id;
    uint32_t x;
    uint32_t y;
    uint32_t rounds;
} t_bomb;

void player_init(t_player* p_player, uint8_t num);


#endif