/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#ifndef city_h
#define city_h

void city_screen();

class City{
    private:
    public:
    City(int x,int y,int make_city);/**Initializes the variables.*/
    void show();/**Shows the city on the screen.*/

    SDL_Rect hitbox;/**The collision box of the city.*/

    int which_city;/**This corresponds with cities stored in city[].*/
};

#endif
