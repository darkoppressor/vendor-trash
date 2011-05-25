/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include <SDL.h>

#include "city.h"
#include "variables.h"
#include "input.h"
#include "screen_draw.h"
#include "sdl.h"
#include "logic.h"
#include "random_events.h"

using namespace std;

void city_screen(){
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,100);
    bool loop=true;
    /**Reset the selection bar.*/
    b_select_menu.box.x=-1;

    Timer delta;
    delta.start();/**Start the delta timer.*/

    while(loop==true){
        /**Set the player's home coordinates:*/
        home_x=character.x;
        home_y=character.y;

        last_city=current_city;

        /**Set city name:*/
        if(city[current_city]==1){
            city_name="Faeor";
        }
        if(city[current_city]==2){
            city_name="Tathar Unque";
        }
        if(city[current_city]==3){
            city_name="Adan Edhel'Dwar";
        }
        if(city[current_city]==4){
            city_name="Linna";
        }
        if(city[current_city]==5){
            city_name="Torden";
        }
        if(city[current_city]==6){
            city_name="Thanmar";
        }
        if(city[current_city]==7){
            city_name="Aegeria";
        }
        if(city[current_city]==8){
            city_name="Ened'Ost";
        }
        if(city[current_city]==9){
            city_name="Aear'Ost";
        }
        if(city[current_city]==10){
            city_name="Melkor";
        }
        if(city[current_city]==11){
            city_name="Kiinai";
        }
        if(city[current_city]==12){
            city_name="Dunelm";
        }
        if(city[current_city]==13){
            city_name="Thanarnorn";
        }
        if(city[current_city]==14){
            city_name="Naenyr";
        }
        if(city[current_city]==15){
            city_name="Ketlar";
        }
        if(city[current_city]==16){
            city_name="Vanwa Tol";
        }
        if(city[current_city]==17){
            city_name="Amar En Ar'Gwaith";
        }
        if(city[current_city]==18){
            city_name="Isca";
        }
        if(city[current_city]==19){
            city_name="Midgard";
        }
        if(city[current_city]==20){
            city_name="Magauraun";
        }
        if(city[current_city]==21){
            city_name="Tor-Telormar";
        }
        input_city();
        movement_other(delta.get_ticks());
        animation(delta.get_ticks());
        delta.start();/**Restart delta timer.*/
        draw();
        draw_city();
        SDL_Flip(screen);/**SDL_Flip() must be called here instead of in draw_city(). See screen_draw.h for more information.*/

        events_city();/**If any random city events have occurred, display their messages now. The actual random event check occurs in set_item_prices().*/
    }
}

City::City(int x,int y,int make_city){
    /**Set the city's location.*/
    hitbox.x=x;
    hitbox.y=y;

    /**Set the hitbox's dimensions.*/
    hitbox.w=30;
    hitbox.h=30;

    which_city=make_city;
}

void City::show(){
    if(city[which_city]>=1 && city[which_city]<=6)
    apply_surface((int)hitbox.x,(int)hitbox.y,city_icon_small,screen,NULL,0);
    if(city[which_city]>=7 && city[which_city]<=15)
    apply_surface((int)hitbox.x,(int)hitbox.y,city_icon_medium,screen,NULL,0);
    if(city[which_city]>=16 && city[which_city]<=21)
    apply_surface((int)hitbox.x,(int)hitbox.y,city_icon_large,screen,NULL,0);
}
