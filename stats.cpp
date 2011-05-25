/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include "stats.h"
#include "sdl.h"
#include "screen_draw.h"
#include "input.h"
#include "variables.h"
#include "stats.h"
#include "dialog.h"

using namespace std;

void stats(){
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,100);
    current_menu=3;
    bool loop=true;
    /**Reset the selection bar.*/
    b_select_menu.box.x=-1;
    while(loop==true){
        input_stats();
        draw_city();/**Draw the city screen in the background.*/
        draw_stats();/**Draw the stats dialog box:*/
    }
}

void level_up(){
    string temp_msg="";
    level++;
    experience-=experience_max;
    experience_max*=1.3;
    skill_points+=5;
    health_max+=5+(level*.5);
    msg1="You have gained a level, and you are now level ";
    ss.clear();ss.str("");ss<<level;ss>>temp_msg;
    msg1+=temp_msg;
    msg1+="!";
    world_dialog_message();
}

void level_check(){
    while(experience>=experience_max){
        level_up();
    }
}
