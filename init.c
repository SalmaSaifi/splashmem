#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <dlfcn.h>
#include "param.h"
#include "world.h"
#include "actions.h"
#include "splash.h"


uint32_t colors[MAX_PLAYERS+1] = { 0 };

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void init_colors(SDL_PixelFormat *format)
{
    colors[0] = SDL_MapRGB(format, 0x00, 0x00, 0x00);
    colors[1] = SDL_MapRGB(format, 0xFF, 0, 0);
    colors[2] = SDL_MapRGB(format, 0, 0xFF, 0);
    colors[3] = SDL_MapRGB(format, 0, 0x0, 0xFF);
    colors[4] = SDL_MapRGB(format, 0xFF, 0, 0xFF);
}


/* ------------------------------------------------------------------------- */
/*                                                                           */
/* ------------------------------------------------------------------------- */
void inits(int argc, char *argv[])
{
    char *p1 =argv[1];
    char *p2 =argv[2];
    char *p3 =argv[3];
    char *p4 =argv[4];

    //Get window surface

    screenSurface = SDL_GetWindowSurface(window);
    SDL_PixelFormat *format = screenSurface->format;
    init_colors(format);

 //  L'ouvrerture des biblio dynamique 

    void *p1sopen = dlopen(p1, RTLD_LAZY);

    void *p2sopen = dlopen(p2, RTLD_LAZY);

    void *p3sopen = dlopen(p3, RTLD_LAZY);
    
    void *p4sopen = dlopen(p4, RTLD_LAZY); 

    actions_init();
    world_create_players();

    //Recuperer les references 

    players[0]->get_action = dlsym(p1sopen, "get_action");

    players[1]->get_action = dlsym(p2sopen, "get_action");

    players[2]->get_action = dlsym(p3sopen, "get_action");

    players[3]->get_action = dlsym(p4sopen, "get_action");

    printf("inits done\n");
}