/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include "game.h"
#include "main.h"
#include "items.h"
#include "variables.h"
#include "random_number_generator.h"
#include "dialog.h"
#include "menus.h"
#include "scores.h"

using namespace std;

void new_game(){
    /**Set up the variables for a new game:*/
    /**Player Stats:*/
    level=1;
    experience=0;
    experience_max=100;
    health=100;
    health_max=100;
    skill_points=0;
    cart_size=0;
    haggling=0;
    banking=0;
    strength=0;
    stamina=0;
    luck=0;
    morality=0;
    battles_won=0;
    battles_lost=0;
    sales=0;
    purchases=0;
    /**Player Information, etc.:*/
    gender=true;
    name=get_player_name.str;
    gold=2000;
    debt=40000;
    savings=0;
    inventory=0;
    inventory_max=200;
    /**Player Inventory:*/
    inv_weapons=0;
    inv_armor=0;
    inv_accessories=0;
    inv_magicalitems=0;
    inv_revives=0;
    inv_manapotions=0;
    inv_healthpotions=0;
    inv_antidotes=0;
    /**Player Equipment:*/
    equip_attack=0;
    equip_defense=0;
    weapon_name="";
    armor_name="";
    /**Game variables:*/
    game_in_progress=true;
    days=0;
    days_max=75;
    current_city=random_range(1,8);
    last_city=current_city;/**We need last_city to be the same as current_city when the game begins.*/
    /**World variables*/
    world_year=random_range(1200,1800);
    world_month=random_range(1,12);
    world_day=random_range(1,30);
    world_hour=random_range(1,23);
    world_scenario=random_range(0,3);/**This is what Problem scenario the game will be using.*/
    good_vs_evil=0;
    /**Not all of these variables will be used in every game, because it depends on which scenario is being played.*/
    int x=random_range(0,11);
    switch(x){
        case 0:
        world_evil="Kelnor";
        break;
        case 1:
        world_evil="Degrund";
        break;
        case 2:
        world_evil="Gamut";
        break;
        case 3:
        world_evil="Mortimer";
        break;
        case 4:
        world_evil="Actor";
        break;
        case 5:
        world_evil="Calchas";
        break;
        case 6:
        world_evil="Alex";
        break;
        case 7:
        world_evil="Karst";
        break;
        case 8:
        world_evil="Magus";
        break;
        case 9:
        world_evil="Nemo";
        break;
        case 10:
        world_evil="Erebus";
        break;
        case 11:
        world_evil="Agrius";
        break;
    }
    x=random_range(0,11);
    switch(x){
        case 0:
        world_homeland="Potos";
        break;
        case 1:
        world_homeland="Vandrol";
        break;
        case 2:
        world_homeland="Annwn";
        break;
        case 3:
        world_homeland="Ismara";
        break;
        case 4:
        world_homeland="Argyre";
        break;
        case 5:
        world_homeland="Dardania";
        break;
        case 6:
        world_homeland="Terale";
        break;
        case 7:
        world_homeland="Hognar";
        break;
        case 8:
        world_homeland="Cedda";
        break;
        case 9:
        world_homeland="Dabo";
        break;
        case 10:
        world_homeland="Brena";
        break;
        case 11:
        world_homeland="Sulla";
        break;
    }
    x=random_range(0,11);
    switch(x){
        case 0:
        world_other_kingdom="Kek";
        break;
        case 1:
        world_other_kingdom="Swantia";
        break;
        case 2:
        world_other_kingdom="Aaru";
        break;
        case 3:
        world_other_kingdom="Avalon";
        break;
        case 4:
        world_other_kingdom="Mashu";
        break;
        case 5:
        world_other_kingdom="Elysium";
        break;
        case 6:
        world_other_kingdom="Menacia";
        break;
        case 7:
        world_other_kingdom="Gogar";
        break;
        case 8:
        world_other_kingdom="Grul";
        break;
        case 9:
        world_other_kingdom="Finai";
        break;
        case 10:
        world_other_kingdom="Gragdish";
        break;
        case 11:
        world_other_kingdom="Corag";
        break;
    }
    x=random_range(0,11);
    switch(x){
        case 0:
        world_king="Tyranus";
        break;
        case 1:
        world_king="Septimus";
        break;
        case 2:
        world_king="Cadmus";
        break;
        case 3:
        world_king="Hector";
        break;
        case 4:
        world_king="Marsyas";
        break;
        case 5:
        world_king="Tantalus";
        break;
        case 6:
        world_king="Arem";
        break;
        case 7:
        world_king="Bik";
        break;
        case 8:
        world_king="Kedas";
        break;
        case 9:
        world_king="Delis";
        break;
        case 10:
        world_king="Juloth";
        break;
        case 11:
        world_king="Cedrich";
        break;
    }
    x=random_range(0,11);
    switch(x){
        case 0:
        world_artifact="Meld Stone";
        break;
        case 1:
        world_artifact="Crystal of Life";
        break;
        case 2:
        world_artifact="Touchstone";
        break;
        case 3:
        world_artifact="Golden Fleece";
        break;
        case 4:
        world_artifact="Sampo";
        break;
        case 5:
        world_artifact="Gleipnir";
        break;
        case 6:
        world_artifact="Orb of Fate";
        break;
        case 7:
        world_artifact="Sceptre of Might";
        break;
        case 8:
        world_artifact="Staff of Time";
        break;
        case 9:
        world_artifact="Mace of Destiny";
        break;
        case 10:
        world_artifact="Stone of Power";
        break;
        case 11:
        world_artifact="Hammer of Victory";
        break;
    }
    x=random_range(0,11);
    switch(x){
        case 0:
        world_hero="Heracles";
        break;
        case 1:
        world_hero="Clive";
        break;
        case 2:
        world_hero="Isaac";
        break;
        case 3:
        world_hero="William";
        break;
        case 4:
        world_hero="Ivan";
        break;
        case 5:
        world_hero="Garet";
        break;
        case 6:
        world_hero="Felix";
        break;
        case 7:
        world_hero="Randi";
        break;
        case 8:
        world_hero="Jonathan";
        break;
        case 9:
        world_hero="Jacob";
        break;
        case 10:
        world_hero="Marcus";
        break;
        case 11:
        world_hero="Edward";
        break;
    }
    /**Random event variables:*/
    re_city_item_zero=0;
    re_city_item_cheap=0;
    re_city_item_expensive=0;
    re_moral=false;

    /**Set the player's current position to the location of their starting city:*/
    if(current_city==1){
    character.x=city1.hitbox.x;
    character.y=city1.hitbox.y;
    }
    if(current_city==2){
    character.x=city2.hitbox.x;
    character.y=city2.hitbox.y;
    }
    if(current_city==3){
    character.x=city3.hitbox.x;
    character.y=city3.hitbox.y;
    }
    if(current_city==4){
    character.x=city4.hitbox.x;
    character.y=city4.hitbox.y;
    }
    if(current_city==5){
    character.x=city5.hitbox.x;
    character.y=city5.hitbox.y;
    }
    if(current_city==6){
    character.x=city6.hitbox.x;
    character.y=city6.hitbox.y;
    }
    if(current_city==7){
    character.x=city7.hitbox.x;
    character.y=city7.hitbox.y;
    }
    if(current_city==8){
    character.x=city8.hitbox.x;
    character.y=city8.hitbox.y;
    }

    /**Generate the cities:*/
    city[1]=0;
    city[2]=0;
    city[3]=0;
    city[4]=0;
    city[5]=0;
    city[6]=0;
    city[7]=0;
    city[8]=0;
    city[1]=random_range(1,21);
    while(city[2]==0 || city[2]==city[1]){
        city[2]=random_range(1,21);
    }
    while(city[3]==0 || city[3]==city[1] || city[3]==city[2]){
        city[3]=random_range(1,21);
    }
    while(city[4]==0 || city[4]==city[1] || city[4]==city[2] || city[4]==city[3]){
        city[4]=random_range(1,21);
    }
    while(city[5]==0 || city[5]==city[1] || city[5]==city[2] || city[5]==city[3] || city[5]==city[4]){
        city[5]=random_range(1,21);
    }
    while(city[6]==0 || city[6]==city[1] || city[6]==city[2] || city[6]==city[3] || city[6]==city[4] || city[6]==city[5]){
        city[6]=random_range(1,21);
    }
    while(city[7]==0 || city[7]==city[1] || city[7]==city[2] || city[7]==city[3] || city[7]==city[4] || city[7]==city[5] || city[7]==city[6]){
        city[7]=random_range(1,21);
    }
    while(city[8]==0 || city[8]==city[1] || city[8]==city[2] || city[8]==city[3] || city[8]==city[4] || city[8]==city[5] || city[8]==city[6] || city[8]==city[7]){
        city[8]=random_range(1,21);
    }

    /**Generate first city's item prices:*/
    set_item_prices();

    /**Get the player's name.*/
    get_name();

    get_max_days();

    /**Reset the selection bar.*/
    b_select_menu.box.x=-1;

    /**Display the beginning of game story:*/
    switch(world_scenario){
        case 0:
        msg1="The evil warlord ";
        msg1+=world_evil;
        msg1+=" has conquered the kingdom of ";
        msg1+=world_other_kingdom;
        msg1+=".";
        msg2="His vast armies have now been spotted marching upon your homeland of ";
        msg2+=world_homeland;
        msg2+="!";
        msg3="The renowned hero, ";
        msg3+=world_hero;
        msg3+=", has embarked on an adventure to defeat the evil ";
        msg3+=world_evil;
        msg3+=".";
        msg4="You have other fish to fry, however. You have just taken out a loan so that you can open";
        msg5="your very own item shop. You want to travel the world, seeking your fortune in exotic goods.";
        msg6="On the course of your journey, you will have to make a decision:";
        msg7="Which side is more profitable: good or evil?";
        msg8="And which side will you choose?";
        new_game_dialog_message();
        break;
        case 1:
        msg1="The evil warlord ";
        msg1+=world_evil;
        msg1+=" has killed ";
        msg1+=world_king;
        msg1+=", king of ";
        msg1+=world_other_kingdom;
        msg1+="!";
        msg2="He has seized the throne, and now begins to threaten your own homeland of ";
        msg2+=world_homeland;
        msg2+="!";
        msg3="The renowned hero, ";
        msg3+=world_hero;
        msg3+=", has embarked on an adventure to defeat the evil ";
        msg3+=world_evil;
        msg3+=".";
        msg4="You have other fish to fry, however. You have just taken out a loan so that you can open";
        msg5="your very own item shop. You want to travel the world, seeking your fortune in exotic goods.";
        msg6="On the course of your journey, you will have to make a decision:";
        msg7="Which side is more profitable: good or evil?";
        msg8="And which side will you choose?";
        new_game_dialog_message();
        break;
        case 2:
        msg1="The evil wizard ";
        msg1+=world_evil;
        msg1+=" has loosed a plague of undeath upon your homeland of ";
        msg1+=world_homeland;
        msg1+="!";
        msg2="Everywhere, people are dying, and then rising again as undead servants to ";
        msg2+=world_evil;
        msg2+=".";
        msg3="The renowned hero, ";
        msg3+=world_hero;
        msg3+=", has embarked on an adventure to defeat the evil ";
        msg3+=world_evil;
        msg3+=".";
        msg4="You have other fish to fry, however. You have just taken out a loan so that you can open";
        msg5="your very own item shop. You want to travel the world, seeking your fortune in exotic goods.";
        msg6="On the course of your journey, you will have to make a decision:";
        msg7="Which side is more profitable: good or evil?";
        msg8="And which side will you choose?";
        new_game_dialog_message();
        break;
        case 3:
        msg1="The evil wizard ";
        msg1+=world_evil;
        msg1+=" has begun collecting the pieces of the ";
        msg1+=world_artifact;
        msg1+=".";
        msg2="If he succeeds in collecting all of the pieces, he will become unstoppable!";
        msg3="The renowned hero, ";
        msg3+=world_hero;
        msg3+=", has embarked on an adventure to defeat the evil ";
        msg3+=world_evil;
        msg3+=".";
        msg4="You have other fish to fry, however. You have just taken out a loan so that you can open";
        msg5="your very own item shop. You want to travel the world, seeking your fortune in exotic goods.";
        msg6="On the course of your journey, you will have to make a decision:";
        msg7="Which side is more profitable: good or evil?";
        msg8="And which side will you choose?";
        new_game_dialog_message();
        break;
    }

    game_loop();
}

void end_game(){
    game_in_progress=false;

    //Update the scores and display the high scores screen:
    scores_load();
    long final_score=gold+savings-(debt*1.5);//The final score that needs to be checked against the high scores.
    for(int x=9;x>-1;x--){
        if(final_score>=score[x]){
            long temp_score=score[x];
            long temp_score_days=score_days[x];
            long temp_score_level=score_level[x];
            string temp_score_name=score_name[x];
            score[x]=final_score;
            score_days[x]=days_max;
            score_level[x]=level;
            score_name[x]=name;
            final_score=temp_score;
            days_max=temp_score_days;
            level=temp_score_level;
            name=temp_score_name;
        }
    }

    scores_save();
    scores_display();

    main_menu();
}
