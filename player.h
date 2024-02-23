#ifndef __PLAYER__
#define __PLAYER__

#include <stdlib.h>
#include <stdint.h>

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
    char (*get_action)(); 
} t_player;

void player_init(t_player* p_player, uint8_t num);


#endif