/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include "screen_draw.h"
#include "variables.h"
#include "sdl.h"
#include "time_of_day.h"

using namespace std;

void draw(){
    /**Grab the coordinates of the mouse cursor, so that it can be displayed.*/
    int x=0,y=0;/**The mouse offsets.*/
    SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/

    text_color=text_color_white;/**Set the text color.*/

    SDL_FillRect(screen,0,SDL_MapRGB(screen->format,0,91,152));

    apply_surface(0,0,waves,screen,&clip_waves[anim_waves_frame],0);

    apply_surface(0,0,overworld,screen,NULL,0);

    apply_surface(0,0,lighthouse,screen,&clip_lighthouse[anim_lighthouse_frame],0);

    city1.show();
    city2.show();
    city3.show();
    city4.show();
    city5.show();
    city6.show();
    city7.show();
    city8.show();

    character.show();

    cloud1.show();
    cloud2.show();
    cloud3.show();

    apply_surface(0,SCREEN_HEIGHT-50,time_back,screen,NULL,0);
    display_time();

    //Show the world hitboxes.
    if(option_dev==true){
        for(int i=0;i<hitboxes.size();i++){
            hitboxes.at(i).show();
        }
        text_color=text_color_yellow;
        ss.clear();ss.str("");ss<<"FPS: ";ss<<frame_rate;msg=ss.str();
        msg_write(10,50,36,msg,0);
        ss.clear();ss.str("");ss<<"MS Per Frame: ";ss<<ms_per_frame;msg=ss.str();
        msg_write(10,80,36,msg,0);
        text_color=text_color_white;
    }

    apply_surface(x,y,cursor,screen,NULL,0);/**Show the mouse cursor.*/

    /**No call to SDL_Flip() here because it needs to be placed in the code right after the call to this function, draw().*/
}

void draw_battle(){
    /**Grab the coordinates of the mouse cursor, so that it can be displayed.*/
    int x=0,y=0;/**The mouse offsets.*/
    SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/

    text_color=text_color_white;/**Set the text color.*/

    apply_surface(0,0,dialog,screen,NULL,0);

    msg_write(0,0,42,"Battle!",1);

    string temp_msg="";

    /**Display the combatants information:*/
    msg_write(0,SCREEN_HEIGHT/2-175,36,name,1);
    msg="Health: ";
    ss.clear();ss.str("");ss<<health;ss>>temp_msg;
    msg+=temp_msg;
    msg+="/";
    ss.clear();ss.str("");ss<<health_max;ss>>temp_msg;
    msg+=temp_msg;
    msg_write(0,SCREEN_HEIGHT/2-140,36,msg,1);

    msg_write(0,SCREEN_HEIGHT/2-100,36,"VS.",1);

    msg_write(0,SCREEN_HEIGHT/2-60,36,enemy_name,1);
    msg="Health: ";
    ss.clear();ss.str("");ss<<enemy_health;ss>>temp_msg;
    msg+=temp_msg;
    msg+="/";
    ss.clear();ss.str("");ss<<enemy_health_max;ss>>temp_msg;
    msg+=temp_msg;
    msg_write(0,SCREEN_HEIGHT/2-25,36,msg,1);

    /**Draw the buttons:*/
    msg_write(0,SCREEN_HEIGHT-110-BUTTON_HEIGHT*2,30,"Attack",1);
    msg_write(0,SCREEN_HEIGHT-110-BUTTON_HEIGHT,30,"Drink a Health Potion",1);
    msg_write(0,SCREEN_HEIGHT-110,30,"Flee",1);

    b_select_menu.show();

    apply_surface(x,y,cursor,screen,NULL,0);/**Show the mouse cursor.*/

    SDL_Flip(screen);
}

void draw_city(){
    /**Grab the coordinates of the mouse cursor, so that it can be displayed.*/
    int x=0,y=0;/**The mouse offsets.*/
    SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/

    text_color=text_color_white;/**Set the text color.*/

    /**Apply the city background.*/
    apply_surface(0,0,city_background,screen,NULL,0);

    /**Display the inventory items:*/
    /**Display the chart labels:*/
    msg_write(20,7,24,"Item Type",0);
    msg_write(125,7,24,"Number",0);
    msg_write(243,7,24,"Price",0);
    /**Display the item names and buy/sell buttons:*/
    apply_surface(15,BUTTON_HEIGHT+20,b_buy,screen,NULL,0);
    msg_write(30,BUTTON_HEIGHT,18,"Weapons",0);
    apply_surface(15,BUTTON_HEIGHT*2+20,b_buy,screen,NULL,0);
    msg_write(37,BUTTON_HEIGHT*2,18,"Armor",0);
    apply_surface(15,BUTTON_HEIGHT*3+20,b_buy,screen,NULL,0);
    msg_write(22,BUTTON_HEIGHT*3,18,"Accessories",0);
    apply_surface(15,BUTTON_HEIGHT*4+20,b_buy,screen,NULL,0);
    msg_write(16,BUTTON_HEIGHT*4,18,"Magical Items",0);
    apply_surface(15,BUTTON_HEIGHT*5+20,b_buy,screen,NULL,0);
    msg_write(35,BUTTON_HEIGHT*5,18,"Revives",0);
    apply_surface(15,BUTTON_HEIGHT*6+20,b_buy,screen,NULL,0);
    msg_write(17,BUTTON_HEIGHT*6,18,"Mana Potions",0);
    apply_surface(15,BUTTON_HEIGHT*7+20,b_buy,screen,NULL,0);
    msg_write(16,BUTTON_HEIGHT*7,18,"Health Potions",0);
    apply_surface(15,BUTTON_HEIGHT*8+20,b_buy,screen,NULL,0);
    msg_write(25,BUTTON_HEIGHT*8,18,"Antidotes",0);
    /**Display the player's inventory amounts:*/
    ss.clear();ss.str("");ss<<inv_weapons;ss>>msg;
    msg_write(145,BUTTON_HEIGHT+8,24,msg,0);
    ss.clear();ss.str("");ss<<inv_armor;ss>>msg;
    msg_write(145,BUTTON_HEIGHT*2+8,24,msg,0);
    ss.clear();ss.str("");ss<<inv_accessories;ss>>msg;
    msg_write(145,BUTTON_HEIGHT*3+8,24,msg,0);
    ss.clear();ss.str("");ss<<inv_magicalitems;ss>>msg;
    msg_write(145,BUTTON_HEIGHT*4+8,24,msg,0);
    ss.clear();ss.str("");ss<<inv_revives;ss>>msg;
    msg_write(145,BUTTON_HEIGHT*5+8,24,msg,0);
    ss.clear();ss.str("");ss<<inv_manapotions;ss>>msg;
    msg_write(145,BUTTON_HEIGHT*6+8,24,msg,0);
    ss.clear();ss.str("");ss<<inv_healthpotions;ss>>msg;
    msg_write(145,BUTTON_HEIGHT*7+8,24,msg,0);
    ss.clear();ss.str("");ss<<inv_antidotes;ss>>msg;
    msg_write(145,BUTTON_HEIGHT*8+8,24,msg,0);
    /**Display the current item prices:*/
    ss.clear();ss.str("");ss<<price_weapons;ss>>msg;/**Put the current item price into msg.*/
    if(price_weapons==0){/**If the item's price is 0, change msg to tell the player none of that item are in stock.*/
    msg="Not Trading";
    }
    msg_write(243,BUTTON_HEIGHT+8,24,msg,0);
    ss.clear();ss.str("");ss<<price_armor;ss>>msg;
    if(price_armor==0){
    msg="Not Trading";
    }
    msg_write(243,BUTTON_HEIGHT*2+8,24,msg,0);
    ss.clear();ss.str("");ss<<price_accessories;ss>>msg;
    if(price_accessories==0){
    msg="Not Trading";
    }
    msg_write(243,BUTTON_HEIGHT*3+8,24,msg,0);
    ss.clear();ss.str("");ss<<price_magicalitems;ss>>msg;
    if(price_magicalitems==0){
    msg="Not Trading";
    }
    msg_write(243,BUTTON_HEIGHT*4+8,24,msg,0);
    ss.clear();ss.str("");ss<<price_revives;ss>>msg;
    if(price_revives==0){
    msg="Not Trading";
    }
    msg_write(243,BUTTON_HEIGHT*5+8,24,msg,0);
    ss.clear();ss.str("");ss<<price_manapotions;ss>>msg;
    if(price_manapotions==0){
    msg="Not Trading";
    }
    msg_write(243,BUTTON_HEIGHT*6+8,24,msg,0);
    ss.clear();ss.str("");ss<<price_healthpotions;ss>>msg;
    if(price_healthpotions==0){
    msg="Not Trading";
    }
    msg_write(243,BUTTON_HEIGHT*7+8,24,msg,0);
    ss.clear();ss.str("");ss<<price_antidotes;ss>>msg;
    if(price_antidotes==0){
    msg="Not Trading";
    }
    msg_write(243,BUTTON_HEIGHT*8+8,24,msg,0);

    msg_write(SCREEN_WIDTH-307,7,30,city_name,0);/**City name.*/

    /**Display the remaining days of game time:*/
    string temp_msg="";/**Used to create long string with multiple variables, etc.*/
    msg="Days Remaining: ";
    ss.clear();ss.str("");ss<<days_max-days;ss>>temp_msg;
    msg+=temp_msg;
    msg_write(SCREEN_WIDTH-307,35,24,msg,0);

    /**Display the time:*/
    //msg="Time: ";
    //ss.clear();ss.str("");ss<<world_hour;ss>>temp_msg;
    //msg+=temp_msg;
    //msg+=":00";
    //msg_write(SCREEN_WIDTH-100,35,24,msg,0);

    /**Display the info:*/
    msg="Gold: ";
    msg_write(SCREEN_WIDTH-307,65,24,msg,0);
    ss.clear();ss.str("");ss<<gold;ss>>temp_msg;
    msg=temp_msg;
    msg_write(SCREEN_WIDTH-207,65,24,msg,0);
    msg="Debt: ";
    msg_write(SCREEN_WIDTH-307,85,24,msg,0);
    ss.clear();ss.str("");ss<<debt;ss>>temp_msg;
    msg=temp_msg;
    msg_write(SCREEN_WIDTH-207,85,24,msg,0);
    msg="Savings: ";
    msg_write(SCREEN_WIDTH-307,105,24,msg,0);
    ss.clear();ss.str("");ss<<savings;ss>>temp_msg;
    msg=temp_msg;
    msg_write(SCREEN_WIDTH-207,105,24,msg,0);
    msg="Cart Space: ";
    msg_write(SCREEN_WIDTH-307,125,24,msg,0);
    ss.clear();ss.str("");ss<<inventory;ss>>temp_msg;
    msg=temp_msg;
    msg+=" / ";
    ss.clear();ss.str("");ss<<inventory_max;ss>>temp_msg;
    msg+=temp_msg;
    msg_write(SCREEN_WIDTH-207,125,24,msg,0);

    msg_write(SCREEN_WIDTH-193,165,30,"Set Out",0);
    msg_write(SCREEN_WIDTH-227,205,30,"Visit the Bank",0);
    msg_write(SCREEN_WIDTH-225,245,30,"Player Screen",0);
    msg_write(SCREEN_WIDTH-207,285,30,"Main Menu",0);
    b_select_item.show();
    b_select_menu.show();

    apply_surface(x,y,cursor,screen,NULL,0);/**Show the mouse cursor.*/

    /**No call to SDL_Flip() here because it needs to be placed in the code right after the call to this function, draw_city().*/
}

void draw_main_menu(){
    /**Grab the coordinates of the mouse cursor, so that it can be displayed.*/
    int x=0,y=0;/**The mouse offsets.*/
    SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/

    text_color=text_color_white;/**Set the text color.*/

    apply_surface(0,0,menu_background,screen,NULL,0);/**Show the menu background.*/
    msg_write(0,0,42,"Vendor Trash",1);
    msg_write(0,90,36,"A Kevin Wells Production",1);

    if(game_in_progress==true){
        msg_write(0,(SCREEN_HEIGHT/2)-(BUTTON_HEIGHT*3)+20,30,"Continue",1);
    }
    msg_write(0,(SCREEN_HEIGHT/2)-(BUTTON_HEIGHT*2)+20,30,"New Game",1);
    msg_write(0,(SCREEN_HEIGHT/2)-(BUTTON_HEIGHT)+20,30,"High Scores",1);
    msg_write(0,(SCREEN_HEIGHT/2)+20,30,"Options",1);
    msg_write(0,(SCREEN_HEIGHT/2)+(BUTTON_HEIGHT)+20,30,"About",1);
    msg_write(0,(SCREEN_HEIGHT/2)+(BUTTON_HEIGHT)*2+20,30,"Quit",1);

    b_select_menu.show();

    msg_write(10,SCREEN_HEIGHT-35,30,"Version: Beta 0.9",0);

    /**msg_write(300,SCREEN_HEIGHT-50,18,"Copyright 2010 by Kevin Wells",0);
    msg_write(300,SCREEN_HEIGHT-25,18,"Licensed under the 'Tasty Cheese'-ware License",0);*/

    apply_surface(x,y,cursor,screen,NULL,0);/**Show the mouse cursor.*/

    /**No call to SDL_Flip() here because a dialog window can pop up in front of it.*/
}

void draw_options(){
    /**Grab the coordinates of the mouse cursor, so that it can be displayed.*/
    int x=0,y=0;/**The mouse offsets.*/
    SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/

    text_color=text_color_white;/**Set the text color.*/

    apply_surface(0,0,menu_background,screen,NULL,0);
    msg_write(0,0,42,"Options",1);

    msg_write((SCREEN_WIDTH-255)/2,(BUTTON_HEIGHT*2)+30,30,"Fullscreen",0);

    b_fullscreen.show();/**Show the fullscreen toggle button.*/

    msg_write(0,SCREEN_HEIGHT-BUTTON_HEIGHT-10,30,"Back",1);
    b_select_menu.show();

    apply_surface(x,y,cursor,screen,NULL,0);/**Show the mouse cursor.*/

    SDL_Flip(screen);/**Update the screen.*/
}

void draw_about(){
    /**Grab the coordinates of the mouse cursor, so that it can be displayed.*/
    int x=0,y=0;/**The mouse offsets.*/
    SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/

    text_color=text_color_white;/**Set the text color.*/

    apply_surface(0,0,about_background,screen,NULL,0);
    msg_write(0,0,42,"About",1);

    msg_write(0,100,24,"Welcome to Vendor Trash!",1);
    msg_write(0,120,24,"In this game, you play the part of an NPC in the world of Aearun.",1);
    msg_write(0,140,24,"Aearun is in constant jeopardy, be it from evil tyrants,",1);
    msg_write(0,160,24,"powerful wizards, or natural disasters.",1);
    msg_write(0,180,24,"When a new evil threatens Aearun,",1);
    msg_write(0,200,24,"a brave hero always rises to meet the challenge.",1);
    msg_write(0,220,24,"You, however, have somewhat less lofty goals in life.",1);
    msg_write(0,240,24,"You have taken out a loan and set up your very own item shop.",1);
    msg_write(0,260,24,"Now, you can travel the world seeking exotic deals",1);
    msg_write(0,280,24,"and legendary items to trade in the marketplace.",1);

    msg_write(0,SCREEN_HEIGHT-BUTTON_HEIGHT-10,30,"Back",1);
    b_select_menu.show();

    apply_surface(x,y,cursor,screen,NULL,0);/**Show the mouse cursor.*/

    SDL_Flip(screen);/**Update the screen.*/
}

void draw_stats(){
    /**Grab the coordinates of the mouse cursor, so that it can be displayed.*/
    int x=0,y=0;/**The mouse offsets.*/
    SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/

    text_color=text_color_white;/**Set the text color.*/

    apply_surface(0,0,stats_background,screen,NULL,2);
    msg_write(10,0,42,"Player Information",0);

    b_cart_size.show();
    b_haggling.show();
    b_banking.show();
    b_strength.show();
    b_stamina.show();
    b_luck.show();
    msg_write(0,SCREEN_HEIGHT-BUTTON_HEIGHT-10,30,"Back",1);
    msg_write(23,230,30,"Drink a Health Potion",0);
    b_select_menu.show();

    string msg_temp;

    msg="Name: ";
    msg+=name;
    msg_write(10,50,30,msg,0);

    msg="Level: ";/**Set the string to be displayed to "Level: ".*/
    ss.clear();ss.str("");ss<<level;ss>>msg_temp;/**Store the level variable in a temporary string.*/
    msg+=msg_temp;/**Add the level variable stored in the temporary string to the string to be displayed.*/
    msg_write(10,95,30,msg,0);/**Display the string.*/

    msg="Experience: ";
    ss.clear();ss.str("");ss<<experience;ss>>msg_temp;
    msg+=msg_temp;
    msg+=" / ";
    ss.clear();ss.str("");ss<<experience_max;ss>>msg_temp;
    msg+=msg_temp;
    msg_write(10,140,30,msg,0);

    msg="Health: ";
    ss.clear();ss.str("");ss<<health;ss>>msg_temp;
    msg+=msg_temp;
    msg+=" / ";
    ss.clear();ss.str("");ss<<health_max;ss>>msg_temp;
    msg+=msg_temp;
    msg_write(10,185,30,msg,0);

    /**Display equipment:*/
    msg="Weapon: ";
    msg+=weapon_name;
    msg_write(10,275,30,msg,0);
    msg="Damage Bonus: ";
    ss.clear();ss.str("");ss<<equip_attack;ss>>msg_temp;
    msg+=msg_temp;
    msg_write(10,310,24,msg,0);
    msg="Armor: ";
    msg+=armor_name;
    msg_write(10,355,30,msg,0);
    msg="Defense Bonus: ";
    ss.clear();ss.str("");ss<<equip_defense;ss>>msg_temp;
    msg+=msg_temp;
    msg_write(10,390,24,msg,0);

    msg_write(SCREEN_WIDTH-200,0,42,"Skills",0);

    msg="Skill Points: ";
    ss.clear();ss.str("");ss<<skill_points;ss>>msg_temp;
    msg+=msg_temp;
    msg_write(SCREEN_WIDTH-215,50,24,msg,0);

    msg="Travel: ";
    ss.clear();ss.str("");ss<<cart_size;ss>>msg_temp;
    msg+=msg_temp;
    msg_write(SCREEN_WIDTH-200,90,30,msg,0);
    msg_write(SCREEN_WIDTH-210,120,18,"Increases inventory size.",0);

    msg="Haggling: ";
    ss.clear();ss.str("");ss<<haggling;ss>>msg_temp;
    msg+=msg_temp;
    msg_write(SCREEN_WIDTH-200,140,30,msg,0);
    msg_write(SCREEN_WIDTH-210,170,18,"Increases gold from trades.",0);

    msg="Banking: ";
    ss.clear();ss.str("");ss<<banking;ss>>msg_temp;
    msg+=msg_temp;
    msg_write(SCREEN_WIDTH-200,190,30,msg,0);
    msg_write(SCREEN_WIDTH-210,220,18,"Increases interest rate.",0);

    msg="Strength: ";
    ss.clear();ss.str("");ss<<strength;ss>>msg_temp;
    msg+=msg_temp;
    msg_write(SCREEN_WIDTH-200,240,30,msg,0);
    msg_write(SCREEN_WIDTH-210,270,18,"Increases damage done in battle.",0);

    msg="Stamina: ";
    ss.clear();ss.str("");ss<<stamina;ss>>msg_temp;
    msg+=msg_temp;
    msg_write(SCREEN_WIDTH-200,290,30,msg,0);
    msg_write(SCREEN_WIDTH-210,320,18,"Increases health regeneration.",0);

    msg="Luck: ";
    ss.clear();ss.str("");ss<<luck;ss>>msg_temp;
    msg+=msg_temp;
    msg_write(SCREEN_WIDTH-200,340,30,msg,0);
    msg_write(SCREEN_WIDTH-210,370,18,"Affects a variety of things!",0);

    apply_surface(x,y,cursor,screen,NULL,0);/**Show the mouse cursor.*/

    SDL_Flip(screen);/**Update the screen.*/
}

void draw_dialog_bank(){
    /**Grab the coordinates of the mouse cursor, so that it can be displayed.*/
    int x=0,y=0;/**The mouse offsets.*/
    SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/

    text_color=text_color_white;/**Set the text color.*/

    apply_surface(0,0,dialog,screen,NULL,1);/**Show the dialog box.*/
    msg_write(0,0,42,"Bank",1);

    msg_write(0,75,30,"Deposit",1);
    msg_write(0,75+BUTTON_HEIGHT,30,"Withdraw",1);
    msg_write(0,75+(BUTTON_HEIGHT*2),30,"Pay Back Loan",1);
    msg_write(0,SCREEN_HEIGHT-BUTTON_HEIGHT-10,30,"Back",1);
    b_select_menu.show();

    apply_surface(x,y,cursor,screen,NULL,0);/**Show the mouse cursor.*/

    SDL_Flip(screen);/**Update the screen.*/
}

void draw_dialog_bank_transaction(){
    /**Grab the coordinates of the mouse cursor, so that it can be displayed.*/
    int x=0,y=0;/**The mouse offsets.*/
    SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/

    text_color=text_color_white;/**Set the text color.*/

    apply_surface(0,0,dialog,screen,NULL,1);/**Show the dialog box.*/
    if(bank_mode==1)
        msg_write(0,0,42,"How much would you like to deposit?",1);
    if(bank_mode==2)
        msg_write(0,0,42,"How much would you like to withdraw?",1);
    if(bank_mode==3)
        msg_write(0,0,36,"How much of your loan would you like to pay off?",1);

    /**Show the current amount of money being deposited/withdrawn/paid off:*/
    ss.clear();ss.str("");ss<<current_trade;ss>>msg;
    msg_write(0,SCREEN_HEIGHT/2,30,msg,1);

    b_arrowup.show();
    b_arrowdown.show();
    msg_write(150,SCREEN_HEIGHT-BUTTON_HEIGHT-10,30,"Ok",0);
    msg_write(SCREEN_WIDTH-BUTTON_WIDTH,SCREEN_HEIGHT-BUTTON_HEIGHT-10,30,"Cancel",0);
    b_select_menu.show();

    apply_surface(x,y,cursor,screen,NULL,0);/**Show the mouse cursor.*/

    SDL_Flip(screen);/**Update the screen.*/
}

void draw_dialog_buy_items(){
    /**Grab the coordinates of the mouse cursor, so that it can be displayed.*/
    int x=0,y=0;/**The mouse offsets.*/
    SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/

    text_color=text_color_white;/**Set the text color.*/

    apply_surface(0,0,dialog,screen,NULL,1);/**Show the dialog box.*/
    msg_write(0,(SCREEN_HEIGHT/2)-(BUTTON_HEIGHT*4),42,"How many would you like to purchase?",1);
    msg_write(0,(SCREEN_HEIGHT/2)-(BUTTON_HEIGHT*4)+40,42,"You can afford a maximum of:",1);

    /**Show the current number of this item you are buying:*/
    ss.clear();ss.str("");ss<<current_trade;ss>>msg;
    msg_write(0,SCREEN_HEIGHT/2,30,msg,1);

    b_arrowup.show();
    b_arrowdown.show();
    msg_write(150,SCREEN_HEIGHT-BUTTON_HEIGHT-10,30,"Ok",0);
    msg_write(SCREEN_WIDTH-BUTTON_WIDTH,SCREEN_HEIGHT-BUTTON_HEIGHT-10,30,"Cancel",0);
    b_select_menu.show();

    apply_surface(x,y,cursor,screen,NULL,0);/**Show the mouse cursor.*/

    SDL_Flip(screen);/**Update the screen.*/
}

void draw_dialog_sell_items(){
    /**Grab the coordinates of the mouse cursor, so that it can be displayed.*/
    int x=0,y=0;/**The mouse offsets.*/
    SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/

    text_color=text_color_white;/**Set the text color.*/

    apply_surface(0,0,dialog,screen,NULL,1);/**Show the dialog box.*/
    msg_write(0,(SCREEN_HEIGHT/2)-(BUTTON_HEIGHT*4),42,"How many would you like to sell?",1);
    msg_write(0,(SCREEN_HEIGHT/2)-(BUTTON_HEIGHT*4)+40,42,"You have a total of:",1);

    /**Show the current number of this item you are selling:*/
    ss.clear();ss.str("");ss<<current_trade;ss>>msg;
    msg_write(0,SCREEN_HEIGHT/2,30,msg,1);

    b_arrowup.show();
    b_arrowdown.show();
    msg_write(150,SCREEN_HEIGHT-BUTTON_HEIGHT-10,30,"Ok",0);
    msg_write(SCREEN_WIDTH-BUTTON_WIDTH,SCREEN_HEIGHT-BUTTON_HEIGHT-10,30,"Cancel",0);
    b_select_menu.show();

    apply_surface(x,y,cursor,screen,NULL,0);/**Show the mouse cursor.*/

    SDL_Flip(screen);/**Update the screen.*/
}

void draw_moral_dialog(){
    /**Grab the coordinates of the mouse cursor, so that it can be displayed.*/
    int x=0,y=0;/**The mouse offsets.*/
    SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/

    text_color=text_color_white;/**Set the text color.*/

    apply_surface(0,0,dialog,screen,NULL,1);/**Show the dialog box.*/

    if(msg1!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-100,18,msg1,1);/**Display the message.*/
    }
    if(msg2!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-75,18,msg2,1);/**Display the message.*/
    }
    if(msg3!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-50,18,msg3,1);/**Display the message.*/
    }
    if(msg4!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-25,18,msg4,1);/**Display the message.*/
    }
    if(msg5!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-0,18,msg5,1);/**Display the message.*/
    }

    msg_write(10,SCREEN_HEIGHT-125,18,msg_good,0);/**Display the good text.*/
    msg_write(10,SCREEN_HEIGHT-80,18,msg_neutral,0);/**Display the neutral text.*/
    msg_write(10,SCREEN_HEIGHT-35,18,msg_bad,0);/**Display the bad text.*/
    b_moral_good.show();
    b_moral_neutral.show();
    b_moral_bad.show();

    apply_surface(x,y,cursor,screen,NULL,0);/**Show the mouse cursor.*/

    SDL_Flip(screen);/**Update the screen.*/
}

void draw_get_max_days(){
    /**Grab the coordinates of the mouse cursor, so that it can be displayed.*/
    int x=0,y=0;/**The mouse offsets.*/
    SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/

    text_color=text_color_white;/**Set the text color.*/

    apply_surface(0,0,dialog,screen,NULL,1);/**Show the dialog box.*/

    msg_write(0,(SCREEN_HEIGHT/2)-225,36,"How many days would you like your game to last?",1);/**Display the message.*/

    msg_write(0,SCREEN_HEIGHT-260,24,"1. 25 days.",1);
    msg_write(0,SCREEN_HEIGHT-215,24,"2. 50 days.",1);
    msg_write(0,SCREEN_HEIGHT-170,24,"3. 75 days.",1);
    msg_write(0,SCREEN_HEIGHT-125,24,"4. 100 days.",1);
    msg_write(0,SCREEN_HEIGHT-80,24,"5. 150 days.",1);
    msg_write(0,SCREEN_HEIGHT-35,24,"6. 200 days.",1);

    apply_surface(x,y,cursor,screen,NULL,0);/**Show the mouse cursor.*/

    SDL_Flip(screen);/**Update the screen.*/
}

void draw_dialog_message(){
    /**Grab the coordinates of the mouse cursor, so that it can be displayed.*/
    int x=0,y=0;/**The mouse offsets.*/
    SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/

    text_color=text_color_white;/**Set the text color.*/

    apply_surface(0,0,dialog,screen,NULL,1);/**Show the dialog box.*/

    if(msg1!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-100,18,msg1,1);/**Display the message.*/
    }
    if(msg2!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-75,18,msg2,1);/**Display the message.*/
    }
    if(msg3!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-50,18,msg3,1);/**Display the message.*/
    }
    if(msg4!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-25,18,msg4,1);/**Display the message.*/
    }
    if(msg5!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-0,18,msg5,1);/**Display the message.*/
    }

    msg_write(0,SCREEN_HEIGHT-BUTTON_HEIGHT-10,30,"Ok",1);
    b_select_menu.show();

    apply_surface(x,y,cursor,screen,NULL,0);/**Show the mouse cursor.*/

    SDL_Flip(screen);/**Update the screen.*/
}

void draw_found_dialog_message(){
    /**Grab the coordinates of the mouse cursor, so that it can be displayed.*/
    int x=0,y=0;/**The mouse offsets.*/
    SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/

    text_color=text_color_white;/**Set the text color.*/

    apply_surface(0,0,dialog,screen,NULL,1);/**Show the dialog box.*/

    if(msg1!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-100,18,msg1,1);/**Display the message.*/
    }
    if(msg2!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-75,18,msg2,1);/**Display the message.*/
    }
    if(msg3!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-50,18,msg3,1);/**Display the message.*/
    }
    if(msg4!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-25,18,msg4,1);/**Display the message.*/
    }
    if(msg5!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-0,18,msg5,1);/**Display the message.*/
    }

    msg_write(150,SCREEN_HEIGHT-BUTTON_HEIGHT-10,30,"Equip it",0);
    msg_write(SCREEN_WIDTH-BUTTON_WIDTH,SCREEN_HEIGHT-BUTTON_HEIGHT-10,30,"Toss it",0);
    b_select_menu.show();

    apply_surface(x,y,cursor,screen,NULL,0);/**Show the mouse cursor.*/

    SDL_Flip(screen);/**Update the screen.*/
}

void draw_new_game_dialog_message(){
    /**Grab the coordinates of the mouse cursor, so that it can be displayed.*/
    int x=0,y=0;/**The mouse offsets.*/
    SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/

    text_color=text_color_white;/**Set the text color.*/

    apply_surface(0,0,dialog,screen,NULL,1);/**Show the dialog box.*/

    if(msg1!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-125,18,msg1,1);/**Display the message.*/
    }
    if(msg2!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-100,18,msg2,1);/**Display the message.*/
    }
    if(msg3!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-75,18,msg3,1);/**Display the message.*/
    }
    if(msg4!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-50,18,msg4,1);/**Display the message.*/
    }
    if(msg5!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-25,18,msg5,1);/**Display the message.*/
    }
    if(msg6!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)-0,18,msg6,1);/**Display the message.*/
    }
    if(msg7!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)+25,18,msg7,1);/**Display the message.*/
    }
    if(msg8!="0"){
        msg_write(0,(SCREEN_HEIGHT/2)+50,18,msg8,1);/**Display the message.*/
    }

    msg_write(0,SCREEN_HEIGHT-BUTTON_HEIGHT-10,30,"Ok",1);
    b_select_menu.show();

    apply_surface(x,y,cursor,screen,NULL,0);/**Show the mouse cursor.*/

    SDL_Flip(screen);/**Update the screen.*/
}

void draw_scores_display(){
    /**Grab the coordinates of the mouse cursor, so that it can be displayed.*/
    int x=0,y=0;/**The mouse offsets.*/
    SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/

    text_color=text_color_white;/**Set the text color.*/

    apply_surface(0,0,dialog,screen,NULL,1);/**Show the dialog box.*/

    msg_write(10,0,36,"Name",0);
    msg_write(175,0,36,"High Scores",0);
    msg_write(405,0,36,"Level",0);
    msg_write(565,0,36,"Days",0);

    msg_write(20,(SCREEN_HEIGHT/2)-200,24,score_name[9],0);
    ss.clear();ss.str("");ss<<score[9];ss>>msg;
    msg_write(200,(SCREEN_HEIGHT/2)-200,24,msg,0);
    ss.clear();ss.str("");ss<<score_level[9];ss>>msg;
    msg_write(425,(SCREEN_HEIGHT/2)-200,24,msg,0);
    ss.clear();ss.str("");ss<<score_days[9];ss>>msg;
    msg_write(580,(SCREEN_HEIGHT/2)-200,24,msg,0);

    msg_write(20,(SCREEN_HEIGHT/2)-160,24,score_name[8],0);
    ss.clear();ss.str("");ss<<score[8];ss>>msg;
    msg_write(200,(SCREEN_HEIGHT/2)-160,24,msg,0);
    ss.clear();ss.str("");ss<<score_level[8];ss>>msg;
    msg_write(425,(SCREEN_HEIGHT/2)-160,24,msg,0);
    ss.clear();ss.str("");ss<<score_days[8];ss>>msg;
    msg_write(580,(SCREEN_HEIGHT/2)-160,24,msg,0);

    msg_write(20,(SCREEN_HEIGHT/2)-120,24,score_name[7],0);
    ss.clear();ss.str("");ss<<score[7];ss>>msg;
    msg_write(200,(SCREEN_HEIGHT/2)-120,24,msg,0);
    ss.clear();ss.str("");ss<<score_level[7];ss>>msg;
    msg_write(425,(SCREEN_HEIGHT/2)-120,24,msg,0);
    ss.clear();ss.str("");ss<<score_days[7];ss>>msg;
    msg_write(580,(SCREEN_HEIGHT/2)-120,24,msg,0);

    msg_write(20,(SCREEN_HEIGHT/2)-80,24,score_name[6],0);
    ss.clear();ss.str("");ss<<score[6];ss>>msg;
    msg_write(200,(SCREEN_HEIGHT/2)-80,24,msg,0);
    ss.clear();ss.str("");ss<<score_level[6];ss>>msg;
    msg_write(425,(SCREEN_HEIGHT/2)-80,24,msg,0);
    ss.clear();ss.str("");ss<<score_days[6];ss>>msg;
    msg_write(580,(SCREEN_HEIGHT/2)-80,24,msg,0);

    msg_write(20,(SCREEN_HEIGHT/2)-40,24,score_name[5],0);
    ss.clear();ss.str("");ss<<score[5];ss>>msg;
    msg_write(200,(SCREEN_HEIGHT/2)-40,24,msg,0);
    ss.clear();ss.str("");ss<<score_level[5];ss>>msg;
    msg_write(425,(SCREEN_HEIGHT/2)-40,24,msg,0);
    ss.clear();ss.str("");ss<<score_days[5];ss>>msg;
    msg_write(580,(SCREEN_HEIGHT/2)-40,24,msg,0);

    msg_write(20,(SCREEN_HEIGHT/2)-0,24,score_name[4],0);
    ss.clear();ss.str("");ss<<score[4];ss>>msg;
    msg_write(200,(SCREEN_HEIGHT/2)-0,24,msg,0);
    ss.clear();ss.str("");ss<<score_level[4];ss>>msg;
    msg_write(425,(SCREEN_HEIGHT/2)-0,24,msg,0);
    ss.clear();ss.str("");ss<<score_days[4];ss>>msg;
    msg_write(580,(SCREEN_HEIGHT/2)-0,24,msg,0);

    msg_write(20,(SCREEN_HEIGHT/2)+40,24,score_name[3],0);
    ss.clear();ss.str("");ss<<score[3];ss>>msg;
    msg_write(200,(SCREEN_HEIGHT/2)+40,24,msg,0);
    ss.clear();ss.str("");ss<<score_level[3];ss>>msg;
    msg_write(425,(SCREEN_HEIGHT/2)+40,24,msg,0);
    ss.clear();ss.str("");ss<<score_days[3];ss>>msg;
    msg_write(580,(SCREEN_HEIGHT/2)+40,24,msg,0);

    msg_write(20,(SCREEN_HEIGHT/2)+80,24,score_name[2],0);
    ss.clear();ss.str("");ss<<score[2];ss>>msg;
    msg_write(200,(SCREEN_HEIGHT/2)+80,24,msg,0);
    ss.clear();ss.str("");ss<<score_level[2];ss>>msg;
    msg_write(425,(SCREEN_HEIGHT/2)+80,24,msg,0);
    ss.clear();ss.str("");ss<<score_days[2];ss>>msg;
    msg_write(580,(SCREEN_HEIGHT/2)+80,24,msg,0);

    msg_write(20,(SCREEN_HEIGHT/2)+120,24,score_name[1],0);
    ss.clear();ss.str("");ss<<score[1];ss>>msg;
    msg_write(200,(SCREEN_HEIGHT/2)+120,24,msg,0);
    ss.clear();ss.str("");ss<<score_level[1];ss>>msg;
    msg_write(425,(SCREEN_HEIGHT/2)+120,24,msg,0);
    ss.clear();ss.str("");ss<<score_days[1];ss>>msg;
    msg_write(580,(SCREEN_HEIGHT/2)+120,24,msg,0);

    msg_write(20,(SCREEN_HEIGHT/2)+160,24,score_name[0],0);
    ss.clear();ss.str("");ss<<score[0];ss>>msg;
    msg_write(200,(SCREEN_HEIGHT/2)+160,24,msg,0);
    ss.clear();ss.str("");ss<<score_level[0];ss>>msg;
    msg_write(425,(SCREEN_HEIGHT/2)+160,24,msg,0);
    ss.clear();ss.str("");ss<<score_days[0];ss>>msg;
    msg_write(580,(SCREEN_HEIGHT/2)+160,24,msg,0);

    msg_write(0,SCREEN_HEIGHT-BUTTON_HEIGHT-10,30,"Back",1);
    b_select_menu.show();

    apply_surface(x,y,cursor,screen,NULL,0);/**Show the mouse cursor.*/

    SDL_Flip(screen);/**Update the screen.*/
}

void draw_get_name(){
    /**Grab the coordinates of the mouse cursor, so that it can be displayed.*/
    int x=0,y=0;/**The mouse offsets.*/
    SDL_GetMouseState(&x,&y);/**Store the mouse's current coordinates in x and y.*/

    text_color=text_color_white;/**Set the text color.*/

    apply_surface(0,0,dialog,screen,NULL,1);/**Show the dialog box.*/

    msg_write(0,0,42,"What is your name?",1);
    msg_write(0,SCREEN_HEIGHT/2,42,"________________",1);
    msg_write(0,SCREEN_HEIGHT-50,36,"Press Enter to Continue",1);

    get_player_name.show();

    apply_surface(x,y,cursor,screen,NULL,0);/**Show the mouse cursor.*/

    SDL_Flip(screen);/**Update the screen.*/
}
