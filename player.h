/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#ifndef player_h
#define player_h

#include <SDL.h>

class Player{
    private:
    int frame,status;/**Current frame and its animation status.*/
    float counter;/**Using the delta timer from main.cpp, counter keeps track of how many milliseconds it has been since the last frame update.*/

    public:
    Player();/**Initializes the variables.*/
    void handle_input();/**Takes key presses and adjusts the player's velocity.*/
    void move(Uint32 delta_ticks);/**Move the player.*/
    void handle_events(Uint32 delta_ticks);
    void animate(Uint32 delta_ticks_anim);/**Animate the player.*/
    void show();/**Shows the player on the screen.*/
    int move_state;/**Current state of movement for the player.*/
    float x,y;/**Player's location.*/
    int w,h;/**Player's dimensions.*/
};

#endif
