#include <stdlib.h>
#include <stdio.h>

#include "world.h"
#include "param.h"
#include "player.h"
#include "actions.h"

/* !!!!!!!!!!!!!!!! MAP !!!!!!!!!!!!!!!!!!!!! */
/*code */
uint8_t mapmem[MAP_SIZE * MAP_SIZE] = {0};

/*  PLAYERS */
t_player *players[MAX_PLAYERS] = {0};

/*  BOMBS */
t_bomb *bombs[MAX_PLAYERS * BOMB_COUNTER] = {0};

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_create_players()
{
    int i = 0;

    for (i = 0; i < MAX_PLAYERS; i++)
    {
        players[i] = (t_player *)malloc(sizeof(t_player));
        player_init(players[i], i);
        world_paint_spot(players[i]->x, players[i]->y, players[i]->id);
    }
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_create_bombs()
{
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        for (int j = 0; j < BOMB_COUNTER; j++)
        {
            bombs[i*BOMB_COUNTER + j] = (t_bomb *)malloc(sizeof(t_bomb));
            bombs[i*BOMB_COUNTER+j]->player_id = i+1;
            bombs[i*BOMB_COUNTER+j]->x = 0;
            bombs[i*BOMB_COUNTER+j]->y = 0;
            bombs[i*BOMB_COUNTER+j]->rounds = -1;
            //bombs_init(bombs[i*BOMB_COUNTER + j], i, j);
        }
    }
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_do_player_action(t_player *p_player)
{
    // ici du code a qui fonctionne
    actions_do(p_player, p_player->get_action());
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_paint_spot(uint32_t x, uint32_t y, uint32_t num)
{
    uint32_t pos = y * MAP_SIZE + x;
    mapmem[pos] = num;
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_get_winner()
{
    // ici du code a qui fonctionne
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_set_bomb(t_player *p_player)
{
    bombs[(p_player->id - 1) * BOMB_COUNTER + p_player->bombs-1]->player_id = p_player->id;
    bombs[(p_player->id - 1) * BOMB_COUNTER + p_player->bombs-1]->x = p_player->x;
    bombs[(p_player->id - 1) * BOMB_COUNTER + p_player->bombs-1]->y = p_player->y;
    bombs[(p_player->id - 1) * BOMB_COUNTER + p_player->bombs-1]->rounds = p_player->count;
}

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void world_bomb_explosion(t_bomb *p_bomb)
{
    for (int b = 0; b < 3; b++)
    {
        for (int a = 0; a < 3; a++)
        {
            uint32_t cord_x = p_bomb->x - 1 + b;
            uint32_t cord_y = p_bomb->y - 1 + a;

            if (cord_x <= MAP_SIZE && cord_y <= MAP_SIZE)
            {
                world_paint_spot(cord_x, cord_y, p_bomb->player_id);
            }
            else if (cord_x > MAP_SIZE)
            {
                cord_x = 1;
                world_paint_spot(cord_x, cord_y, p_bomb->player_id);
            }
            else if (cord_y > MAP_SIZE)
            {
                cord_y = 1;
                world_paint_spot(cord_x, cord_y, p_bomb->player_id);
            }
        }
    }
}