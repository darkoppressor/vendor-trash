/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include "random_events.h"
#include "variables.h"
#include "dialog.h"
#include "random_number_generator.h"

using namespace std;

void found_equipment(){
    equip_found_name="";
    string temp_msg="";
    equip_found_attack=0;
    equip_found_defense=0;
    if(equip_found==1){
        equip_found_name="dagger";
        equip_found_attack=1+random_range(((level*.2)*5),((level*.2)*10));
    }
    if(equip_found==2){
        equip_found_name="longsword";
        equip_found_attack=1+random_range(((level*.2)*11),((level*.2)*20));
    }
    if(equip_found==3){
        equip_found_name="broadsword";
        equip_found_attack=1+random_range(((level*.2)*21),((level*.2)*30));
    }
    if(equip_found==4){
        equip_found_name="warhammer";
        equip_found_attack=1+random_range(((level*.2)*31),((level*.2)*40));
    }
    if(equip_found==5){
        equip_found_name="leather jerkin";
        equip_found_defense=1+random_range(((level*.2)*1),((level*.2)*5));
    }
    if(equip_found==6){
        equip_found_name="suit of bronze";
        equip_found_defense=1+random_range(((level*.2)*6),((level*.2)*10));
    }
    if(equip_found==7){
        equip_found_name="suit of iron";
        equip_found_defense=1+random_range(((level*.2)*11),((level*.2)*15));
    }
    if(equip_found==8){
        equip_found_name="suit of enchanted platemail";
        equip_found_defense=1+random_range(((level*.2)*16),((level*.2)*20));
    }
    msg1="You stumble over something lying in the undergrowth, and stoop down to retrieve it.";
    msg2="You have found a +";
    if(equip_found_defense==0){/**If it is a weapon.*/
        if(equip_attack==0){
            msg3="You do not currently have a weapon equipped.";
        }
        else{
            msg3="Your current weapon is a +";
            ss.clear();ss.str("");ss<<equip_attack;ss>>temp_msg;
            msg3+=temp_msg;
            msg3+=" ";
            msg3+=weapon_name;
            msg3+=".";
        }
        ss.clear();ss.str("");ss<<equip_found_attack;ss>>temp_msg;
    }
    if(equip_found_attack==0){/**If it is armor.*/
        if(equip_defense==0){
            msg3="You do not currently have any armor equipped.";
        }
        else{
            msg3="Your current armor is a +";
            ss.clear();ss.str("");ss<<equip_defense;ss>>temp_msg;
            msg3+=temp_msg;
            msg3+=" ";
            msg3+=armor_name;
            msg3+=".";
        }
        ss.clear();ss.str("");ss<<equip_found_defense;ss>>temp_msg;
    }
    msg2+=temp_msg;
    msg2+=" ";
    msg2+=equip_found_name;
    msg2+="!";
    msg4="What do you want to do?";
    found_dialog_message();
}

void found_something(){
    string temp_msg="";
    int x;
    int lose_or_gain=random_range(0,1);/**Do we lose something or gain something?*/
    if(lose_or_gain==0){/**Ok, we lose something. For now, at least, only gold can be lost.*/
        long gold_lost=random_range(gold*.01,gold*.05);
        gold_lost-=random_range(luck*.5,luck*.75);
        if(gold_lost<0){
            gold_lost=2;
        }
        gold-=gold_lost;/**Subtract between 1% and 5% of the player's gold.*/
        x=random_range(0,2);/**Select a random reason for why the gold was lost.*/
        if(x==0){
            msg1="As you are walking along the road, a gang of bandits ambushes your caravan!";
        }
        if(x==1){
            msg1="While attempting to cross a particularly swampy portion of the trail, your wagon tips!";
        }
        if(x==2){
            msg1="You awaken from a brief nap to find that you have been robbed!";
        }
        msg2="You check your gold reserves, and find that ";
        ss.clear();ss.str("");ss<<gold_lost;ss>>temp_msg;
        msg2+=temp_msg;
        msg2+=" gold pieces are missing!";
        world_dialog_message();
    }
    if(lose_or_gain==1){/**Ok, we find something.*/
        x=random_range(0,1);/**Determine what has been found.*/
        if(x==0){/**Ok, we've found gold.*/
            long gold_found=random_range(500,10000)+random_range(luck*2,luck*5);
            gold+=gold_found;
            msg1="While traveling, you notice a crate lying alongside the road.";
            msg2="Curious, you open the crate and find ";
            ss.clear();ss.str("");ss<<gold_found;ss>>temp_msg;
            msg2+=temp_msg;
            msg2+=" gold pieces inside!";
            world_dialog_message();
        }
        if(x==1){/**Ok, we've found a piece of equipment.*/
            equip_found=random_range(1,8);
            found_equipment();
        }
    }
}

void moral_dialog(){
    int dilemma=random_range(0,3);/**Determine which moral dilemma will be given to the player.*/
    if(dilemma==0){
        /**Set the dialog message.*/
        msg1="You see a cart full of goods on the side of the road.";
        msg2="Further examination reveals that the cart's owner is letting his horse graze nearby.";
        msg3="He appears completely unaware of your presence.";
        msg4="You also notice a purse of gold coins that has been left in the cart.";
        msg5="What do you want to do?";
        /**Set the moral button text.*/
        msg_good="1. Warn the cart's owner that bandits have been seen in the area.";
        msg_neutral="2. Continue on your journey.";
        msg_bad="3. Take the man's gold!";
        re_gold_bad=random_range(1,1000);
        moral_dialog_message();/**Display the dialog message.*/
    }
    if(dilemma==1){
        /**Set the dialog message.*/
        msg1="While traveling, you happen across a man who has been beaten severely.";
        msg2="He begs you for help.";
        msg3="What do you want to do?";
        /**Set the moral button text.*/
        msg_good="1. Bring him along with your caravan to the next town.";
        msg_neutral="2. Assure him that you will send help as soon as you reach the next town.";
        msg_bad="3. Kick him soundly in the stomach and run off, laughing hysterically!";
        moral_dialog_message();/**Display the dialog message.*/
    }
    if(dilemma==2){
        /**Set the dialog message.*/
        msg1="A kind elderly couple has allowed you to stay the night in their home.";
        msg2="Now that you are rested and refreshed, you are preparing to take your leave.";
        msg3="What do you want to do?";
        /**Set the moral button text.*/
        msg_good="1. Thank the couple, and offer them some gold.";
        msg_neutral="2. Thank the couple and head back to the road.";
        msg_bad="3. Set their barn on fire on your way out!";
        re_gold_good=random_range(-1,-500);
        moral_dialog_message();/**Display the dialog message.*/
    }
    if(dilemma==3){
        /**Set the dialog message.*/
        msg1="While traveling, you happen across a man who has fallen asleep alongside the road.";
        msg2="What do you want to do?";
        /**Set the moral button text.*/
        msg_good="1. Wake the man up and warn him that bandits are about.";
        msg_neutral="2. Continue on your journey.";
        msg_bad="3. Rob him blind!";
        re_gold_bad=random_range(1,1000);
        moral_dialog_message();/**Display the dialog message.*/
    }
    re_moral=false;/**We have displayed the moral dialog, and the player has made their choice. This variable is only set to true when used as a City Event.*/
}

void good_vs_evil_dialog(){
    int x=random_range(0,1);/**In what direction will the balance of power be altered?*/
    int change=random_range(8,12);/**How much to alter the balance of power.*/
    int message=random_range(0,3);/**Which message should be displayed?*/
    if(x==0){/**Good has succeeded in something.*/
        good_vs_evil+=change;
        switch(message){
            case 0:
            msg1=world_hero;
            msg1+=" has defeated a group of ";
            msg1+=world_evil;
            msg1+="'s minions!";
            break;
            case 1:
            msg1=world_hero;
            msg1+=" has discovered a powerful artifact!";
            break;
            case 2:
            msg1=world_hero;
            msg1+=" managed to defeat ";
            msg1+=world_evil;
            msg1+=" in battle, but he escaped!";
            break;
            case 3:
            msg1="The people of ";
            msg1+=world_other_kingdom;
            msg1+=" have risen up against ";
            msg1+=world_evil;
            msg1+="!";
            break;
        }
        msg3="The balance of power on Aearun shifts in favor of good.";
        world_dialog_message();
    }
    if(x==1){/**Evil has succeeded in something.*/
        good_vs_evil-=change;
        switch(message){
            case 0:
            msg1=world_evil;
            msg1+=" has defeated ";
            msg1+=world_hero;
            msg1+=" in battle, but he managed to escape!";
            break;
            case 1:
            msg1=world_evil;
            msg1+=" has conquered a town in ";
            msg1+=world_other_kingdom;
            msg1+="!";
            break;
            case 2:
            msg1=world_evil;
            msg1+=" is pillaging farms throughout ";
            msg1+=world_homeland;
            msg1+="!";
            break;
            case 3:
            msg1=world_evil;
            msg1+=" has quelled resistance in ";
            msg1+=world_other_kingdom;
            msg1+=" with a terrifying act!";
            break;
        }
        msg3="The balance of power on Aearun shifts in favor of evil.";
        world_dialog_message();
    }
}

void events_city(){
    if(re_moral==true){/**If a moral dialog needs to be displayed, do so.*/
        moral_dialog();
    }
    int temp_reason=0;/**Used to select a random reason to be displayed, informing the player why a particular city event has occurred.*/
    /**If the city is not trading in some item, let the player know, and give a random reason.*/
    if(re_city_item_zero>0){
        /**Set the name of the item in question.*/
        if(re_city_item_zero==1){
            item_name="weapons";
        }
        if(re_city_item_zero==2){
            item_name="armor";
        }
        if(re_city_item_zero==3){
            item_name="accessories";
        }
        if(re_city_item_zero==4){
            item_name="magical items";
        }
        if(re_city_item_zero==5){
            item_name="revives";
        }
        if(re_city_item_zero==6){
            item_name="mana potions";
        }
        if(re_city_item_zero==7){
            item_name="health potions";
        }
        if(re_city_item_zero==8){
            item_name="antidotes";
        }
        /**Choose a random reason for the item not being available for trade, set the string, and display the message.*/
        temp_reason=random_range(0,3);
        if(temp_reason==0){
            msg1="The citizens of ";
            msg1+=city_name;
            msg1+=" recently received a";
            msg2="plague-infected shipment of ";
            msg2+=item_name;
            msg2+=", and have";
            msg3="instituted a boycott against them in response.";
        }
        if(temp_reason==1){
            msg1="Rumours abound in ";
            msg1+=city_name;
            msg1+=" about a cursed";
            msg2="shipment of ";
            msg2+=item_name;
            msg2+=". To protect the city, a ban has";
            msg3="been declared on all ";
            msg3+=item_name;
            msg3+=".";
        }
        if(temp_reason==2){
            msg1="The ruling council of ";
            msg1+=city_name;
            msg1+=" has placed";
            msg2="a trade ban on all ";
            msg2+=item_name;
            msg2+=" for the time being.";
        }
        if(temp_reason==3){
            msg1="A recent scam involving ";
            msg1+=item_name;
            msg1+=" has caused";
            msg2="quite a bit of turmoil in ";
            msg2+=city_name;
            msg2+=".";
            msg3="As a result, all trade in ";
            msg3+=item_name;
            msg3+=" has been";
            msg4="halted for the foreseeable future.";
        }
        dialog_message();
        re_city_item_zero=0;
    }
    /**If the city is trading some item at a reduced price, let the player know, and give a random reason.*/
    if(re_city_item_cheap>0){
        /**Set the name of the item in question.*/
        if(re_city_item_cheap==1){
            item_name="weapons";
        }
        if(re_city_item_cheap==2){
            item_name="armor";
        }
        if(re_city_item_cheap==3){
            item_name="accessories";
        }
        if(re_city_item_cheap==4){
            item_name="magical items";
        }
        if(re_city_item_cheap==5){
            item_name="revives";
        }
        if(re_city_item_cheap==6){
            item_name="mana potions";
        }
        if(re_city_item_cheap==7){
            item_name="health potions";
        }
        if(re_city_item_cheap==8){
            item_name="antidotes";
        }
        /**Choose a random reason for the item being traded at a reduced rate, set the string, and display the message.*/
        temp_reason=random_range(0,3);
        if(temp_reason==0){
            msg1="A surplus of ";
            msg1+=item_name;
            msg1+=" have flooded the market in ";
            msg1+=city_name;
            msg1+=",";
            msg2="so they are being traded at a reduced rate.";
        }
        if(temp_reason==1){
            msg1="A rumour has begun to spread through ";
            msg1+=city_name;
            msg2="about a cursed shipment of ";
            msg2+=item_name;
            msg2+=". ";
            msg3="Trade in ";
            msg3+=item_name;
            msg3+=" has plummeted as a result.";
        }
        if(temp_reason==2){
            msg1="A wealthy citizen of ";
            msg1+=city_name;
            msg1+=" has donated";
            msg2="a large number of ";
            msg2+=item_name;
            msg2+=" to the city.";
            msg3="Trade in ";
            msg3+=item_name;
            msg3+=" has been reduced as a result.";
        }
        if(temp_reason==3){
            msg1="A den of thieves was recently raided near ";
            msg1+=city_name;
            msg1+=".";
            msg2="A large number of stolen ";
            msg2+=item_name;
            msg2+=" were recovered,";
            msg3="flooding ";
            msg3+=city_name;
            msg3+="'s ";
            msg3+=item_name;
            msg3+=" market.";
            msg4="The price of ";
            msg4+=item_name;
            msg4+=" has plummeted as a result.";
        }
        dialog_message();
        re_city_item_cheap=0;
    }
    /**If the city is trading some item at an increased price, let the player know, and give a random reason.*/
    if(re_city_item_expensive>0){
        /**Set the name of the item in question.*/
        if(re_city_item_expensive==1){
            item_name="weapons";
        }
        if(re_city_item_expensive==2){
            item_name="armor";
        }
        if(re_city_item_expensive==3){
            item_name="accessories";
        }
        if(re_city_item_expensive==4){
            item_name="magical items";
        }
        if(re_city_item_expensive==5){
            item_name="revives";
        }
        if(re_city_item_expensive==6){
            item_name="mana potions";
        }
        if(re_city_item_expensive==7){
            item_name="health potions";
        }
        if(re_city_item_expensive==8){
            item_name="antidotes";
        }
        /**Choose a random reason for the item being traded at an increased rate, set the string, and display the message.*/
        temp_reason=random_range(0,3);
        if(temp_reason==0){
            msg1="A wealthy citizen bought all of the ";
            msg1+=item_name;
            msg2="in ";
            msg2+=city_name;
            msg2+=".";
            msg3="Trade in ";
            msg3+=item_name;
            msg3+=" has skyrocketed as a result.";
        }
        if(temp_reason==1){
            msg1="Rumours abound in ";
            msg1+=city_name;
            msg1+=" about a";
            msg2="shipment of blessed ";
            msg2+=item_name;
            msg2+=".";
            msg3=city_name;
            msg3+="'s ";
            msg3+=item_name;
            msg3+=" market is booming as a result.";
        }
        if(temp_reason==2){
            msg1="There is a severe shortage of ";
            msg1+=item_name;
            msg1+=" in ";
            msg1+=city_name;
            msg1+=".";
            msg2="The price of ";
            msg2+=item_name;
            msg2+=" has skyrocketed as a result.";
        }
        if(temp_reason==3){
            msg1="A recent series of thefts has left ";
            msg1+=city_name;
            msg1+="'s";
            msg2="supply of ";
            msg2+=item_name;
            msg2+=" severely depleted.";
            msg3="Trade in ";
            msg3+=item_name;
            msg3+=" has increased as a result.";
        }
        dialog_message();
        re_city_item_expensive=0;
    }
}

void city_event_notrade(){
    int x=random_range(0,7);/**Determine which item will not be available for trade.*/
    if(x==0){
        price_weapons=0;
        re_city_item_zero=1;
    }
    if(x==1){
        price_armor=0;
        re_city_item_zero=2;
    }
    if(x==2){
        price_accessories=0;
        re_city_item_zero=3;
    }
    if(x==3){
        price_magicalitems=0;
        re_city_item_zero=4;
    }
    if(x==4){
        price_revives=0;
        re_city_item_zero=5;
    }
    if(x==5){
        price_manapotions=0;
        re_city_item_zero=6;
    }
    if(x==6){
        price_healthpotions=0;
        re_city_item_zero=7;
    }
    if(x==7){
        price_antidotes=0;
        re_city_item_zero=8;
    }
}

void city_event_cheaper(){
    int x=random_range(0,7);/**Determine which item will be cheaper.*/
    if(x==0){
        price_weapons-=price_weapons*(random_range(50,75)*.01);/**Subtract between 50% and 75% of the item price from the item price.*/
        re_city_item_cheap=1;
    }
    if(x==1){
        price_armor-=price_armor*(random_range(50,75)*.01);
        re_city_item_cheap=2;
    }
    if(x==2){
        price_accessories-=price_accessories*(random_range(50,75)*.01);
        re_city_item_cheap=3;
    }
    if(x==3){
        price_magicalitems-=price_magicalitems*(random_range(50,75)*.01);
        re_city_item_cheap=4;
    }
    if(x==4){
        price_revives-=price_revives*(random_range(50,75)*.01);
        re_city_item_cheap=5;
    }
    if(x==5){
        price_manapotions-=price_manapotions*(random_range(50,75)*.01);
        re_city_item_cheap=6;
    }
    if(x==6){
        price_healthpotions-=price_healthpotions*(random_range(50,75)*.01);
        re_city_item_cheap=7;
    }
    if(x==7){
        price_antidotes-=price_antidotes*(random_range(50,75)*.01);
        re_city_item_cheap=8;
    }
}

void city_event_more_expensive(){
    int x=random_range(0,7);/**Determine which item will be more expensive.*/
    if(x==0){
        price_weapons+=price_weapons*(random_range(50,75)*.01);/**Add between 50% and 75% of the item price to the item price.*/
        re_city_item_expensive=1;
    }
    if(x==1){
        price_armor+=price_armor*(random_range(50,75)*.01);
        re_city_item_expensive=2;
    }
    if(x==2){
        price_accessories+=price_accessories*(random_range(50,75)*.01);
        re_city_item_expensive=3;
    }
    if(x==3){
        price_magicalitems+=price_magicalitems*(random_range(50,75)*.01);
        re_city_item_expensive=4;
    }
    if(x==4){
        price_revives+=price_revives*(random_range(50,75)*.01);
        re_city_item_expensive=5;
    }
    if(x==5){
        price_manapotions+=price_manapotions*(random_range(50,75)*.01);
        re_city_item_expensive=6;
    }
    if(x==6){
        price_healthpotions+=price_healthpotions*(random_range(50,75)*.01);
        re_city_item_expensive=7;
    }
    if(x==7){
        price_antidotes+=price_antidotes*(random_range(50,75)*.01);
        re_city_item_expensive=8;
    }
}
