/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#ifndef world_h
#define world_h

#include <SDL.h>

class Hitbox{
    private:
    public:
    Hitbox(int get_x,int get_y);
    void show();
    SDL_Rect box;
};

void animate_waves(Uint32 delta_ticks_anim);

void animate_lighthouse(Uint32 delta_ticks_anim);

#endif
