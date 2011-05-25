/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include <SDL.h>

#include "clouds.h"
#include "timer.h"
#include "variables.h"
#include "sdl.h"
#include "random_number_generator.h"

using namespace std;

Cloud::Cloud(){
    exists=false;
    cloud_timer=false;
    velocity_timer=false;
    x=0;
    y=0;
    sprite=0;
    direction=0;
    velocity=0;
    velocity_y=0;
    spawn_time=0;
    width=0;
    height=0;
    velocity_y=0;
    velocity_time=0;
}

/**If this is called and the cloud does not exist, create it. Then move the cloud.*/
void Cloud::move(Uint32 delta_ticks){
    /**If the cloud does not exist and the timer is off, start the timer.*/
    if(exists==false && cloud_timer==false){
        cloud_timer=true;
        spawn_time=random_range(15000,60000);
        timer_spawn.start();/**Start the cloud spawn timer.*/
    }

    /**If the cloud does not exist, and the timer is on and has passed the maximum(spawn_time), spawn the cloud.*/
    if(exists==false && cloud_timer==true && timer_spawn.get_ticks()>spawn_time){
        cloud_timer=false;
        timer_spawn.stop();/**Stop the cloud spawn timer.*/
        exists=true;

        width=40;
        height=25;

        direction=random_range(0,1);
        if(direction==0){
            x=0-width;
            velocity=(int)random_range(15,20);
        }
        else if(direction==1){
            x=SCREEN_WIDTH;
            velocity=-1 * (int)random_range(15,20);
        }
        y=random_range(0,SCREEN_HEIGHT/2);/**Set the cloud's y coordinate.*/
        sprite=random_range(0,3);
    }

    /**The rest of the function handles the cloud once it exists.*/
    x+=velocity * (delta_ticks/1000.f);/**Actually move the cloud on the x axis.*/

    /**If the cloud exists and the velocity timer is off, turn it on. This timer */
    if(exists==true && velocity_timer==false){
        velocity_timer=true;
        velocity_time=random_range(10000,15000);
        timer_velocity.start();
    }

    /**If the cloud exists and the velocity timer is on and has passed the maximum(velocity_change), change the y velocity.*/
    if(exists==true && velocity_timer==true && timer_velocity.get_ticks()>velocity_time){
        velocity_timer=false;
        timer_velocity.stop();
        velocity_y=random_range(0,2);
    }
    if(velocity_y==0){
        y+=-5 * (delta_ticks/1000.f);/**Move the cloud up on the y axis.*/
    }
    if(velocity_y==1){
        y+=5 * (delta_ticks/1000.f);/**Move the cloud down on the y axis.*/
    }

    /**If the cloud goes off the edge of the screen, despawn the cloud.*/
    if(x+width<0 && direction==1)
    exists=false;
    if(x>SCREEN_WIDTH && direction==0)
    exists=false;
    if(y+height<0)
    exists=false;
    if(y>SCREEN_HEIGHT)
    exists=false;
}

void Cloud::show(){
    if(exists==true){
        apply_surface((int)x,(int)y,clouds,screen,&clip_clouds[sprite],0);/**Apply the cloud to the screen.*/
    }
}
