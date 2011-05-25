/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include "string_input.h"
#include "variables.h"
#include "sdl.h"

#include "quit.h"

using namespace std;

string_input::string_input(){
    str="Vendor";
    text=NULL;
    SDL_EnableUNICODE(SDL_ENABLE);/**Enable unicode.*/
}

string_input::~string_input(){
    SDL_FreeSurface(text);
    SDL_EnableUNICODE(SDL_DISABLE);/**Disable unicode*/
}

void string_input::handle_events(){
    if(event.type==SDL_KEYDOWN){
        string temp=str;/**Keep a copy of the current version of the string.*/
        if(str.length()<16){/**If the string is less than the maximum size.*/
            //if(event.key.keysym.unicode==(Uint16)' '){/**If the key is a space.*/
            //    str+=(char)event.key.keysym.unicode;
            //}
            if(event.key.keysym.unicode>=(Uint16)'A' && event.key.keysym.unicode<=(Uint16)'Z'){/**If the key is a capital letter.*/
                str+=(char)event.key.keysym.unicode;
            }
            else if(event.key.keysym.unicode>=(Uint16)'a' && event.key.keysym.unicode<=(Uint16)'z'){/**If the key is a lowercase letter.*/
                str+=(char)event.key.keysym.unicode;
            }
        }
        if(event.key.keysym.sym==SDLK_BACKSPACE && str.length()!=0){/**If the backspace key is pressed and the string is not empty.*/
            str.erase(str.length()-1);/**Remove one character from the end of the string.*/
        }
        if(str!=temp){/**If the string has been changed.*/
            /**Free the old surface and render a new text surface to display the changed string.*/
            SDL_FreeSurface(text);
            text=TTF_RenderText_Solid(font_42,str.c_str(),text_color);
        }
        if(event.key.keysym.sym==SDLK_RETURN && str.length()!=0){/**If the player hits enter, and the string has at least one character.*/
            //Make sure that enter is cleared before moving to the next screen.
            Uint8 *keystates=SDL_GetKeyState(NULL);/**Get keystates.*/
            keystates[SDLK_RETURN]=NULL;

            confirm=true;
            name=str;
        }
    }
}

void string_input::show(){
    if(text==NULL){
        text=TTF_RenderText_Solid(font_42,str.c_str(),text_color);
    }
    if(text!=NULL){/**If the surface is not blank.*/
        apply_surface(0,(SCREEN_HEIGHT-text->h)/2,text,screen,NULL,1);/**Show the name.*/
    }
}
