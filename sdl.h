/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#ifndef sdl_h
#define sdl_h

#include <string>

#include <SDL.h>
#include <SDL_image.h>

/**This little function loads an image, and then returns the optimized version of that image. We are going to use it instead of IMG_Load to load images in the program.*/
SDL_Surface *load_image(std::string filename);

/**x offset, y offset, source surface, destination surface, clipping SDL_Rect, change offsets to center source surface somewhere?*/
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* surface_clip,int centered);

void msg_write(int a,int b,int font_size,std::string msg,int centered);

/**Here we initialize all of the SDL stuff.*/
bool init();

bool load_files();

void clean_up();

#endif
