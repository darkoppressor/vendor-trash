/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include "sdl.h"
#include "buttons.h"
#include "main.h"/**We have buttons that start up game_loop().*/
#include "menus.h"/**We have buttons that call the various menus.*/
#include "items.h"/**We have buttons that call the item trading dialogs.*/
#include "city.h"/**We have buttons that call city_screen().*/
#include "variables.h"
#include "quit.h"
#include "game.h"
#include "bank.h"/**We have buttons that call bank().*/
#include "stats.h"/**We have buttons that call stats().*/
#include "random_number_generator.h"
#include "dialog.h"
#include "scores.h"

using namespace std;

Selection_Menu::Selection_Menu(int x,int y,int w,int h){
    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;
}

Selection_Item::Selection_Item(int x,int y,int w,int h){
    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;
}

Menu_Button::Menu_Button(int x,int y,int w,int h,int which_button){
    /**Set the button's attributes.*/
    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;
    button=which_button;
}

Battle_Button::Battle_Button(int x,int y,int w,int h,int which_button){
    /**Set the button's attributes.*/
    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;
    button=which_button;
}

Options_Button::Options_Button(int x,int y,int w,int h, int which_sprite){
    /**Set the button's attributes.*/
    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;
    sprite=which_sprite;
    /**Set the default sprite.*/
    clip=&clip_options_items[sprite];
}

Item_Button::Item_Button(int x,int y,int w,int h,int which_item){
    /**Set the button's attributes.*/
    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;
    item=which_item;
}

Bank_Button::Bank_Button(int x,int y,int w,int h, int which_button){
    /**Set the button's attributes.*/
    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;
    button=which_button;
}

Arrow_Button::Arrow_Button(int x,int y,int w,int h, int which_sprite){
    /**Set the button's attributes.*/
    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;
    sprite=which_sprite;
    /**Set the default sprite.*/
    clip=&clip_arrows[sprite];
}

Dialog_Button::Dialog_Button(int x,int y,int w,int h,int which_button){
    /**Set the button's attributes.*/
    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;
    button=which_button;
}

Found_Button::Found_Button(int x,int y,int w,int h,int which_button){
    /**Set the button's attributes.*/
    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;
    button=which_button;
}

Moral_Button::Moral_Button(int x,int y,int w,int h,int which_choice){
    /**Set the button's attributes.*/
    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;
    choice=which_choice;
}

Days_Button::Days_Button(int x,int y,int w,int h,int which_choice){
    /**Set the button's attributes.*/
    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;
    choice=which_choice;
}

City_Button::City_Button(int x,int y,int w,int h, int which_button){
    /**Set the button's attributes.*/
    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;
    button=which_button;
}

Stats_Button::Stats_Button(int x,int y,int w,int h, int which_sprite, int which_skill){
    /**Set the button's attributes.*/
    box.x=x;
    box.y=y;
    box.w=w;
    box.h=h;
    sprite=which_sprite;
    skill=which_skill;
    /**Set the default sprite.*/
    clip=&clip_stats_items[sprite];
}

void Menu_Button::handle_events(){
    /**The mouse offsets.*/
    int x=0,y=0;

    if(event.type==SDL_MOUSEBUTTONUP){
        if(event.button.button==SDL_BUTTON_LEFT){
            SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
            if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
                /**Do a menu event.*/
                switch(button){
                    case 5:/**Continue*/
                    game_loop();
                    break;
                    case 0:/**New Game*/
                    new_game();
                    break;
                    case 6:/**High Scores*/
                    scores_display();
                    break;
                    case 1:/**Options*/
                    options();
                    break;
                    case 2:/**About*/
                    about();
                    break;
                    case 3:/**Quit*/
                    quit_game();
                    break;
                    case 4:/**Back*/
                    menu_back();
                    break;
                }
            }
        }
    }
    else{/**If the left mouse button is not pressed.*/
        SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
        if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
            /**Set the selection bars to this button.*/
            b_select_menu.box.x=box.x;
            b_select_menu.box.y=box.y;
        }
    }
}

void Battle_Button::handle_events(){
    /**The mouse offsets.*/
    int x=0,y=0;
    int check=0;/**May be used to determine if the player succeeds in fleeing.*/

    if(event.type==SDL_MOUSEBUTTONUP){
        if(event.button.button==SDL_BUTTON_LEFT){
            SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
            if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
                /**Do a menu event.*/
                switch(button){
                    case 0:/**Attack*/
                    if(turn==true){/**If it is the player's turn.*/
                        enemy_health-=random_range(1,3)+random_range((level*.5)+strength,(level*.5)+strength+(strength*.5))+equip_attack;
                        turn=false;/**It's the enemy's turn.*/
                    }
                    break;
                    case 1:/**Health Potion*/
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
                    break;
                    case 2:/**Flee*/
                    if(turn==true){/**If it is the player's turn.*/
                    check=random_range(0,99);
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
                    break;
                }
            }
        }
    }
    else{/**If the left mouse button is not pressed.*/
        SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
        if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
            /**Set the selection bars to this button.*/
            b_select_menu.box.x=box.x;
            b_select_menu.box.y=box.y;
        }
    }
}

void Options_Button::handle_events(){
    /**The mouse offsets.*/
    int x=0,y=0;

    if(event.type==SDL_MOUSEBUTTONUP){
        if(event.button.button==SDL_BUTTON_LEFT){
            SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
            if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
                /**Do a menu event.*/
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
                    sprite=0;
                }
                if(fullscreen==true){
                    screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE|SDL_FULLSCREEN);
                    sprite=1;
                }
            }
        }
    }
}

void Item_Button::handle_events(){
    /**The mouse offsets.*/
    int x=0,y=0;

    if(event.type==SDL_MOUSEBUTTONUP){
        if(event.button.button==SDL_BUTTON_LEFT){
            SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
            if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
                /**Do a menu event.*/
                if(item<=7){/**If we click on a buy button.*/
                    trading=item;/**Tell the game what item we are buying.*/
                    buy_items();/**Pop up the item buying dialog.*/
                }
                if(item>7){/**If we click on a sell button.*/
                    trading=item;/**Tell the game what item we are selling.*/
                    sell_items();/**Pop up the item selling dialog.*/
                }
            }
        }
    }
    else{/**If the left mouse button is not pressed.*/
        SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
        if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
            /**Set the selection bars to this button.*/
            b_select_item.box.x=box.x;
            b_select_item.box.y=box.y;
            /**Turn off the menu item selection bar.*/
            b_select_menu.box.x=-1;
        }
    }
}

void Bank_Button::handle_events(){
    /**The mouse offsets.*/
    int x=0,y=0;

    if(event.type==SDL_MOUSEBUTTONUP){
        if(event.button.button==SDL_BUTTON_LEFT){
            SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
            if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
                /**Do a menu event.*/
                switch(button){
                    case 0:/**Deposit*/
                    bank_mode=1;
                    bank_transaction();
                    break;
                    case 1:/**Withdraw*/
                    bank_mode=2;
                    bank_transaction();
                    break;
                    case 2:/**Pay Debt*/
                    bank_mode=3;
                    bank_transaction();
                    break;
                    case 3:/**Back*/
                    city_screen();
                    break;
                }
            }
        }
    }
    else{/**If the left mouse button is not pressed.*/
        SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
        if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
            /**Set the selection bars to this button.*/
            b_select_menu.box.x=box.x;
            b_select_menu.box.y=box.y;
        }
    }
}

void Arrow_Button::handle_events(){
    /**The mouse offsets.*/
    int x=0,y=0;

    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    /**Handle input.*/
    //Pressing up raises the number by 1.
    if(keystates[SDLK_UP]){
        keystates[SDLK_UP]=NULL;
        if(bank_mode==0){/**If we are on the buying/selling screen and not in the bank.*/
            if(current_trade<max_trade)
            current_trade++;
        }
        if(bank_mode==1){/**If we are depositing money.*/
            if(current_trade<gold)
            current_trade++;
        }
        if(bank_mode==2){/**If we are withdrawing money.*/
            if(current_trade<savings)
            current_trade++;
        }
        if(bank_mode==3){/**If we are paying off debt.*/
            if((current_trade<debt) && (current_trade<gold+savings))
            current_trade++;
        }
    }
    //Holding right raises the number by .1 percent of the maximum number.
    if(keystates[SDLK_RIGHT]){
        if(bank_mode==0){/**If we are on the buying/selling screen and not in the bank.*/
            int trade_rate=1;
            if((max_trade*.001)>=1){
                trade_rate=max_trade*.001;
            }
            if(current_trade<max_trade)
            current_trade+=trade_rate;
            if(current_trade>max_trade)
            current_trade=max_trade;
        }
        if(bank_mode==1){/**If we are depositing money.*/
            int trade_rate=1;
            if((gold*.001)>=1){
                trade_rate=gold*.001;
            }
            if(current_trade<gold)
            current_trade+=trade_rate;
            if(current_trade>gold)
            current_trade=gold;
        }
        if(bank_mode==2){/**If we are withdrawing money.*/
            int trade_rate=1;
            if((savings*.001)>=1){
                trade_rate=savings*.001;
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
    //Pressing down lowers the number by 1.
    if(keystates[SDLK_DOWN]){
        keystates[SDLK_DOWN]=NULL;
        if(bank_mode==0){/**If we are on the buying/selling screen and not in the bank.*/
            if(current_trade>0)
            current_trade--;
        }
        if(bank_mode==1){/**If we are depositing money.*/
            if(current_trade>0)
            current_trade--;
        }
        if(bank_mode==2){/**If we are withdrawing money.*/
            if(current_trade>0)
            current_trade--;
        }
        if(bank_mode==3){/**If we are paying off debt.*/
            if(current_trade>0)
            current_trade--;
        }
    }
    //Holding down lowers the number by .1 percent of the maximum.
    if(keystates[SDLK_LEFT]){
        if(bank_mode==0){/**If we are on the buying/selling screen and not in the bank.*/
            int trade_rate=1;
            if((max_trade*.001)>=1){
                trade_rate=max_trade*.001;
            }
            if(current_trade>0)
            current_trade-=trade_rate;
            if(current_trade<0)
            current_trade=0;
        }
        if(bank_mode==1){/**If we are depositing money.*/
            int trade_rate=1;
            if((gold*.001)>=1){
                trade_rate=gold*.001;
            }
            if(current_trade>0)
            current_trade-=trade_rate;
            if(current_trade<0)
            current_trade=0;
        }
        if(bank_mode==2){/**If we are withdrawing money.*/
            int trade_rate=1;
            if((savings*.001)>=1){
                trade_rate=savings*.001;
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

    if(SDL_GetMouseState(NULL,NULL)&SDL_BUTTON(SDL_BUTTON_LEFT)){
            SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
            if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
                /**Do a menu event.*/
                if(bank_mode==0){/**If we are on the buying/selling screen and not in the bank.*/
                    switch(sprite){
                    case 0:/**Up Arrow*/
                    if(current_trade<max_trade)
                    current_trade++;
                    break;
                    case 2:/**Down Arrow*/
                    if(current_trade>0)
                    current_trade--;
                    break;
                    }
                }
                if(bank_mode==1){/**If we are depositing money.*/
                    switch(sprite){
                    case 0:/**Up Arrow*/
                    if(current_trade<gold)
                    current_trade++;
                    break;
                    case 2:/**Down Arrow*/
                    if(current_trade>0)
                    current_trade--;
                    break;
                    }
                }
                if(bank_mode==2){/**If we are withdrawing money.*/
                    switch(sprite){
                    case 0:/**Up Arrow*/
                    if(current_trade<savings)
                    current_trade++;
                    break;
                    case 2:/**Down Arrow*/
                    if(current_trade>0)
                    current_trade--;
                    break;
                    }
                }
                if(bank_mode==3){/**If we are paying off debt.*/
                    switch(sprite){
                    case 0:/**Up Arrow*/
                    if((current_trade<debt) && (current_trade<gold+savings))
                    current_trade++;
                    break;
                    case 2:/**Down Arrow*/
                    if(current_trade>0)
                    current_trade--;
                    break;
                    }
                }
            }
    }
    else{/**If the left mouse button has not been pressed.*/
        SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
        if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
            /**Set the button sprite.*/
            clip=&clip_arrows[sprite+1];
        }
        else{/**If the mouse is not over the button.*/
            /**Set the button sprite.*/
            clip=&clip_arrows[sprite];
        }
    }
}

void Dialog_Button::handle_events(){
    /**The mouse offsets.*/
    int x=0,y=0;

    if(event.type==SDL_MOUSEBUTTONUP){
        if(event.button.button==SDL_BUTTON_LEFT){
            SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
            if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
                /**Do a menu event.*/
                switch(button){
                    case 0:/**OK*/
                    confirm=true;
                    b_select_menu.box.x=-1;
                    break;
                    case 1:/**Cancel*/
                    if(bank_mode==0)/**If we are not in the bank.*/
                    city_screen();
                    if(bank_mode!=0){/**If we are in the bank.*/
                        bank_mode=0;/**This needs to be 0 so I can reuse the Dialog_Buttons for the bank transactions.*/
                        bank();
                    }
                    break;
                }
            }
        }
    }
    else{/**If the left mouse button is not pressed.*/
        SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
        if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
            /**Set the selection bars to this button.*/
            b_select_menu.box.x=box.x;
            b_select_menu.box.y=box.y;
        }
    }
}

void Found_Button::handle_events(){
    /**The mouse offsets.*/
    int x=0,y=0;

    if(event.type==SDL_MOUSEBUTTONUP){
        if(event.button.button==SDL_BUTTON_LEFT){
            SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
            if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
                /**Do a menu event.*/
                switch(button){
                    case 0:/**Equip it*/
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
                    break;
                    case 1:/**Sell it*/
                    if(equip_found_attack!=0){
                        gold+=1+random_range(equip_found_attack*1.5,equip_found_attack*6);
                    }
                    if(equip_found_defense!=0){
                        gold+=1+random_range(equip_found_defense*1.5,equip_found_defense*6);
                    }
                    confirm=true;
                    break;
                }
            }
        }
    }
    else{/**If the left mouse button is not pressed.*/
        SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
        if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
            /**Set the selection bars to this button.*/
            b_select_menu.box.x=box.x;
            b_select_menu.box.y=box.y;
        }
    }
}

void Moral_Button::handle_events(){
    /**The mouse offsets.*/
    int x=0,y=0;

    if(event.type==SDL_MOUSEBUTTONUP){
        if(event.button.button==SDL_BUTTON_LEFT){
            SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
            if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
                /**Do a menu event.*/
                switch(choice){
                    case 0:/**Good choice*/
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
                    break;
                    case 1:/**Neutral choice*/
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
                    break;
                    case 2:/**Evil choice*/
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
                    break;
                }
            }
        }
    }
}

void Days_Button::handle_events(){
    /**The mouse offsets.*/
    int x=0,y=0;

    if(event.type==SDL_MOUSEBUTTONUP){
        if(event.button.button==SDL_BUTTON_LEFT){
            SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
            if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
                /**Do a menu event.*/
                switch(choice){
                    case 0:
                    days_max=25;
                    confirm=true;
                    break;
                    case 1:
                    days_max=50;
                    confirm=true;
                    break;
                    case 2:
                    days_max=75;
                    confirm=true;
                    break;
                    case 3:
                    days_max=100;
                    confirm=true;
                    break;
                    case 4:
                    days_max=150;
                    confirm=true;
                    break;
                    case 5:
                    days_max=200;
                    confirm=true;
                    break;
                }
            }
        }
    }
}

void City_Button::handle_events(){
    /**The mouse offsets.*/
    int x=0,y=0;

    if(event.type==SDL_MOUSEBUTTONUP){
        if(event.button.button==SDL_BUTTON_LEFT){
            SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
            if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
                /**Do a menu event.*/
                switch(button){
                    case 0:/**Bank*/
                    bank();
                    break;
                    case 1:/**Travel*/
                    current_city=0;
                    game_loop();
                    break;
                    case 2:/**Stats*/
                    stats();
                    break;
                    case 3:/**Menu*/
                    main_menu();
                    break;
                }
            }
        }
    }
    else{/**If the left mouse button is not pressed.*/
        SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
        if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
            /**Set the selection bars to this button.*/
            b_select_menu.box.x=box.x;
            b_select_menu.box.y=box.y;
            /**Turn off the item selection bar.*/
            b_select_item.box.x=-1;
        }
    }
}

void Stats_Button::handle_events(){
    /**The mouse offsets.*/
    int x=0,y=0;

    if(event.type==SDL_MOUSEBUTTONUP){
        if(event.button.button==SDL_BUTTON_LEFT){
            SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
            if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h)){/**If the mouse is currently over the button.*/
                /**Do a menu event.*/
                if(skill_points>0){
                switch(skill){
                        case 0:/**Cart Size*/
                        if(cart_size<200){
                        skill_points--;
                        cart_size++;
                        inventory_max+=5;
                        }
                        break;
                        case 1:/**Haggling*/
                        if(haggling<200){
                        skill_points--;
                        haggling++;
                        }
                        break;
                        case 2:/**Banking*/
                        if(banking<200){
                        skill_points--;
                        banking++;
                        }
                        break;
                        case 3:/**Strength*/
                        if(strength<200){
                        skill_points--;
                        strength++;
                        }
                        break;
                        case 4:/**Stamina*/
                        if(stamina<200){
                        skill_points--;
                        stamina++;
                        }
                        break;
                        case 5:/**Luck*/
                        if(luck<200){
                        skill_points--;
                        luck++;
                        }
                        break;
                }
                }
                if(skill==6){/**Health Potion Button*/
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
        }
    }
    else{/**If the left mouse button is not pressed.*/
        SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/
        if((x>box.x) && (x<box.x+box.w) && (y>box.y) && (y<box.y+box.h) && skill==6){/**If the mouse is currently over the button.*/
            /**Set the selection bars to this button.*/
            b_select_menu.box.x=box.x;
            b_select_menu.box.y=box.y;
        }
    }
}

void Selection_Menu::show(){
    if(box.x>-1){/**As long as the selection bar is set to a button, display it.*/
        apply_surface(box.x,box.y,select_menu,screen,NULL,0);/**Show the selection bar.*/
    }
}

void Selection_Item::show(){
    if(box.x>-1){/**As long as the selection bar is set to a button, display it.*/
        apply_surface(box.x,box.y,select_item,screen,NULL,0);/**Show the selection bar.*/
    }
}

void Options_Button::show(){
    clip=&clip_options_items[sprite];/**This needs to be here so that the options buttons have the right colors even when the game has just started.*/
    apply_surface(box.x,box.y,options_items,screen,clip,0);/**Show the button.*/
}

void Arrow_Button::show(){
    apply_surface(box.x,box.y,arrows,screen,clip,0);/**Show the button.*/
}

void Moral_Button::show(){
    apply_surface(box.x,box.y,moral_choice,screen,NULL,0);/**Show the button.*/
}

void Stats_Button::show(){
    if(skill_points==0){
        sprite=0;
    }
    if(skill_points>0){/**If the player has skill points, and the associated skill is not maxed, light the button up. If the skill is maxed, make sure the button is off.*/
        switch(skill){
            case 0:/**Cart Size*/
            if(cart_size<200){
                sprite=1;
            }
            else{
                sprite=0;
            }
            break;
            case 1:/**Haggling*/
            if(haggling<200){
                sprite=1;
            }
            else{
                sprite=0;
            }
            break;
            case 2:/**Banking*/
            if(banking<200){
                sprite=1;
            }
            else{
                sprite=0;
            }
            break;
            case 3:/**Strength*/
            if(strength<200){
                sprite=1;
            }
            else{
                sprite=0;
            }
            break;
            case 4:/**Stamina*/
            if(stamina<200){
                sprite=1;
            }
            else{
                sprite=0;
            }
            break;
            case 5:/**Luck*/
            if(luck<200){
                sprite=1;
            }
            else{
                sprite=0;
            }
            break;
        }
    }
    clip=&clip_stats_items[sprite];
    if(skill!=6){/**Show all buttons except for the drinking health potion one.*/
        apply_surface(box.x,box.y,stats_items,screen,clip,0);/**Show the button.*/
    }
}
