#ifndef __PARAM__
#define __PARAM__

#define MAX_PLAYERS 4
#define MAP_SIZE 100
#define SPOT_NUM MAP_SIZE * MAP_SIZE
#define SQUARE_SIZE 10
#define WIN_SIZE MAP_SIZE * SQUARE_SIZE

#define P_CREDITS 100
#define BOMB_COUNTER 5

/*le cout de chaque mouvement*/
#define STILL_COST 1
#define COUT_ACTION_MOVE 1 
#define COUT_ACTION_DASH 10 
#define COUT_ACTION_SPLASH 8  
#define COUT_ACTION_TELEPORT 2
#define COUT_ACTION_BOMB 9    

#endif 