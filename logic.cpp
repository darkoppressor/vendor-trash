/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include "logic.h"
#include "variables.h"
#include "random_number_generator.h"
#include "random_events.h"
#include "bank.h"
#include "world.h"
#include "battle.h"

using namespace std;

void tick(){
    /**Subtract travel costs:*/
    int costs=random_range(1,3);/**The costs of travel to be subtracted this tick.*/
    if(gold>=costs){/**If there is enough gold to cover the costs, simply subtract costs from gold.*/
        gold=gold-costs;
        costs=0;/**We set costs back to 0 after using it so the following two checks that also use it will be skipped.*/
    }
    if(gold<costs && savings>=costs){/**If there is not enough gold to cover the costs, but there is enough money in savings, subtract costs from savings.*/
        savings=savings-costs;
        costs=0;
    }
    if(gold<costs && savings<costs){/**If there is not enough gold or savings to cover the costs, add costs to debt.*/
        debt=debt+costs;
        costs=0;
    }
    /**Add health:*/
    int health_to_regain=1;/**Base health to be regained this tick.*/
    if(health<health_max){/**If health is less than max health.*/
        health_to_regain+=stamina*.5;
        health+=health_to_regain;
    }
    /**Check to see if health has gone above max health. If so, set health to max health.*/
    if(health>health_max){
        health=health_max;
    }
    /**Advance clock six hours. Thus, 1 real second = 6 game hours.*/
    world_hour+=6;
    if(world_hour>23){
        world_hour-=23;
        world_day++;
        days++;
        interest();
    }
    if(world_day>30){
        world_day-=30;
        world_month++;
    }
    if(world_month>12){
        world_month-=12;
        world_year++;
    }
    /**Random good_vs_evil fluctuation:*/
    int x=random_range(0,99);
    if(x<50){/**50% chance that good_vs_evil will fluctuate. Technically less, as there is a possibility that 0 will be added to good_vs_evil.*/
        good_vs_evil+=random_range(-2,2);
    }
    /**Random World Events:*/
    x=random_range(0,99);/**Set the variable to determine whether any world event should occur.*/
    if(x<25){/**There is a 25% chance that some world event will be triggered.*/
        x=random_range(0,99);/**A world event has been triggered, now determine which one should be triggered.*/
        if(x<5){/**There is a 5% chance that a moral decision dialog will be displayed.*/
            /**Stop the player's movement.*/
            character.move_state=0;
            moral_dialog();/**Display the moral dialog.*/
        }
        if(x>=5 && x<55){/**There is a 50% chance that a battle will occur.*/
            /**Stop the player's movement.*/
            character.move_state=0;
            battle();
        }
        if(x>=55 && x<60){/**There is a 5% chance that a world good vs. evil event will occur.*/
            /**Stop the player's movement.*/
            character.move_state=0;
            good_vs_evil_dialog();/**Display the good vs. evil event dialog.*/
        }
        if(x>=60){/**There is a 40% chance that something will be lost or found.*/
            character.move_state=0;
            found_something();
        }
    }
    /**good_vs_evil can be anywhere from -100 to 100.*/
    if(good_vs_evil<-100){/**If good_vs_evil has gone beyond the minimum value, set it to the minimum value.*/
        good_vs_evil=-100;
    }
    if(good_vs_evil>100){/**If good_vs_evil has gone beyond the maximum value, set it to the maximum value.*/
        good_vs_evil=100;
    }
}

void movement(Uint32 delta_ticks){
    character.move(delta_ticks);
    character.handle_events(delta_ticks);
    cloud1.move(delta_ticks);
    cloud2.move(delta_ticks);
    cloud3.move(delta_ticks);
}

void movement_other(Uint32 delta_ticks){
    cloud1.move(delta_ticks);
    cloud2.move(delta_ticks);
    cloud3.move(delta_ticks);
}

void hit_detection(){
    if(check_collision(character.x,character.y,character.w,character.h,city1.hitbox)){
        character.move_state=0;
        current_city=1;
    }
    if(check_collision(character.x,character.y,character.w,character.h,city2.hitbox)){
        character.move_state=0;
        current_city=2;
    }
    if(check_collision(character.x,character.y,character.w,character.h,city3.hitbox)){
        character.move_state=0;
        current_city=3;
    }
    if(check_collision(character.x,character.y,character.w,character.h,city4.hitbox)){
        character.move_state=0;
        current_city=4;
    }
    if(check_collision(character.x,character.y,character.w,character.h,city5.hitbox)){
        character.move_state=0;
        current_city=5;
    }
    if(check_collision(character.x,character.y,character.w,character.h,city6.hitbox)){
        character.move_state=0;
        current_city=6;
    }
    if(check_collision(character.x,character.y,character.w,character.h,city7.hitbox)){
        character.move_state=0;
        current_city=7;
    }
    if(check_collision(character.x,character.y,character.w,character.h,city8.hitbox)){
        character.move_state=0;
        current_city=8;
    }
}

void animation(Uint32 delta_ticks_anim){
    character.animate(delta_ticks_anim);
    animate_waves(delta_ticks_anim);
    animate_lighthouse(delta_ticks_anim);
}

bool check_collision(int a_x, int a_y, int a_w, int a_h, SDL_Rect b){
    /**The sides of the rectangles.*/
    int left_a,left_b;
    int right_a,right_b;
    int top_a,top_b;
    int bottom_a,bottom_b;

    /**Calculate the sides of rect A.*/
    left_a=a_x;
    right_a=a_x + a_w;
    top_a=a_y;
    bottom_a=a_y + a_h;

    /**Calculate the sides of rect B.*/
    left_b=b.x;
    right_b=b.x + b.w;
    top_b=b.y;
    bottom_b=b.y + b.h;

    /**Check each side of a.  If it is found to be outside of b, these two squares are not colliding, so return false.*/
    if(bottom_a<=top_b){
        return false;
    }
    if(top_a>=bottom_b){
        return false;
    }
    if(right_a<=left_b){
        return false;
    }
    if(left_a>=right_b){
        return false;
    }

    /**If none of the sides from a are outside b.*/
    return true;
}
