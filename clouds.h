/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#ifndef clouds_h
#define clouds_h

#include <SDL.h>

#include "timer.h"

class Cloud{
    private:
    bool exists,cloud_timer,velocity_timer;/**Does this cloud currently exist? Is the cloud spawn timer on or off?*/
    double x,y,velocity,velocity_y;/**Location of cloud. x and y velocity of cloud.*/
    int sprite;
    int direction;/**Current direction of the cloud on the x axis.*/
    int spawn_time;/**Randomly chosen whenever the cloud spawn timer is reset. Time until the cloud spawns.*/
    int width,height;/**The width and height of the cloud.*/
    int velocity_time;/**How long to wait before velocity change.*/

    Timer timer_spawn;/**When this timer reaches spawn_time, we spawn the cloud.*/
    Timer timer_velocity;/**When this timer reaches velocity_time, we change the cloud's y velocity.*/

    public:
    Cloud();
    void move(Uint32 delta_ticks);
    void show();
};

#endif
