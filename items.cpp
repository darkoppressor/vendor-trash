/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include "items.h"
#include "input.h"
#include "variables.h"
#include "quit.h"
#include "city.h"
#include "sdl.h"
#include "random_number_generator.h"
#include "screen_draw.h"
#include "dialog.h"
#include "random_events.h"

using namespace std;

void buy_items(){
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,100);

    bool loop=true;

    /**Set current_item_price to price of current item:*/
    if(trading==0){
        current_item_price=price_weapons;
        item_name="weapons";
    }
    if(trading==1){
        current_item_price=price_armor;
        item_name="armor";
    }
    if(trading==2){
        current_item_price=price_accessories;
        item_name="accessories";
    }
    if(trading==3){
        current_item_price=price_magicalitems;
        item_name="magical items";
    }
    if(trading==4){
        current_item_price=price_revives;
        item_name="revives";
    }
    if(trading==5){
        current_item_price=price_manapotions;
        item_name="mana potions";
    }
    if(trading==6){
        current_item_price=price_healthpotions;
        item_name="health potions";
    }
    if(trading==7){
        current_item_price=price_antidotes;
        item_name="antidotes";
    }

    /**If the item is not currently being traded, don't allow any transaction and display a dialog telling the player about this.*/
    if(current_item_price==0){
        msg1=city_name;
        msg1+=" is not currently trading in ";
        msg1+=item_name;
        msg1+=".";
        dialog_message();
        return;
    }

    /**Determine max price of current item:*/
    max_trade=inventory_max-inventory;
    for(long temp_price=max_trade*current_item_price;temp_price>gold+savings && max_trade>0;){
        max_trade--;
        temp_price=max_trade*current_item_price;
    }

    /**Set the starting purchase amount to the max purchasable amount:*/
    current_trade=max_trade;

    while(loop==true){
        input_trade();

        if(confirm==true){
            purchases++;
            confirm=false;
            /**Buy the items:*/
            if(trading==0)
                inv_weapons+=current_trade;/**Add the purchased items to the proper inventory slot.*/
            if(trading==1)
                inv_armor+=current_trade;
            if(trading==2)
                inv_accessories+=current_trade;
            if(trading==3)
                inv_magicalitems+=current_trade;
            if(trading==4)
                inv_revives+=current_trade;
            if(trading==5)
                inv_manapotions+=current_trade;
            if(trading==6)
                inv_healthpotions+=current_trade;
            if(trading==7)
                inv_antidotes+=current_trade;

            inventory+=current_trade;/**Add the traded items to inventory weight.*/

            /**Subtract the cost from gold first, then savings if gold is depleted.*/
            for(long temp_cost=current_trade*current_item_price;temp_cost>0;){
                if(gold>0){
                    gold--;
                    temp_cost--;
                }
                if(gold==0){
                    savings--;
                    temp_cost--;
                }
            }

            /**If the Haggling skill is 1 or higher, make a check to see if some gold should be added.*/
            int haggle_check=random_range(0,99);/**Used to do a random chance check for a Haggling bonus.*/
            /**A base 10% chance that the player will receive a Haggle bonus. Every 1 Haggle point, this chance increases by 1%. At least one Haggle point is needed.*/
            if(haggling>0 && haggle_check>(89-(haggling*1))){
                /**If the check is successful, give the player some bonus gold, determined by their Haggling skill.*/
                gold+=random_range(haggling*1,haggling*5);
            }

            city_screen();
        }
        draw_city();
        draw_dialog_buy_items();
    }
}

void sell_items(){
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,100);

    bool loop=true;

    /**Set current_item_price to price of current item and max_trade to current owned amount of item:*/
    if(trading==8){
        max_trade=inv_weapons;
        current_item_price=price_weapons;
        item_name="weapons";
    }
    if(trading==9){
        max_trade=inv_armor;
        current_item_price=price_armor;
        item_name="armor";
    }
    if(trading==10){
        max_trade=inv_accessories;
        current_item_price=price_accessories;
        item_name="accessories";
    }
    if(trading==11){
        max_trade=inv_magicalitems;
        current_item_price=price_magicalitems;
        item_name="magical items";
    }
    if(trading==12){
        max_trade=inv_revives;
        current_item_price=price_revives;
        item_name="revives";
    }
    if(trading==13){
        max_trade=inv_manapotions;
        current_item_price=price_manapotions;
        item_name="mana potions";
    }
    if(trading==14){
        max_trade=inv_healthpotions;
        current_item_price=price_healthpotions;
        item_name="health potions";
    }
    if(trading==15){
        max_trade=inv_antidotes;
        current_item_price=price_antidotes;
        item_name="antidotes";
    }

    /**If the item is not currently being traded, don't allow any transaction and display a dialog telling the player about this.*/
    if(current_item_price==0){
        msg1=city_name;
        msg1+=" is not currently trading in ";
        msg1+=item_name;
        msg1+=".";
        dialog_message();
        return;
    }

    /**Set the starting sell amount to the max sellable amount:*/
    current_trade=max_trade;

    while(loop==true){
        input_trade();

        if(confirm==true){
            sales++;
            confirm=false;
            /**Sell the items:*/
            if(trading==8)
                inv_weapons-=current_trade;/**Subtract the traded items from the current items' spot.*/
            if(trading==9)
                inv_armor-=current_trade;
            if(trading==10)
                inv_accessories-=current_trade;
            if(trading==11)
                inv_magicalitems-=current_trade;
            if(trading==12)
                inv_revives-=current_trade;
            if(trading==13)
                inv_manapotions-=current_trade;
            if(trading==14)
                inv_healthpotions-=current_trade;
            if(trading==15)
                inv_antidotes-=current_trade;

            inventory-=current_trade;/**Subtract the traded item from the inventory weight.*/
            gold+=current_trade*current_item_price;/**Add the price to gold.*/

            /**If the Haggling skill is 1 or higher, make a check to see if some gold should be added.*/
            int haggle_check=random_range(0,99);/**Used to do a random chance check for a Haggling bonus.*/
            /**A base 10% chance that the player will receive a Haggle bonus. Every 1 Haggle point, this chance increases by 1%. At least one Haggle point is needed.*/
            if(haggling>0 && haggle_check>(89-(haggling*1))){
                /**If the check is successful, give the player some bonus gold, determined by their Haggling skill.*/
                gold+=random_range(haggling*1,haggling*5);
            }

            city_screen();
        }
        draw_city();
        draw_dialog_sell_items();
    }
}

void set_item_prices(){
    int min,max;/**Minimum price, maximum price*/
    double current_item;/**Item currently having its price range determined*/
    /**Set all item prices using base item price ranges:*/
    min=0;
    max=0;
    /**For each item, apply the range formula to determine the price range, then randomly select a price from that range for the item.*/
    for(current_item=1;current_item<9;current_item++){
        min=(max*2) + (5*current_item);
        max=(min*2) + (5*current_item);
        if(current_item==1)
        price_antidotes=random_range(min,max);
        if(current_item==2)
        price_healthpotions=random_range(min,max);
        if(current_item==3)
        price_manapotions=random_range(min,max);
        if(current_item==4)
        price_revives=random_range(min,max);
        if(current_item==5)
        price_magicalitems=random_range(min,max);
        if(current_item==6)
        price_accessories=random_range(min,max);
        if(current_item==7)
        price_armor=random_range(min,max);
        if(current_item==8)
        price_weapons=random_range(min,max);
    }

    /**Add fluctuation price to each item:*/
    min=0;
    max=0;
    for(current_item=1;current_item<9;current_item++){
        min=(max/2) - (2*current_item);
        max=min*-1;
        if(current_item==8)
        price_weapons+=random_range(min,max);
        if(current_item==7)
        price_armor+=random_range(min,max);
        if(current_item==6)
        price_accessories+=random_range(min,max);
        if(current_item==5)
        price_magicalitems+=random_range(min,max);
        if(current_item==4)
        price_revives+=random_range(min,max);
        if(current_item==3)
        price_manapotions+=random_range(min,max);
        if(current_item==2)
        price_healthpotions+=random_range(min,max);
        if(current_item==1)
        price_antidotes+=random_range(min,max);
    }

    /**Add city fluctuation price to each item:*/
    /**If the current city is a small city:*/
    if(city[current_city]>=1 && city[current_city]<=6){
        min=0;
        max=0;
        for(current_item=1;current_item<9;current_item++){
            min=(max/2) - (3*current_item);
            max=min*-1;
            if(current_item==8)
            price_weapons+=random_range(min,max);
            if(current_item==7)
            price_armor+=random_range(min,max);
            if(current_item==6)
            price_accessories+=random_range(min,max);
            if(current_item==5)
            price_magicalitems+=random_range(min,max);
            if(current_item==4)
            price_revives+=random_range(min,max);
            if(current_item==3)
            price_manapotions+=random_range(min,max);
            if(current_item==2)
            price_healthpotions+=random_range(min,max);
            if(current_item==1)
            price_antidotes+=random_range(min,max);
        }
    }
    /**If the current city is a medium city:*/
    if(city[current_city]>=7 && city[current_city]<=15){
        min=0;
        max=0;
        for(current_item=1;current_item<9;current_item++){
            min=(max/2) - (4*current_item);
            max=min*-1;
            if(current_item==8)
            price_weapons+=random_range(min,max);
            if(current_item==7)
            price_armor+=random_range(min,max);
            if(current_item==6)
            price_accessories+=random_range(min,max);
            if(current_item==5)
            price_magicalitems+=random_range(min,max);
            if(current_item==4)
            price_revives+=random_range(min,max);
            if(current_item==3)
            price_manapotions+=random_range(min,max);
            if(current_item==2)
            price_healthpotions+=random_range(min,max);
            if(current_item==1)
            price_antidotes+=random_range(min,max);
        }
    }
    /**If the current city is a large city:*/
    if(city[current_city]>=16 && city[current_city]<=21){
        min=0;
        max=0;
        for(current_item=1;current_item<9;current_item++){
            min=(max/2) - (5*current_item);
            max=min*-1;
            if(current_item==8)
            price_weapons+=random_range(min,max);
            if(current_item==7)
            price_armor+=random_range(min,max);
            if(current_item==6)
            price_accessories+=random_range(min,max);
            if(current_item==5)
            price_magicalitems+=random_range(min,max);
            if(current_item==4)
            price_revives+=random_range(min,max);
            if(current_item==3)
            price_manapotions+=random_range(min,max);
            if(current_item==2)
            price_healthpotions+=random_range(min,max);
            if(current_item==1)
            price_antidotes+=random_range(min,max);
        }
    }

    /**Add global fluctuation price to each item:*/
    min=0;
    max=0;
    int temp_morality_compare=good_vs_evil-morality;/**Find the difference between world and player morality.*/
    if(temp_morality_compare<0){/**If temp_morality_compare is a negative number, make it positive.*/
        temp_morality_compare*=-1;
    }
    for(current_item=1;current_item<9;current_item++){
        min=(max/2)-(2*current_item)*(current_item*temp_morality_compare);
        max=min*-1;
        if(current_item==8)
        price_weapons+=random_range(min,max);
        if(current_item==7)
        price_armor+=random_range(min,max);
        if(current_item==6)
        price_accessories+=random_range(min,max);
        if(current_item==5)
        price_magicalitems+=random_range(min,max);
        if(current_item==4)
        price_revives+=random_range(min,max);
        if(current_item==3)
        price_manapotions+=random_range(min,max);
        if(current_item==2)
        price_healthpotions+=random_range(min,max);
        if(current_item==1)
        price_antidotes+=random_range(min,max);
    }

    /**If an item's price goes to 0 or below, set it to some small number:*/
    if(price_weapons<=0)
    price_weapons=random_range(1,10);
    if(price_armor<=0)
    price_armor=random_range(1,10);
    if(price_accessories<=0)
    price_accessories=random_range(1,10);
    if(price_magicalitems<=0)
    price_magicalitems=random_range(1,10);
    if(price_revives<=0)
    price_revives=random_range(1,10);
    if(price_manapotions<=0)
    price_manapotions=random_range(1,10);
    if(price_healthpotions<=0)
    price_healthpotions=random_range(1,10);
    if(price_antidotes<=0)
    price_antidotes=random_range(1,10);

    /**Random City Events:*/
    int x=random_range(0,99);/**Set the variable to determine whether any city event should occur.*/
    if(x>(89-(luck*2))){/**A base 10% chance that a city event will occur. Every 1 Luck point, this chance increases by 2%.*/
        x=random_range(0,99);/**A city event has been triggered, now determine which one should be triggered.*/
        if(x<5){/**There is a 5% chance that a moral decision dialog will be displayed.*/
            re_moral=true;/**Tell the game that a moral dialog should be displayed.*/
        }
        if(x>=5 && x<15){/**There is a 10% chance that some item will not be available for trade.*/
            city_event_notrade();/**Set which item is not available for trade.*/
        }
        if(x>=15 && x<58){/**There is a 43% chance that some item will be much cheaper.*/
            city_event_cheaper();/**Set which item is cheaper.*/
        }
        if(x>=58){/**There is a 42% chance that some item will be much more expensive.*/
            city_event_more_expensive();/**Set which item is more expensive.*/
        }
    }
}
