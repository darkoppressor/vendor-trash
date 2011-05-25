/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include "world.h"
#include "variables.h"
#include "sdl.h"

#include <SDL.h>

using namespace std;

Hitbox::Hitbox(int get_x,int get_y){
    box.x=get_x;
    box.y=get_y;
    box.w=30;
    box.h=30;
}

void animate_waves(Uint32 delta_ticks_anim){
    anim_waves_counter+=delta_ticks_anim;/**Add the time since last call to animate_waves() to the counter.*/
    while(anim_waves_counter>=800){/**While the counter is more than our maximum milliseconds per frame, keep decrementing it by the maximum ms/frame.  Each time we decrease our counter,
                        we also increment the current frame by 1.*/
        anim_waves_counter-=800;
        anim_waves_frame++;/**Increment the frame.*/
        /**Keep the animation looping.*/
        if(anim_waves_frame>1){
            anim_waves_frame=0;
        }
    }
}

void animate_lighthouse(Uint32 delta_ticks_anim){
    anim_lighthouse_counter+=delta_ticks_anim;/**Add the time since last call to animate_waves() to the counter.*/
    while(anim_lighthouse_counter>=1100){/**While the counter is more than our maximum milliseconds per frame, keep decrementing it by the maximum ms/frame.  Each time we decrease our counter,
                        we also increment the current frame by 1.*/
        anim_lighthouse_counter-=1100;
        anim_lighthouse_frame++;/**Increment the frame.*/
        /**Keep the animation looping.*/
        if(anim_lighthouse_frame>3){
            anim_lighthouse_frame=0;
        }
    }
}

void Hitbox::show(){
    apply_surface(box.x,box.y,hitbox,screen,NULL,0);
}
