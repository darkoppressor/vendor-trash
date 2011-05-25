/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include "input.h"
#include "variables.h"
#include "quit.h"
#include "buttons.h"
#include "sdl.h"
#include "screen_draw.h"
#include "menus.h"/**Some inputs call the various menus.*/
#include "city.h"/**Some inputs call city_screen().*/
#include "logic.h"/**Some inputs call hit_detection().*/
#include "main.h"/**Some inputs call game_loop().*/
#include "bank.h"
#include "stats.h"
#include "game.h"
#include "scores.h"
#include "random_number_generator.h"
#include "dialog.h"

#include "random_events.h"

using namespace std;

void input_global(){
    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    if((keystates[SDLK_LALT] || keystates[SDLK_RALT]) && (keystates[SDLK_RETURN])){
        keystates[SDLK_LALT]=NULL;
        keystates[SDLK_RALT]=NULL;
        keystates[SDLK_RETURN]=NULL;
        switch(fullscreen){
            case false:/**Off*/
            fullscreen=true;
            break;
            case true:/**On*/
            fullscreen=false;
            break;
        }
        if(fullscreen==false){
            screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);
            b_fullscreen.sprite=0;
        }
        if(fullscreen==true){
            screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE|SDL_FULLSCREEN);
            b_fullscreen.sprite=1;
        }
    }
}

void input_game(){
    input_global();
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
            quit_game();
            break;
        }
    }
    character.handle_input();
    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    /**Handle input.*/
    if(keystates[SDLK_ESCAPE]){
        keystates[SDLK_ESCAPE]=NULL;
        main_menu();
    }
    if(keystates[SDLK_RETURN] && !keystates[SDLK_LALT] && !keystates[SDLK_RALT]){
        keystates[SDLK_RETURN]=NULL;
        hit_detection();/**Check to see if the player is on a city. If so, hit_detection() will call the city screen for that city.*/
    }
    //if(keystates[SDLK_h]){
    //    keystates[SDLK_h]=NULL;
    //    option_dev=!option_dev;
    //}
}

void input_battle(){
    input_global();
    while(SDL_PollEvent(&event)){
        b_attack.handle_events();
        b_healthpotion.handle_events();
        b_flee.handle_events();
        switch(event.type){
            case SDL_QUIT:
            quit_game();
            break;
        }
    }
    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    if(keystates[SDLK_a] || (keystates[SDLK_RETURN] && !keystates[SDLK_LALT] && !keystates[SDLK_RALT])){
        keystates[SDLK_a]=NULL;
        keystates[SDLK_RETURN]=NULL;
        if(turn==true){/**If it is the player's turn.*/
            enemy_health-=random_range(1,3)+random_range((level*.5)+strength,(level*.5)+strength+(strength*.5))+equip_attack;
            turn=false;/**It's the enemy's turn.*/
        }
    }
    if(keystates[SDLK_d]){
        keystates[SDLK_d]=NULL;
        if(turn==true){/**If it is the player's turn.*/
            if(inv_healthpotions>0){/**If the player has at least one health potion.*/
                inv_healthpotions--;/**Use up one health potion.*/
                inventory--;
                health+=random_range(25,50);/**Restore a little health.*/
                if(health>health_max){/**If health exceeds health_max, set it to health_max.*/
                    health=health_max;
                }
                turn=false;/**It's the enemy's turn.*/
            }
            else{
                msg1="You have no health potions!";
                world_dialog_message();
            }
        }
    }
    if(keystates[SDLK_f]){
        keystates[SDLK_f]=NULL;
        if(turn==true){/**If it is the player's turn.*/
            int check=random_range(0,99);
            if(check>(89-(luck*1))){/**A base 10% chance that you will escape. Every 1 Luck point, this chance increases by 1%.*/
                msg1="You escaped the ";
                msg1+=enemy_name;
                msg1+="!";
                world_dialog_message();
                confirm=true;
            }
            else{/**If you failed to flee.*/
                msg1="You failed to flee the battle...";
                msg2="The ";
                msg2+=enemy_name;
                msg2+=" launches another attack!";
                world_dialog_message();
                turn=false;/**It's the enemy's turn.*/
            }
        }
    }
}

void input_city(){
    input_global();
    while(SDL_PollEvent(&event)){
        /**Handle item buy and sell "buttons":*/
        b_buy_weapons.handle_events();
        b_buy_armor.handle_events();
        b_buy_accessories.handle_events();
        b_buy_magicalitems.handle_events();
        b_buy_revives.handle_events();
        b_buy_manapotions.handle_events();
        b_buy_healthpotions.handle_events();
        b_buy_antidotes.handle_events();
        b_sell_weapons.handle_events();
        b_sell_armor.handle_events();
        b_sell_accessories.handle_events();
        b_sell_magicalitems.handle_events();
        b_sell_revives.handle_events();
        b_sell_manapotions.handle_events();
        b_sell_healthpotions.handle_events();
        b_sell_antidotes.handle_events();

        /**Handle other city buttons:*/
        b_bank.handle_events();
        b_travel.handle_events();
        b_stats.handle_events();
        b_menu.handle_events();

        switch(event.type){
            case SDL_QUIT:
            quit_game();
            break;
        }
    }
    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    if(keystates[SDLK_ESCAPE] || keystates[SDLK_m]){
        keystates[SDLK_ESCAPE]=NULL;
        keystates[SDLK_m]=NULL;
        main_menu();
    }
    if(keystates[SDLK_s]){
        keystates[SDLK_s]=NULL;
        current_city=0;
        game_loop();
    }
    if(keystates[SDLK_v]){
        keystates[SDLK_v]=NULL;
        bank();
    }
    if(keystates[SDLK_p]){
        keystates[SDLK_p]=NULL;
        stats();
    }
}

void input_menu(){
    input_global();
    while(SDL_PollEvent(&event)){
        if(game_in_progress==true){
            b_continue.handle_events();
        }
        b_newgame.handle_events();
        b_highscores.handle_events();
        b_options.handle_events();
        b_about.handle_events();
        b_quit.handle_events();
        switch(event.type){
            case SDL_QUIT:
            quit_game();
            break;
        }
    }
    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    if((keystates[SDLK_ESCAPE] && game_in_progress==false) || keystates[SDLK_q]){
        keystates[SDLK_ESCAPE]=NULL;
        keystates[SDLK_q]=NULL;
        quit_game();
    }
    else if((keystates[SDLK_ESCAPE] && game_in_progress==true) || (keystates[SDLK_c] && game_in_progress==true)){
        keystates[SDLK_ESCAPE]=NULL;
        keystates[SDLK_c]=NULL;
        game_loop();
    }
    if(keystates[SDLK_n]){
        keystates[SDLK_n]=NULL;
        new_game();
    }
    if(keystates[SDLK_o]){
        keystates[SDLK_o]=NULL;
        options();
    }
    if(keystates[SDLK_a]){
        keystates[SDLK_a]=NULL;
        about();
    }
    if(keystates[SDLK_h]){
        keystates[SDLK_h]=NULL;
        scores_display();
    }
}

void input_stats(){
    input_global();
    while(SDL_PollEvent(&event)){
        b_cart_size.handle_events();
        b_haggling.handle_events();
        b_banking.handle_events();
        b_strength.handle_events();
        b_stamina.handle_events();
        b_luck.handle_events();
        b_potion.handle_events();
        b_back.handle_events();
        switch(event.type){
            case SDL_QUIT:
            quit_game();
            break;
        }
    }
    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    if(keystates[SDLK_ESCAPE] || keystates[SDLK_b] || (keystates[SDLK_RETURN] && !keystates[SDLK_LALT] && !keystates[SDLK_RALT])){
        keystates[SDLK_ESCAPE]=NULL;
        keystates[SDLK_b]=NULL;
        keystates[SDLK_RETURN]=NULL;
        city_screen();
    }
    if(keystates[SDLK_d]){
        keystates[SDLK_d]=NULL;
        if(inv_healthpotions>0){/**If the player has at least one health potion.*/
            inv_healthpotions--;/**Use up one health potion.*/
            inventory--;
            health+=random_range(25,50);/**Restore a little health.*/
            if(health>health_max){/**If health exceeds health_max, set it to health_max.*/
                health=health_max;
            }
        }
        else{
            msg1="You have no health potions!";
            dialog_message();
            stats();
        }
    }
}

void input_bank(){
    input_global();
    while(SDL_PollEvent(&event)){
        b_deposit.handle_events();
        b_withdraw.handle_events();
        b_paydebt.handle_events();
        b_back_bank.handle_events();
        switch(event.type){
            case SDL_QUIT:
            quit_game();
            break;
        }
    }
    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    if(keystates[SDLK_ESCAPE] || keystates[SDLK_b] || (keystates[SDLK_RETURN] && !keystates[SDLK_LALT] && !keystates[SDLK_RALT])){
        keystates[SDLK_ESCAPE]=NULL;
        keystates[SDLK_b]=NULL;
        keystates[SDLK_RETURN]=NULL;
        city_screen();
    }
    if(keystates[SDLK_d]){
        keystates[SDLK_d]=NULL;
        bank_mode=1;
        bank_transaction();
    }
    if(keystates[SDLK_w]){
        keystates[SDLK_w]=NULL;
        bank_mode=2;
        bank_transaction();
    }
    if(keystates[SDLK_p]){
        keystates[SDLK_p]=NULL;
        bank_mode=3;
        bank_transaction();
    }
}

void input_bank_transaction(){
    input_global();
    while(SDL_PollEvent(&event)){
        b_ok.handle_events();
        b_cancel.handle_events();
        switch(event.type){
            case SDL_QUIT:
            quit_game();
            break;
            case SDL_MOUSEBUTTONDOWN:
            if(event.button.button==SDL_BUTTON_WHEELUP){
                if(bank_mode==1){/**If we are depositing money.*/
                    int trade_rate=1;
                    if((gold*.01)>=1){
                        trade_rate=gold*.01;
                    }
                    if(current_trade<gold)
                    current_trade+=trade_rate;
                    if(current_trade>gold)
                    current_trade=gold;
                }
                if(bank_mode==2){/**If we are withdrawing money.*/
                    int trade_rate=1;
                    if((savings*.01)>=1){
                        trade_rate=savings*.01;
                    }
                    if(current_trade<savings)
                    current_trade+=trade_rate;
                    if(current_trade>savings)
                    current_trade=savings;
                }
                if(bank_mode==3){/**If we are paying off debt.*/
                    if((current_trade<debt) && (current_trade<gold+savings))
                    current_trade+=10;
                    if(current_trade>debt)
                    current_trade=debt;
                    if(current_trade>gold+savings)
                    current_trade=gold+savings;
                }
            }
            if(event.button.button==SDL_BUTTON_WHEELDOWN){
                if(bank_mode==1){/**If we are depositing money.*/
                    int trade_rate=1;
                    if((gold*.01)>=1){
                        trade_rate=gold*.01;
                    }
                    if(current_trade>0)
                    current_trade-=trade_rate;
                    if(current_trade<0)
                    current_trade=0;
                }
                if(bank_mode==2){/**If we are withdrawing money.*/
                    int trade_rate=1;
                    if((savings*.01)>=1){
                        trade_rate=savings*.01;
                    }
                    if(current_trade>0)
                    current_trade-=trade_rate;
                    if(current_trade<0)
                    current_trade=0;
                }
                if(bank_mode==3){/**If we are paying off debt.*/
                    if(current_trade>0)
                    current_trade-=10;
                    if(current_trade<0)
                    current_trade=0;
                }
            }
            break;
        }
    }
    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    b_arrowup.handle_events();
    b_arrowdown.handle_events();
    if(keystates[SDLK_ESCAPE]){
        keystates[SDLK_ESCAPE]=NULL;
        bank_mode=0;
        bank();
    }
    if(keystates[SDLK_RETURN] && !keystates[SDLK_LALT] && !keystates[SDLK_RALT]){
        keystates[SDLK_RETURN]=NULL;
        confirm=true;
    }
}

void input_trade(){
    input_global();
    while(SDL_PollEvent(&event)){
        b_ok.handle_events();
        b_cancel.handle_events();
        switch(event.type){
            case SDL_QUIT:
            quit_game();
            break;
            case SDL_MOUSEBUTTONDOWN:
            if(event.button.button==SDL_BUTTON_WHEELUP){
                if(bank_mode==0){/**If we are on the buying/selling screen and not in the bank.*/
                    int trade_rate=1;
                    if((max_trade*.01)>=1){
                        trade_rate=max_trade*.01;
                    }
                    if(current_trade<max_trade)
                    current_trade+=trade_rate;
                    if(current_trade>max_trade)
                    current_trade=max_trade;
                }
            }
            if(event.button.button==SDL_BUTTON_WHEELDOWN){
                if(bank_mode==0){/**If we are on the buying/selling screen and not in the bank.*/
                    int trade_rate=1;
                    if((max_trade*.01)>=1){
                        trade_rate=max_trade*.01;
                    }
                    if(current_trade>0)
                    current_trade-=trade_rate;
                    if(current_trade<0)
                    current_trade=0;
                }
            }
            break;
        }
    }
    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    b_arrowdown.handle_events();
    b_arrowup.handle_events();
    if(keystates[SDLK_ESCAPE]){
        keystates[SDLK_ESCAPE]=NULL;
        city_screen();
    }
    if(keystates[SDLK_RETURN] && !keystates[SDLK_LALT] && !keystates[SDLK_RALT]){
        keystates[SDLK_RETURN]=NULL;
        confirm=true;
    }
}

void input_moral_dialog(){
    input_global();
    while(SDL_PollEvent(&event)){
        b_moral_good.handle_events();
        b_moral_neutral.handle_events();
        b_moral_bad.handle_events();
        switch(event.type){
            case SDL_QUIT:
            quit_game();
            break;
        }
    }
    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    /**Here we handle keyboard input. The numbers 1, 2, and 3 correspond to the good, neutral, and evil choice, respectively.*/
    if(keystates[SDLK_1]){
        keystates[SDLK_1]=NULL;
        if(good_vs_evil<=98){/**Don't let good_vs_evil exceed 100.*/
            good_vs_evil+=2;/**Add world moral points.*/
        }
        if(morality<=96){/**Don't let morality exceed 100.*/
            morality+=4;/**Add player moral points.*/
        }
        gold+=re_gold_good;
        if(gold<0){
            gold=0;
        }
        re_gold_good=0;
        re_gold_neutral=0;
        re_gold_bad=0;
        confirm=true;
    }
    if(keystates[SDLK_2]){
        keystates[SDLK_2]=NULL;
        /**Determine whether the world and player are good or evil, and bring them 1 or 2 moral points closer to neutrality, respectively.*/
        if(good_vs_evil<0){
            good_vs_evil+=1;
            morality+=2;
        }
        if(good_vs_evil>0){
            good_vs_evil-=1;
            morality-=2;
        }
        gold+=re_gold_neutral;
        if(gold<0){
            gold=0;
        }
        re_gold_good=0;
        re_gold_neutral=0;
        re_gold_bad=0;
        confirm=true;
    }
    if(keystates[SDLK_3]){
        keystates[SDLK_3]=NULL;
        if(good_vs_evil>=-98){/**Don't let good_vs_evil go below -100.*/
            good_vs_evil-=2;/**Subtract world moral points.*/
        }
        if(morality>=-96){/**Don't let morality go below -100.*/
            morality-=4;/**Subtract player moral points.*/
        }
        gold+=re_gold_bad;
        if(gold<0){
            gold=0;
        }
        re_gold_good=0;
        re_gold_neutral=0;
        re_gold_bad=0;
        confirm=true;
    }
}

void input_get_max_days(){
    input_global();
    while(SDL_PollEvent(&event)){
        b_days_1.handle_events();
        b_days_2.handle_events();
        b_days_3.handle_events();
        b_days_4.handle_events();
        b_days_5.handle_events();
        b_days_6.handle_events();
        switch(event.type){
            case SDL_QUIT:
            quit_game();
            break;
        }
    }
    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    if(keystates[SDLK_1]){
        keystates[SDLK_1]=NULL;
        days_max=25;
        confirm=true;
    }
    if(keystates[SDLK_2]){
        keystates[SDLK_2]=NULL;
        days_max=50;
        confirm=true;
    }
    if(keystates[SDLK_3]){
        keystates[SDLK_3]=NULL;
        days_max=75;
        confirm=true;
    }
    if(keystates[SDLK_4]){
        keystates[SDLK_4]=NULL;
        days_max=100;
        confirm=true;
    }
    if(keystates[SDLK_5]){
        keystates[SDLK_5]=NULL;
        days_max=150;
        confirm=true;
    }
    if(keystates[SDLK_6]){
        keystates[SDLK_6]=NULL;
        days_max=200;
        confirm=true;
    }
}

void input_dialog_message(){
    input_global();
    while(SDL_PollEvent(&event)){
        b_ok_dialog_message.handle_events();
        switch(event.type){
            case SDL_QUIT:
            quit_game();
            break;
        }
    }
    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    if(keystates[SDLK_ESCAPE]){
        keystates[SDLK_ESCAPE]=NULL;
        confirm=true;
    }
    if(keystates[SDLK_RETURN] && !keystates[SDLK_LALT] && !keystates[SDLK_RALT] && confirm==false){
        keystates[SDLK_RETURN]=NULL;
        confirm=true;
    }
}

void input_scores_display(){
    input_global();
    while(SDL_PollEvent(&event)){
        b_ok_dialog_message.handle_events();
        switch(event.type){
            case SDL_QUIT:
            quit_game();
            break;
        }
    }
    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    if((keystates[SDLK_RETURN] && !keystates[SDLK_LALT] && !keystates[SDLK_RALT] && confirm==false) || (keystates[SDLK_b] && confirm==false) || (keystates[SDLK_ESCAPE] && confirm==false)){
        keystates[SDLK_RETURN]=NULL;
        keystates[SDLK_b]=NULL;
        keystates[SDLK_ESCAPE]=NULL;
        /**Reset the selection bar.*/
        b_select_menu.box.x=-1;
        confirm=true;
    }
}

void input_get_name(){
    input_global();
    while(SDL_PollEvent(&event)){
        get_player_name.handle_events();
        b_ok_dialog_message.handle_events();
        switch(event.type){
            case SDL_QUIT:
            quit_game();
            break;
        }
    }
}

void input_found_dialog_message(){
    input_global();
    while(SDL_PollEvent(&event)){
        b_yes.handle_events();
        b_no.handle_events();
        switch(event.type){
            case SDL_QUIT:
            quit_game();
            break;
        }
    }
    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    if(keystates[SDLK_e]){
        keystates[SDLK_e]=NULL;
        if(equip_found<=4){/**If the found equipment is a weapon.*/
            if(equip_attack!=0){
                gold+=1+random_range(equip_attack*1.5,equip_attack*6);
            }
            equip_attack=equip_found_attack;
            weapon_name=equip_found_name;
        }
        if(equip_found>=5){/**If the found equipment is a piece of armor.*/
            if(equip_defense!=0){
                gold+=1+random_range(equip_defense*1.5,equip_defense*6);
            }
            equip_defense=equip_found_defense;
            armor_name=equip_found_name;
        }
        confirm=true;
    }
    if(keystates[SDLK_t]){
        keystates[SDLK_t]=NULL;
        if(equip_found_attack!=0){
            gold+=1+random_range(equip_found_attack*1.5,equip_found_attack*6);
        }
        if(equip_found_defense!=0){
            gold+=1+random_range(equip_found_defense*1.5,equip_found_defense*6);
        }
        confirm=true;
    }
}

void input_options(){
    input_global();
    while(SDL_PollEvent(&event)){
        b_fullscreen.handle_events();
        b_back.handle_events();
        switch(event.type){
            case SDL_QUIT:
            quit_game();
            break;
        }
    }
    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    if(keystates[SDLK_ESCAPE] || keystates[SDLK_b] || (keystates[SDLK_RETURN] && !keystates[SDLK_LALT] && !keystates[SDLK_RALT])){
        keystates[SDLK_ESCAPE]=NULL;/**Clear the escape keystate so the game doesn't exit when returning to the main menu.*/
        keystates[SDLK_b]=NULL;
        keystates[SDLK_RETURN]=NULL;
        main_menu();
    }
    if(keystates[SDLK_f]){
        keystates[SDLK_f]=NULL;
        switch(fullscreen){
            case false:/**Off*/
            fullscreen=true;
            break;
            case true:/**On*/
            fullscreen=false;
            break;
        }
        if(fullscreen==false){
            screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);
            b_fullscreen.sprite=0;
        }
        if(fullscreen==true){
            screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE|SDL_FULLSCREEN);
            b_fullscreen.sprite=1;
        }
    }
}

void input_about(){
    input_global();
    while(SDL_PollEvent(&event)){
        b_back.handle_events();
        switch(event.type){
            case SDL_QUIT:
            quit_game();
            break;
        }
    }
    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    if(keystates[SDLK_ESCAPE] || keystates[SDLK_b] || (keystates[SDLK_RETURN] && !keystates[SDLK_LALT] && !keystates[SDLK_RALT])){
        keystates[SDLK_ESCAPE]=NULL;
        keystates[SDLK_b]=NULL;
        keystates[SDLK_RETURN]=NULL;
        main_menu();
    }
}
