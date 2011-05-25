/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include "dialog.h"
#include "input.h"
#include "screen_draw.h"
#include "variables.h"
#include "sdl.h"
#include "random_events.h"
#include "logic.h"

#include <SDL.h>

using namespace std;

/**Get the player's name.*/
void get_name(){
    SDL_EnableKeyRepeat(250,50);

    SDL_EnableUNICODE(SDL_ENABLE);

    bool loop=true;
    /**Reset the selection bar.*/
    b_select_menu.box.x=-1;

    while(loop==true){
        input_get_name();
        if(confirm==true){
            confirm=false;
            SDL_EnableUNICODE(SDL_DISABLE);
            return;
        }
        draw_main_menu();
        draw_get_name();
    }
}

/**Get the max number of days for this game.*/
void get_max_days(){
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,100);

    bool loop=true;
    /**Reset the selection bar.*/
    b_select_menu.box.x=-1;

    while(loop==true){
        input_get_max_days();
        if(confirm==true){
            confirm=false;
            return;
        }
        draw_main_menu();
        draw_get_max_days();
    }
}

/**Display a new game dialog message.*/
void new_game_dialog_message(){
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,100);

    bool loop=true;
    /**Reset the selection bar.*/
    b_select_menu.box.x=-1;

    while(loop==true){
        input_dialog_message();
        if(confirm==true){
            confirm=false;
            /**Reset all of the dialog message strings.*/
            msg1="0";
            msg2="0";
            msg3="0";
            msg4="0";
            msg5="0";
            msg6="0";
            msg7="0";
            msg8="0";
            return;
        }
        draw_main_menu();
        draw_new_game_dialog_message();
    }
}

/**Display a dialog message.*/
void dialog_message(){
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,100);

    bool loop=true;
    /**Reset the selection bar.*/
    b_select_menu.box.x=-1;

    Timer delta;
    delta.start();/**Start the delta timer.*/

    while(loop==true){
        input_dialog_message();
        if(confirm==true){
            confirm=false;
            /**Reset all of the dialog message strings.*/
            msg1="0";
            msg2="0";
            msg3="0";
            msg4="0";
            msg5="0";
            /**Reset the selection bar.*/
            b_select_menu.box.x=-1;
            return;
        }
        movement_other(delta.get_ticks());
        animation(delta.get_ticks());
        delta.start();/**Restart delta timer.*/
        draw_city();
        draw_dialog_message();
    }
}

/**Display a world dialog message.*/
void world_dialog_message(){
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,100);

    bool loop=true;
    /**Reset the selection bar.*/
    b_select_menu.box.x=-1;

    Timer delta;
    delta.start();/**Start the delta timer.*/

    while(loop==true){
        input_dialog_message();
        if(confirm==true){
            confirm=false;
            /**Reset all of the dialog message strings.*/
            msg1="0";
            msg2="0";
            msg3="0";
            msg4="0";
            msg5="0";
            /**Reset the selection bar.*/
            b_select_menu.box.x=-1;
            return;
        }
        movement_other(delta.get_ticks());
        animation(delta.get_ticks());
        delta.start();/**Restart delta timer.*/
        draw();
        draw_dialog_message();
    }
}

/**Display a found equipment dialog message.*/
void found_dialog_message(){
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,100);

    bool loop=true;
    /**Reset the selection bar.*/
    b_select_menu.box.x=-1;

    Timer delta;
    delta.start();/**Start the delta timer.*/

    while(loop==true){
        input_found_dialog_message();
        if(confirm==true){
            confirm=false;
            /**Reset all of the dialog message strings.*/
            msg1="0";
            msg2="0";
            msg3="0";
            msg4="0";
            msg5="0";
            /**Reset the selection bar.*/
            b_select_menu.box.x=-1;
            return;
        }
        movement_other(delta.get_ticks());
        animation(delta.get_ticks());
        delta.start();/**Restart delta timer.*/
        draw();
        draw_found_dialog_message();
    }
}

/**Display a moral dialog message.*/
void moral_dialog_message(){
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,100);

    bool loop=true;
    /**Reset the selection bar.*/
    b_select_menu.box.x=-1;

    Timer delta;
    delta.start();/**Start the delta timer.*/

    while(loop==true){
        input_moral_dialog();
        if(confirm==true){
            confirm=false;
            /**Reset all of the dialog message strings.*/
            msg1="0";
            msg2="0";
            msg3="0";
            msg4="0";
            msg5="0";
            /**Reset the selection bar.*/
            b_select_menu.box.x=-1;
            return;
        }
        if(re_moral==false){
            draw();
        }
        if(re_moral==true){
            draw_city();
        }
        movement_other(delta.get_ticks());
        animation(delta.get_ticks());
        delta.start();/**Restart delta timer.*/
        draw_moral_dialog();
    }
}
