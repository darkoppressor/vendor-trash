/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include "bank.h"
#include "sdl.h"
#include "input.h"
#include "variables.h"
#include "screen_draw.h"
#include "logic.h"

using namespace std;

/**interest() is called whenever a day passes in the game.*/
void interest(){
    /**Calculate 1% interest of current savings and add it to savings. Then, calculate .2% interest * the player's Banking skill, and add this to savings as well.*/
    savings+=(savings*.01)+(savings*(.002*banking));

    /**Debt accrues interest at a rate of .2% per day.*/
    debt+=debt*.002;
}

void bank(){
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,100);
    bool loop=true;
    /**Reset the selection bar.*/
    b_select_menu.box.x=-1;

    Timer delta;
    delta.start();/**Start the delta timer.*/

    while(loop==true){
        input_bank();

        movement_other(delta.get_ticks());
        animation(delta.get_ticks());
        delta.start();/**Restart delta timer.*/

        draw_city();/**Draw the city screen in the background.*/
        draw_dialog_bank();/**Draw the bank dialog box:*/
    }
}

void bank_transaction(){
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,100);
    bool loop=true;
    /**Reset the selection bar.*/
    b_select_menu.box.x=-1;

    Timer delta;
    delta.start();/**Start the delta timer.*/

    if(bank_mode==1)
    current_trade=gold;
    if(bank_mode==2)
    current_trade=savings;
    if(bank_mode==3){
        if(debt<gold+savings){
            current_trade=debt;
        }
        else{
            current_trade=gold+savings;
        }
    }

    while(loop==true){
        input_bank_transaction();
        if(confirm==true){
            confirm=false;

            if(bank_mode==1){
                savings+=current_trade;/**Deposit the gold.*/
                gold-=current_trade;/**Subtract the amount of gold being deposited.*/
            }
            if(bank_mode==2){
                savings-=current_trade;/**Subtract the amount of gold being withdrawn.*/
                gold+=current_trade;/**Withdraw the gold.*/
            }
            if(bank_mode==3){
                if(debt<gold){
                    gold-=current_trade;/**Subtract the amount of gold.*/
                    debt-=current_trade;/**Pay off the debt.*/
                }
                else{
                    debt-=current_trade-gold;
                    savings-=current_trade-gold;
                    debt-=gold;
                    gold=0;
                }
            }

            bank_mode=0;/**This needs to be 0 so I can reuse the Dialog_Buttons for the bank transactions. See Dialog_Button::handle_events().*/
            bank();
        }

        movement_other(delta.get_ticks());
        animation(delta.get_ticks());
        delta.start();/**Restart delta timer.*/
        draw_city();
        draw_dialog_bank_transaction();
    }
}
