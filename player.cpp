/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include "player.h"
#include "variables.h"
#include "sdl.h"
#include "logic.h"/**Player::move() needs check_collision().*/

using namespace std;

Player::Player(){
    /**Set the player's location.*/
    x=0;
    y=0;

    /**Set the hitbox's dimensions.*/
    w=PLAYER_WIDTH;
    h=PLAYER_HEIGHT;

    move_state=0;

    frame=0;
    status=PLAYER_DOWN;
    counter=0;/**Set the counter to 0.*/
}

void Player::handle_input(){
    Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
    /**Handle input.*/
    if(keystates[SDLK_LEFT]){
        move_state=PLAYER_LEFT;
    }
    if(keystates[SDLK_UP]){
        move_state=PLAYER_UP;
    }
    if(keystates[SDLK_RIGHT]){
        move_state=PLAYER_RIGHT;
    }
    if(keystates[SDLK_DOWN]){
        move_state=PLAYER_DOWN;
    }
    if(keystates[SDLK_LEFT] && keystates[SDLK_UP]){
        move_state=PLAYER_LEFTUP;
    }
    if(keystates[SDLK_RIGHT] && keystates[SDLK_UP]){
        move_state=PLAYER_RIGHTUP;
    }
    if(keystates[SDLK_RIGHT] && keystates[SDLK_DOWN]){
        move_state=PLAYER_RIGHTDOWN;
    }
    if(keystates[SDLK_LEFT] && keystates[SDLK_DOWN]){
        move_state=PLAYER_LEFTDOWN;
    }
    if(keystates[SDLK_LEFT] && keystates[SDLK_RIGHT]){
        move_state=PLAYER_LEFT;
    }
    if(keystates[SDLK_UP] && keystates[SDLK_DOWN]){
        move_state=PLAYER_UP;
    }
    if(keystates[SDLK_LEFT] && keystates[SDLK_UP] && keystates[SDLK_RIGHT]){
        move_state=PLAYER_LEFTUP;
    }
    if(keystates[SDLK_LEFT] && keystates[SDLK_DOWN] && keystates[SDLK_RIGHT]){
        move_state=PLAYER_LEFTDOWN;
    }
    if(keystates[SDLK_LEFT] && keystates[SDLK_UP] && keystates[SDLK_DOWN]){
        move_state=PLAYER_LEFTUP;
    }
    if(keystates[SDLK_UP] && keystates[SDLK_RIGHT] && keystates[SDLK_DOWN]){
        move_state=PLAYER_RIGHTUP;
    }
    if(keystates[SDLK_LEFT] && keystates[SDLK_UP] && keystates[SDLK_RIGHT] && keystates[SDLK_DOWN]){
        move_state=PLAYER_LEFTUP;
    }
    if(!keystates[SDLK_LEFT] && !keystates[SDLK_UP] && !keystates[SDLK_RIGHT] && !keystates[SDLK_DOWN]){
        move_state=0;
    }
}

void Player::move(Uint32 delta_ticks){
    if(move_state==PLAYER_LEFT){
        x-=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the x axis.*/
    }
    if(move_state==PLAYER_UP){
        y-=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the y axis.*/
    }
    if(move_state==PLAYER_RIGHT){
        x+=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the x axis.*/
    }
    if(move_state==PLAYER_DOWN){
        y+=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the y axis.*/
    }
    if(move_state==PLAYER_LEFTUP){
        x-=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the x axis.*/
        y-=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the y axis.*/
    }
    if(move_state==PLAYER_RIGHTUP){
        x+=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the x axis.*/
        y-=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the y axis.*/
    }
    if(move_state==PLAYER_RIGHTDOWN){
        x+=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the x axis.*/
        y+=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the y axis.*/
    }
    if(move_state==PLAYER_LEFTDOWN){
        x-=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the x axis.*/
        y+=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the y axis.*/
    }

    /**Keep the player in bounds:*/
    if(x<0){/**If the player went too far to the left.*/
        x=0;/**Move back.*/
    }
    else if(x+PLAYER_WIDTH>SCREEN_WIDTH){/**If the player went too far to the right.*/
        x=SCREEN_WIDTH-PLAYER_WIDTH;/**Move back.*/
    }
    if(y<0){/**If the player went too far up.*/
        y=0;/**Move back.*/
    }
    else if(y+PLAYER_HEIGHT>SCREEN_HEIGHT){/**If the player went too far down.*/
        y=SCREEN_HEIGHT-PLAYER_HEIGHT;/**Move back.*/
    }
}

void Player::handle_events(Uint32 delta_ticks){
    bool reverse=false;
    for(int i=0;i<hitboxes.size();i++){
        if(check_collision(x+5,y+5,w-10,h-10,hitboxes.at(i).box)){
            reverse=true;
        }
    }
    if(reverse==true){
        if(move_state==PLAYER_LEFT){
            x+=(PLAYER_SPEED * (delta_ticks/1000.0f));
        }
        if(move_state==PLAYER_RIGHT){
            x-=(PLAYER_SPEED * (delta_ticks/1000.0f));
        }
        if(move_state==PLAYER_UP){
            y+=(PLAYER_SPEED * (delta_ticks/1000.0f));
        }
        if(move_state==PLAYER_DOWN){
            y-=(PLAYER_SPEED * (delta_ticks/1000.0f));
        }
        if(move_state==PLAYER_LEFTUP){
            x+=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the x axis.*/
            y+=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the y axis.*/
        }
        if(move_state==PLAYER_RIGHTUP){
            x-=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the x axis.*/
            y+=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the y axis.*/
        }
        if(move_state==PLAYER_RIGHTDOWN){
            x-=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the x axis.*/
            y-=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the y axis.*/
        }
        if(move_state==PLAYER_LEFTDOWN){
            x+=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the x axis.*/
            y-=(PLAYER_SPEED * (delta_ticks/1000.0f));/**Move the player on the y axis.*/
        }
    }
}

void Player::animate(Uint32 delta_ticks_anim){
    counter+=delta_ticks_anim;/**Add the time since last call to animate() to the counter.*/
    while(counter>=100){/**While the counter is more than our maximum milliseconds per frame, keep decrementing it by the maximum ms/frame.  Each time we decrease our counter,
                        we also increment the current frame by 1.*/
        counter-=100;
        if(move_state!=0){
            status=move_state;
            frame++;
        }
        else{
            frame=0;/**Reset animation.*/
        }
        /**Keep the animation looping.*/
        if(frame>1){
            frame=0;
        }
    }
}

void Player::show(){
    if(status==PLAYER_LEFT)
    apply_surface((int)x,(int)y,player,screen,&clip_player_left[frame],0);
    if(status==PLAYER_UP)
    apply_surface((int)x,(int)y,player,screen,&clip_player_up[frame],0);
    if(status==PLAYER_RIGHT)
    apply_surface((int)x,(int)y,player,screen,&clip_player_right[frame],0);
    if(status==PLAYER_DOWN)
    apply_surface((int)x,(int)y,player,screen,&clip_player_down[frame],0);
    if(status==PLAYER_LEFTUP)
    apply_surface((int)x,(int)y,player,screen,&clip_player_leftup[frame],0);
    if(status==PLAYER_RIGHTUP)
    apply_surface((int)x,(int)y,player,screen,&clip_player_rightup[frame],0);
    if(status==PLAYER_RIGHTDOWN)
    apply_surface((int)x,(int)y,player,screen,&clip_player_rightdown[frame],0);
    if(status==PLAYER_LEFTDOWN)
    apply_surface((int)x,(int)y,player,screen,&clip_player_leftdown[frame],0);
}
