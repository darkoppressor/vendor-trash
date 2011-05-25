/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#ifndef logic_h
#define logic_h

#include <SDL.h>

void tick();/**Is called every 1 second that the player is traveling on the world map. Adds health, mana, subtracts gold, etc.*/

void movement(Uint32 delta_ticks);

void movement_other(Uint32 delta_ticks);/**Enables clouds moving even while player is in a city, reading a dialog message, etc.*/

void hit_detection();

void animation(Uint32 delta_ticks_anim);

bool check_collision(int a_x, int a_y, int a_w, int a_h, SDL_Rect b);

#endif
