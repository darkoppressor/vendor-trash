/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include <SDL.h>

#include "menus.h"
#include "timer.h"
#include "variables.h"
#include "input.h"
#include "logic.h"
#include "screen_draw.h"

using namespace std;

void menu_back(){
    switch(current_menu){
        case 1: case 2: case 4:
        main_menu();
        break;
        case 3:
        current_menu=0;
        city_screen();
        break;
    }
}

void main_menu(){
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,100);

    current_menu=0;/**Here we tell the game that we are currently on the main menu.*/

    /**Reset the selection bar.*/
    b_select_menu.box.x=-1;

    bool loop=true;

    Mix_VolumeMusic(MIX_MAX_VOLUME);
    Mix_PlayMusic(music_menu,-1);

    while(loop==true){
        input_menu();
        draw_main_menu();/**Redraw.*/
        SDL_Flip(screen);
    }
}

void options(){
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,100);

    current_menu=1;

    /**Reset the selection bar.*/
    b_select_menu.box.x=-1;

    bool loop=true;

    while(loop==true){
        input_options();
        draw_options();/**Redraw.*/
    }
}

void about(){
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,100);

    current_menu=2;

    /**Reset the selection bar.*/
    b_select_menu.box.x=-1;

    bool loop=true;

    while(loop==true){
        input_about();
        draw_about();/**Redraw.*/
    }
}
