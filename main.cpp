/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include <SDL.h>/**Standard SDL stuff.*/
#include <SDL_mixer.h>/**SDL audio stuff.*/
#include <SDL_ttf.h>/**SDL true type font stuff.*/
#include <SDL_image.h>/**SDL graphics stuff.*/

#include "main.h"
#include "timer.h"
#include "sprites.h"
#include "variables.h"
#include "input.h"
#include "screen_draw.h"
#include "sdl.h"
#include "menus.h"
#include "city.h"
#include "logic.h"
#include "items.h"/**When a new city is entered, set_item_prices() is called.*/
#include "quit.h"
#include "options.h"
#include "dialog.h"
#include "game.h"

using namespace std;

void game_loop(){
    SDL_EnableKeyRepeat(1,0);
    bool loop=true;
    string temp_msg="";

    /**Reset the selection bar.*/
    b_select_menu.box.x=-1;

    Timer delta;
    delta.start();/**Start the delta timer.*/

    Timer timer_frame_rate;
    timer_frame_rate.start();

    Timer ticks;/**This timer calls tick() every 1 second that passes while traveling on the world map.*/
    ticks.start();

    while(loop==true){
        if(timer_frame_rate.get_ticks()>=1000){
            frame_rate=frame_count;
            frame_count=0;
            ms_per_frame=1000.0f/frame_rate;
            timer_frame_rate.start();
        }
        frame_count++;
        /**If the player is out of days, end the game.*/
        if(days>=days_max){
            msg1="It has been ";
            ss.clear();ss.str("");ss<<days_max;ss>>temp_msg;
            msg1+=temp_msg;
            msg1+=" days since you began your life as an item vendor.";
            msg2="Alas, your game is at an end, and this adventure must come to a close.";
            msg3="Over the course of your adventure, ";
            if((gold+savings-debt)<0){
                msg3+="you lost ";
                ss.clear();ss.str("");ss<<(gold+savings-(debt*1.5))*-1;ss>>temp_msg;
            }
            if((gold+savings-debt)>0){
                msg3+="you amassed ";
                ss.clear();ss.str("");ss<<gold+savings-(debt*1.5);ss>>temp_msg;
            }
            msg3+=temp_msg;
            msg3+=" gold.";
            msg4="You were level ";
            ss.clear();ss.str("");ss<<level;ss>>temp_msg;
            msg4+=temp_msg;
            msg4+=", and lived a ";
            if(morality<-10){/**If the player was evil.*/
                msg4+="terribly evil life.";
            }
            if(morality>10){/**If the player was good.*/
                msg4+="saintly life.";
            }
            if(morality>=-10 && morality<=10){/**If the player was neutral.*/
                msg4+="fair life.";
            }
            world_dialog_message();
            msg1="You made ";
            ss.clear();ss.str("");ss<<purchases;ss>>temp_msg;
            msg1+=temp_msg;
            if(purchases==1){
                msg1+=" purchase and ";
            }
            if(purchases!=1){
                msg1+=" purchases and ";
            }
            ss.clear();ss.str("");ss<<sales;ss>>temp_msg;
            msg1+=temp_msg;
            if(sales==1){
                msg1+=" sale.";
            }
            if(sales!=1){
                msg1+=" sales.";
            }
            msg2="You slew ";
            ss.clear();ss.str("");ss<<battles_won;ss>>temp_msg;
            msg2+=temp_msg;
            if(battles_won==1){
                msg2+=" foe and were slain ";
            }
            if(battles_won!=1){
                msg2+=" foes and were in turn slain ";
            }
            ss.clear();ss.str("");ss<<battles_lost;ss>>temp_msg;
            msg2+=temp_msg;
            if(battles_lost==1){
                msg2+=" time.";
            }
            if(battles_lost!=1){
                msg2+=" times.";
            }
            string player_title="";
            if(gold+savings-debt<=0){
                player_title="penniless pauper";
            }
            if(gold+savings-debt>=1 && gold+savings-debt<=10000){
                player_title="budding entrepreneur";
            }
            if(gold+savings-debt>=10001 && gold+savings-debt<=50000){
                player_title="successful businessman";
            }
            if(gold+savings-debt>=50001){
                player_title="rich, rich man";
            }
            msg3="You are retiring as a ";
            msg3+=player_title;
            msg3+=".";
            world_dialog_message();
            if(good_vs_evil<-10){/**If evil won in the world.*/
                msg1=world_evil;
                msg1+=" has defeated ";
                msg1+=world_hero;
                msg1+=", and succeeded in conquering ";
                msg1+=world_homeland;
                msg1+="!";
            }
            if(good_vs_evil>10){/**If good won in the world.*/
                msg1=world_hero;
                msg1+=" has defeated ";
                msg1+=world_evil;
                msg1+=", and saved ";
                msg1+=world_homeland;
                msg1+="!";
            }
            if(good_vs_evil>=-10 && good_vs_evil<=10){/**If neutral won in the world.*/
                msg1="The forces of ";
                msg1+=world_evil;
                msg1+=" have failed in conquering ";
                msg1+=world_homeland;
                msg1+=".";
                msg2="However, ";
                msg2+=world_hero;
                msg2+=" has been unable to defeat ";
                msg2+=world_evil;
                msg2+=".";
                msg3="The world remains at war.";
            }
            world_dialog_message();
            end_game();
        }

        /**If we are not on the overworld map, go to the city screen.*/
        if(current_city!=0){
            /**If the current city is different from the last one the player was in, the player has traveled to a new city, so generate new prices based on this city.*/
            if(current_city!=last_city){
                set_item_prices();
            }
            city_screen();
        }
        input_game();/**Handle input.*/
        if(ticks.get_ticks()>=1000){
        tick();
        ticks.start();
        }
        movement(delta.get_ticks());
        animation(delta.get_ticks());
        delta.start();/**Restart delta timer.*/
        draw();/**Render the screen.*/
        SDL_Flip(screen);/**SDL_Flip() must be called here instead of in draw(). See screen_draw.h for more information.*/
    }
}

int main(int argc, char* args[]){/**We want to use main this way because SDL doesn't like other ways of using main.*/
    /**The following two lines seed the random number generator.*/
    time_t seconds;
    rng.mrand_main.seed((uint32_t)time(&seconds));
    /**Clip sprite sheets.*/
    sprite_sheet_clouds();
    sprite_sheet_player();
    sprite_sheet_arrows();
    sprite_sheet_options();
    sprite_sheet_stats();
    sprite_sheet_waves();
    sprite_sheet_lighthouse();
    /**Load options from options.cfg.*/
    if(options_load()==false){
        return 1;
    }
    /**Initiation of SDL stuff.*/
    if(init()==false){
        return 1;
    }
    if(load_files()==false){
        return 1;
    }
    main_menu();
    quit_game();
    return 0;
}
