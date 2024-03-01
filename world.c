#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>

#include "world.h"
#include "param.h"
#include "player.h"
#include "actions.h"
#include "splash.h"

/* !!!!!!!!!!!!!!!! MAP !!!!!!!!!!!!!!!!!!!!! */
/*code */
uint8_t mapmem[MAP_SIZE * MAP_SIZE] = {0};

/*  PLAYERS */
t_player *players[MAX_PLAYERS] = {0};

/*  BOMBS */
t_bomb *bombs[MAX_PLAYERS * BOMB_COUNTER] = {0};

int quitting2 = 0;

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
int world_get_winner()
{
    for (int i = 0; i < MAP_SIZE * MAP_SIZE; i++)
    {
        for (int j = 0; j < MAX_PLAYERS; j++)
        {
            if (mapmem[i] == players[j]->id)
            {
                players[j]->score++;
            }
        }
    }
    uint8_t winner = 0;
    for (int k = 1; k < MAX_PLAYERS; k++)
    {
        if (players[k]->score > players[winner]->score)
        {
            winner = k;
        }
    }

    for (int l = 0; l < MAX_PLAYERS; l++)
    {
        printf("%d\n", players[l]->score);
    }
    return winner;
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

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
int world_set_game_finish()
{
    uint8_t winner = world_get_winner();
    int start_pos_x[] = {MAP_SIZE/4, MAP_SIZE/4, MAP_SIZE*3/4, MAP_SIZE*3/4};
    int start_pos_y[] = {MAP_SIZE/4, MAP_SIZE*3/4, MAP_SIZE/4, MAP_SIZE*3/4};
    quitting = 0;
    SDL_Window *window = NULL;

    window = SDL_CreateWindow("SplashMem - Résultats", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, WIN_SIZE, WIN_SIZE,
                              SDL_WINDOW_SHOWN);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_AddEventWatch(watch, NULL);
    SDL_Event event;
    while (!quitting)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
            {
                quitting = 1;
            }
            case SDL_KEYDOWN:
            {
                SDL_Log("Touche enfoncée");
                if(event.key.keysym.sym == SDLK_r)
                {
                    SDL_Log("Touche R appuyée");
                    for (int i = 0; i < MAP_SIZE * MAP_SIZE; i++)
                    {
                        mapmem[i] = 0;
                    }
                    for (int i = 0; i < MAX_PLAYERS; i++)
                    {
                        player_init(players[i], i);
                    }
                    return 0;
                }
                if(event.key.keysym.sym == SDLK_q)
                {
                    quitting = 1;
                    SDL_Log("Touche Q appuyée");
                }
            }
        }

        if (TTF_Init() != 0)
        {
            fprintf(stderr, "Erreur d'initialisation TTF : %s\n", TTF_GetError()); 
        }
        TTF_Font * font;
        font = TTF_OpenFont("arial.ttf", 72); 
        
        // Détermination du gagnant
        char win[50] = "Le gagnant est le joueur ";
        char gagnant[10];
        sprintf(gagnant, "%d", (winner + 1));
        strcat(win, gagnant);

        // Affichage du gagnant
        SDL_Color first = {0xFF, 0xFF, 0xFF};
        SDL_Rect premier;
        premier.x = SQUARE_SIZE/2;
        premier.y = SQUARE_SIZE/10;
        premier.w = MAP_SIZE * SQUARE_SIZE;
        premier.h = 100;
        SDL_Surface *text = TTF_RenderText_Blended(font, win, first);
        SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, text);
        SDL_RenderCopy(renderer, texture, NULL, &premier);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(text);

        // Affichage des touches pour relancer ou quitter le jeu
        SDL_Rect controls;
        controls.x = SQUARE_SIZE/2;
        controls.y = (8 * (MAP_SIZE *SQUARE_SIZE)/10);
        controls.w = MAP_SIZE * SQUARE_SIZE;
        controls.h = 100;
        SDL_Surface *control = TTF_RenderText_Blended(font, "Relancer une partie (R) / Quitter le jeu(Q)", first);
        SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, control);
        SDL_RenderCopy(renderer, texture2, NULL, &controls);
        SDL_DestroyTexture(texture2);
        SDL_FreeSurface(control);

        // Couleur du score pour chaque joueur
        SDL_Color color[4];
        color[0].r = 0xFF;
        color[0].g = 0;
        color[0].b = 0;
        color[1].r = 0;
        color[1].g = 0xFF;
        color[1].b = 0;
        color[2].r = 0;
        color[2].g = 0;
        color[2].b = 0xFF;
        color[3].r = 0xFF;
        color[3].g = 0;
        color[3].b = 0xFF;

        // Affichage du score de chaque joueur
        for (int i = 0; i < 4; i++)
        {
            SDL_Rect score[i];
            score[i].x = start_pos_x[i]*SQUARE_SIZE - 50;
            score[i].y = start_pos_y[i]*SQUARE_SIZE - 50;
            score[i].w = 100;
            score[i].h = 100;
            char player_score[10];
            sprintf(player_score, "%d", players[i]->score);
            SDL_Surface *text = TTF_RenderText_Blended(font, player_score, color[i]);
            SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, text);
            SDL_RenderCopy(renderer, texture, NULL, &score[i]);
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(text);
        }
        TTF_CloseFont(font);
        SDL_RenderPresent(renderer);
    }
    SDL_DelEventWatch(watch, NULL);
    SDL_DestroyWindow(window);
    
    return 1;
}