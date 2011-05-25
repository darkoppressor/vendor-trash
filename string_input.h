/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#ifndef string_input_h
#define string_input_h

#include <string>
#include <SDL.h>

class string_input{
    private:
    SDL_Surface *text;/**Text surface.*/
    public:
    std::string str;/**Storage string.*/
    string_input();
    ~string_input();
    void handle_events();
    void show();
};

#endif
