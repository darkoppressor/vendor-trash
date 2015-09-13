/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include "battle.h"
#include "buttons.h"
#include "variables.h"
#include "screen_draw.h"
#include "input.h"
#include "dialog.h"
#include "random_number_generator.h"
#include "logic.h"
#include "stats.h"

#include <string>

#include <SDL.h>

using namespace std;

void battle(){
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,100);

    bool loop=true;
    /**Reset the selection bar.*/
    b_select_menu.box.x=-1;

    Timer delta;
    delta.start();/**Start the delta timer.*/

    turn=true;/**The player takes the first turn.*/
    int dmg=0;/**Used when determining how much damage the enemy does.*/
    string temp_msg="";
    /**Generate the enemy:*/
    int x=random_range(0,26);
    if(x==0){
        enemy_name="ferocious wolf";
        enemy_health_max=health_max*.25+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.25+random_range(level,level*2);
        enemy_experience=random_range(1,(level*25))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(5,10)+random_range(enemy_health_max*.1,enemy_health_max*.25);
    }
    if(x==1){
        enemy_name="slinking bandit";
        enemy_health_max=health_max*.30+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.30+random_range(level,level*2);
        enemy_experience=random_range(1,(level*26))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(10,15)+random_range(enemy_health_max*.2,enemy_health_max*.25);
    }
    if(x==2){
        enemy_name="thieving footpad";
        enemy_health_max=health_max*.35+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.35+random_range(level,level*2);
        enemy_experience=random_range(1,(level*27))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(15,20)+random_range(enemy_health_max*.25,enemy_health_max*.3);
    }
    if(x==3){
        enemy_name="highwayman";
        enemy_health_max=health_max*.40+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.40+random_range(level,level*2);
        enemy_experience=random_range(1,(level*28))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(20,25)+random_range(enemy_health_max*.3,enemy_health_max*.35);
    }
    if(x==4){
        enemy_name="swarm of killer bees";
        enemy_health_max=health_max*.45+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.45+random_range(level,level*2);
        enemy_experience=random_range(1,(level*29))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(25,30)+random_range(enemy_health_max*.35,enemy_health_max*.4);
    }
    if(x==5){
        enemy_name="minion of ";
        enemy_name+=world_evil;
        enemy_health_max=health_max*.50+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.50+random_range(level,level*2);
        enemy_experience=random_range(1,(level*30))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(30,35)+random_range(enemy_health_max*.4,enemy_health_max*.45);
    }
    if(x==6){
        enemy_name="soldier of ";
        enemy_name+=world_evil;
        enemy_health_max=health_max*.55+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.55+random_range(level,level*2);
        enemy_experience=random_range(1,(level*31))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(35,40)+random_range(enemy_health_max*.45,enemy_health_max*.5);
    }
    if(x==7){
        enemy_name="hand of ";
        enemy_name+=world_evil;
        enemy_health_max=health_max*.60+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.60+random_range(level,level*2);
        enemy_experience=random_range(1,(level*32))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(40,45)+random_range(enemy_health_max*.5,enemy_health_max*.55);
    }
    if(x==8){
        enemy_name="innocent looking bunny";
        enemy_health_max=health_max*.1+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.65+random_range(level,level*2);
        enemy_experience=random_range(1,(level*30))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(30,35)+random_range(enemy_health_max*.3,enemy_health_max*.35);
    }
    if(x==9){
        enemy_name="leprechaun";
        enemy_health_max=health_max*.35+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.25+random_range(level,level*2);
        enemy_experience=random_range(1,(level*20))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(150,200)+random_range(enemy_health_max*.50,enemy_health_max*.75);
    }
    if(x==10){
        enemy_name="zombie";
        enemy_health_max=health_max*.65+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.45+random_range(level,level*2);
        enemy_experience=random_range(1,(level*30))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(35,40)+random_range(enemy_health_max*.45,enemy_health_max*.5);
    }
    if(x==11){
        enemy_name="slime";
        enemy_health_max=health_max*.22+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.22+random_range(level,level*2);
        enemy_experience=random_range(1,(level*22))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(1,4)+random_range(enemy_health_max*.1,enemy_health_max*.14);
    }
    if(x==12){
        enemy_name="snake";
        enemy_health_max=health_max*.20+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.20+random_range(level,level*2);
        enemy_experience=random_range(1,(level*20))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(1,2)+random_range(enemy_health_max*.1,enemy_health_max*.12);
    }
    if(x==13){
        enemy_name="lizard";
        enemy_health_max=health_max*.21+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.21+random_range(level,level*2);
        enemy_experience=random_range(1,(level*21))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(1,3)+random_range(enemy_health_max*.1,enemy_health_max*.13);
    }
    if(x==14){
        enemy_name="rat";
        enemy_health_max=health_max*.23+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.23+random_range(level,level*2);
        enemy_experience=random_range(1,(level*23))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(1,5)+random_range(enemy_health_max*.1,enemy_health_max*.15);
    }
    if(x==15){
        enemy_name="scorpion";
        enemy_health_max=health_max*.24+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.24+random_range(level,level*2);
        enemy_experience=random_range(1,(level*24))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(1,7)+random_range(enemy_health_max*.15,enemy_health_max*.2);
    }
    if(x==16){
        enemy_name="orc";
        enemy_health_max=health_max*.46+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.46+random_range(level,level*2);
        enemy_experience=random_range(1,(level*28))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(30,35)+random_range(enemy_health_max*.38,enemy_health_max*.43);
    }
    if(x==17){
        enemy_name="ghost";
        enemy_health_max=health_max*.56+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.56+random_range(level,level*2);
        enemy_experience=random_range(1,(level*32))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(38,43)+random_range(enemy_health_max*.49,enemy_health_max*.53);
    }
    if(x==18){
        enemy_name="dragon";
        enemy_health_max=health_max*.65+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.65+random_range(level,level*2);
        enemy_experience=random_range(1,(level*35))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(50,55)+random_range(enemy_health_max*.6,enemy_health_max*.65);
    }
    if(x==19){
        enemy_name="kobold";
        enemy_health_max=health_max*.24+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.23+random_range(level,level*2);
        enemy_experience=random_range(1,(level*24))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(10,15)+random_range(enemy_health_max*.2,enemy_health_max*.25);
    }
    if(x==20){
        enemy_name="goblin";
        enemy_health_max=health_max*.23+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.24+random_range(level,level*2);
        enemy_experience=random_range(1,(level*26))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(7,12)+random_range(enemy_health_max*.17,enemy_health_max*.23);
    }
    if(x==21){
        enemy_name="mad cow";
        enemy_health_max=health_max*.14+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.14+random_range(level,level*2);
        enemy_experience=random_range(1,(level*14))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(9,14)+random_range(enemy_health_max*.14,enemy_health_max*.19);
    }
    if(x==22){
        enemy_name="angry sheep";
        enemy_health_max=health_max*.12+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.12+random_range(level,level*2);
        enemy_experience=random_range(1,(level*12))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(7,12)+random_range(enemy_health_max*.12,enemy_health_max*.17);
    }
    if(x==23){
        enemy_name="tiny turtle";
        enemy_health_max=health_max*.10+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.10+random_range(level,level*2);
        enemy_experience=random_range(1,(level*10))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(5,10)+random_range(enemy_health_max*.1,enemy_health_max*.15);
    }
    if(x==24){
        enemy_name="wild hog";
        enemy_health_max=health_max*.16+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.16+random_range(level,level*2);
        enemy_experience=random_range(1,(level*16))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(11,16)+random_range(enemy_health_max*.16,enemy_health_max*.21);
    }
    if(x==25){
        enemy_name="forest spider";
        enemy_health_max=health_max*.25+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.25+random_range(level,level*2);
        enemy_experience=random_range(1,(level*25))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(5,10)+random_range(enemy_health_max*.1,enemy_health_max*.25);
    }
    if(x==26){
        enemy_name="mimic";
        enemy_health_max=health_max*1.5+random_range(level,level*2);
        enemy_health=enemy_health_max;
        enemy_attack=random_range(level*.5,level*.75)*.60+random_range(level,level*2);
        enemy_experience=random_range(1,(level*36))+random_range(enemy_health_max*.5,enemy_health_max);
        enemy_gold=random_range(70,75)+random_range(enemy_health_max*.75,enemy_health_max*1);
    }

    /**Display a dialog message telling the player they are under attack.*/
    msg1="A ";
    msg1+=enemy_name;
    msg1+=" leaps out to attack you!";
    world_dialog_message();

    while(loop==true){
        input_battle();

        if(enemy_health<1){/**If the enemy is dead.*/
            experience+=enemy_experience;
            gold+=enemy_gold;
            msg1="You have slain the ";
            msg1+=enemy_name;
            msg1+="!";
            msg2="You gain ";
            ss.clear();ss.str("");ss<<enemy_experience;ss>>temp_msg;
            msg2+=temp_msg;
            msg2+=" experience!";
            msg3="You loot ";
            ss.clear();ss.str("");ss<<enemy_gold;ss>>temp_msg;
            msg3+=temp_msg;
            msg3+=" gold!";
            world_dialog_message();
            if(health<1){/**If it was a narrow victory.*/
                health=1;
            }
            level_check();
            battles_won++;
            confirm=true;
        }
        if(health<1){/**If the player is dead.*/
            health=health_max;/**Restore the player's health.*/
            long gold_lost=random_range(200,1000)+random_range(gold*.01,gold*.2);
            long experience_lost=random_range(experience*.5,experience);
            gold-=gold_lost;/**Take between 1% and 20% (and a little something extra) of the player's gold as a death penalty.*/
            experience-=experience_lost;/**Take between 50% and 100% of experience towards the next level.*/
            current_city=last_city;/**Send the player back to the last city they visited.*/
            /**Return the player to their home coordinates:*/
            character.x=home_x;
            character.y=home_y;
            msg1="You have been slain by the ";
            msg1+=enemy_name;
            msg1+="!";
            msg2="You feel ";
            ss.clear();ss.str("");ss<<experience_lost;ss>>temp_msg;
            msg2+=temp_msg;
            msg2+=" points of experience slipping away...";
            msg3="You slowly open your eyes to find yourself in a temple.";
            msg4="The priestess requests a donation of ";
            ss.clear();ss.str("");ss<<gold_lost;ss>>temp_msg;
            msg4+=temp_msg;
            msg4+=" gold for her services.";
            if(gold<0){/**If you didn't have enough gold to pay the penalty.*/
                gold=0;
                msg5="You haven't enough gold, but you donate what little you have.";
            }
            world_dialog_message();
            battles_lost++;
            confirm=true;
        }

        if(confirm==true){
            confirm=false;
            /**Reset the selection bar.*/
            b_select_menu.box.x=-1;
            return;
        }
        if(turn==false){/**If it is the enemy's turn.*/
            if(enemy_health<(enemy_health_max*.25)){/**If enemy has less than 25% health.*/
                x=random_range(0,99);
                if(x<1){/**1% chance that the enemy will flee.*/
                    msg1="The ";
                    msg1+=enemy_name;
                    msg1+=" turns and flees in terror!";
                    world_dialog_message();
                    confirm=true;
                }
                if(x==42){/**1% chance that the enemy will use a health potion.*/
                    enemy_health+=random_range(1,50);
                    if(enemy_health>enemy_health_max){
                        enemy_health=enemy_health_max;/**If the enemy's health exceeds the max, set it to the max.*/
                    }
                    msg1="The ";
                    msg1+=enemy_name;
                    msg1+=" gulps down a health potion!";
                    world_dialog_message();
                    turn=true;/**It's the player's turn again.*/
                }
            }
            if(turn==false && confirm==false){/**If the enemy still has a chance to attack, do that now.*/
                dmg=random_range(1,3)+random_range(enemy_attack,enemy_attack+(enemy_attack*.5))-equip_defense;
                if(dmg<0){
                    dmg=0;
                }
                health-=dmg;
            }
            turn=true;/**It is the player's turn again.*/
        }
        movement_other(delta.get_ticks());
        animation(delta.get_ticks());
        delta.start();/**Restart delta timer.*/
        draw();
        draw_battle();
    }
}
