#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "param.h"
#include "actions.h"
#include "world.h"

void actions_init()
{
    /* Ajouter du code */
}


void actions_do(t_player *p_player, enum action id)
{
    p_player->count++; 
        // Selon l'action demandée, effectue différentes actions
    switch (id)
    {
        
    case ACTION_MOVE_L:  /* Déplacement vers la gauche */

        if (p_player->credits >= COUT_ACTION_MOVE)  // Vérifie si le joueur a suffisamment de crédits pour effectuer l'action
        {
            if (p_player->x <= 0)
            {
                p_player->x = MAP_SIZE;
            }
            p_player->x--;

            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= COUT_ACTION_MOVE;  // Déduction du coût de l'action des crédits du joueur
        }
        break;
            

    case ACTION_MOVE_R: /* Déplacement vers la droite */
        if (p_player->credits >= COUT_ACTION_MOVE)
        {
            p_player->x++;
            if (p_player->x >= MAP_SIZE)
            {
                p_player->x = 0;
            }

            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= COUT_ACTION_MOVE;
        }

        break;

    case ACTION_MOVE_U:/* Déplacement vers le haut */
        if (p_player->credits >= COUT_ACTION_MOVE)
        {
            if (p_player->y <= 0)
            {
                p_player->y = MAP_SIZE;
            }
            p_player->y--;

            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= COUT_ACTION_MOVE;
        }

        break;

    case ACTION_MOVE_D:/* Déplacement vers le bas */
        if (p_player->credits >= COUT_ACTION_MOVE)
        {
            if (p_player->y >= MAP_SIZE)
            {
                p_player->y = 0;
            }
            p_player->y++;

            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= COUT_ACTION_MOVE;
        }

        break;
        
    case ACTION_DASH_L:  /* Dash vers la gauche */
        if (p_player->credits >= COUT_ACTION_DASH)
        {
            for (int i = 0; i < 8; i++)
            {
                if (p_player->x <= 0)
                {
                    p_player->x = MAP_SIZE;
                }
                p_player->x--;
                world_paint_spot(p_player->x, p_player->y, p_player->id);
            }
            p_player->credits -= COUT_ACTION_DASH;
        }

        break;

    case ACTION_DASH_R: /* Dash vers la droite */
        if (p_player->credits >= COUT_ACTION_DASH)
        {
            for (int i = 0; i < 8; i++)
            {
                if (p_player->x >= MAP_SIZE)
                {
                    p_player->x = 0;
                }
                p_player->x++;
                world_paint_spot(p_player->x, p_player->y, p_player->id);
            }
            p_player->credits -= COUT_ACTION_DASH;
        }

        break;

    case ACTION_DASH_U:/* Dash vers le haut */
        if (p_player->credits >= COUT_ACTION_DASH)
        {
            for (int i = 0; i < 8; i++)
            {
                if (p_player->y <= 0)
                {
                    p_player->y = MAP_SIZE;
                }
                p_player->y--;
                world_paint_spot(p_player->x, p_player->y, p_player->id);
            }
            p_player->credits -= COUT_ACTION_DASH;
        }

        break;

    case ACTION_DASH_D:/* Dash vers le bas */
        if (p_player->credits >= COUT_ACTION_DASH)
        {
            for (int i = 0; i < 8; i++)
            {
                if (p_player->y >= MAP_SIZE)
                {
                    p_player->y = 0;
                }
                p_player->y++;
                world_paint_spot(p_player->x, p_player->y, p_player->id);
            }
            p_player->credits -= 10;
        }

        break;

    case ACTION_TELEPORT_L:
        if (p_player->credits >= COUT_ACTION_TELEPORT)
        {
            for (int i = 0; i < 8; i++)
            {
                if (p_player->x <= 0)
                {
                    p_player->x = MAP_SIZE;
                }
                p_player->x--;
            }
            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= COUT_ACTION_TELEPORT;
        }
        
        break;

    case ACTION_TELEPORT_R:
        if (p_player->credits >= COUT_ACTION_TELEPORT)
        {
            for (int i = 0; i < 8; i++)
            {
                if (p_player->x >= MAP_SIZE)
                {
                    p_player->x = 0;
                }
                p_player->x++;
            }
            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= COUT_ACTION_TELEPORT;
        }

        break;

    case ACTION_TELEPORT_U:
        if (p_player->credits >= COUT_ACTION_TELEPORT)
        {
            for (int i = 0; i < 8; i++)
            {
                if (p_player->y <= 0)
                {
                    p_player->y = MAP_SIZE;
                }
                p_player->y--;
            }
            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= COUT_ACTION_TELEPORT;
        }

        break;

    case ACTION_TELEPORT_D:
        if (p_player->credits >= COUT_ACTION_TELEPORT)
        {
            for (int i = 0; i < 8; i++)
            {
                if (p_player->y >= MAP_SIZE)
                {
                    p_player->y = 0;
                }
                p_player->y++;
            }
            world_paint_spot(p_player->x, p_player->y, p_player->id);
            p_player->credits -= COUT_ACTION_TELEPORT;
        }

        break;


    case ACTION_SPLASH:
        if (p_player->credits >= COUT_ACTION_SPLASH)
        {
            for (int b = 0; b < 3; b++)
            {
                for (int a = 0; a < 3; a++)
                {
                    uint32_t cord_x = p_player->x - 1 + b;
                    uint32_t cord_y = p_player->y - 1 + a;

                    if (cord_x <= MAP_SIZE && cord_y <= MAP_SIZE)
                    {
                        world_paint_spot(cord_x, cord_y, p_player->id);
                    }
                    else if (cord_x > MAP_SIZE)
                    {
                        cord_x = 1;
                        world_paint_spot(cord_x, cord_y, p_player->id);
                    }
                    else if (cord_y > MAP_SIZE)
                    {
                        cord_y = 1;
                        world_paint_spot(cord_x, cord_y, p_player->id);
                    }
                }
            }
            p_player->credits -= COUT_ACTION_SPLASH;
        }

        break;

    case ACTION_STILL:
        // Pas d'action
        if (p_player->credits >= STILL_COST)
        { 
            p_player->credits -= STILL_COST;
        }

        break;

    case ACTION_BOMB:
        if (p_player->credits >= COUT_ACTION_BOMB && p_player->bombs > 0)
        {
            world_set_bomb(p_player);            
            p_player->bombs --;
            p_player->credits -= COUT_ACTION_BOMB;
        }

        break;
    }
}