#include "actions.h"
#include <stdio.h>
#define MAX_PLAY_ACTION 8

char play_actions[] = {
    ACTION_TELEPORT_L,
    ACTION_MOVE_D,
    ACTION_SPLASH,
    ACTION_MOVE_D,
    ACTION_MOVE_R,
    ACTION_BOMB,
    ACTION_DASH_R,
};

char get_action()
{
    static int i = 0;
    char ret_val = 0;

    ret_val = play_actions[i];
    i++;
    if (i >= MAX_PLAY_ACTION)
    {
        i = 0;
    }
    return (ret_val);
}