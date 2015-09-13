/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#ifndef buttons_h
#define buttons_h

#include <SDL.h>

class Selection_Menu{
    private:
    public:
    Selection_Menu(int x,int y,int w,int h);
    void show();
    SDL_Rect box;
};

class Selection_Item{
    private:
    public:
    Selection_Item(int x,int y,int w,int h);
    void show();
    SDL_Rect box;
};

class Menu_Button{
    private:
    SDL_Rect box;
    int button;

    public:
    /**Initialize the variables.*/
    Menu_Button(int x,int y,int w,int h,int which_button);
    void handle_events();
};

class Battle_Button{
    private:
    SDL_Rect box;
    int button;

    public:
    /**Initialize the variables.*/
    Battle_Button(int x,int y,int w,int h,int which_button);
    void handle_events();
};

class Options_Button{
    private:
    /**The attributes of the button.*/
    SDL_Rect box;
    /**The part of the button sprite sheet that will be shown.*/
    SDL_Rect* clip;

    public:
    int sprite;/**This variable needs to be public so that it can be set in init().*/
    /**Initialize the variables.*/
    Options_Button(int x,int y,int w,int h,int which_sprite);
    /**Handles events and set the button's sprite region.*/
    void handle_events();
    /**Shows the button on the screen.*/
    void show();
};

class Item_Button{
    private:
    /**The attributes of the button.*/
    SDL_Rect box;
    int item;

    public:
    /**Initialize the variables.*/
    Item_Button(int x,int y,int w,int h,int which_item);
    /**Handles events and set the button's sprite region.*/
    void handle_events();
};

class Bank_Button{
    private:
    /**The attributes of the button.*/
    SDL_Rect box;
    int button;

    public:
    /**Initialize the variables.*/
    Bank_Button(int x,int y,int w,int h,int which_button);
    /**Handles events and set the button's sprite region.*/
    void handle_events();
};

class Arrow_Button{
    private:
    /**The attributes of the button.*/
    SDL_Rect box;
    /**The part of the button sprite sheet that will be shown.*/
    SDL_Rect* clip;
    int sprite;

    public:
    /**Initialize the variables.*/
    Arrow_Button(int x,int y,int w,int h,int which_sprite);
    /**Handles events and set the button's sprite region.*/
    void handle_events();
    /**Shows the button on the screen.*/
    void show();
};

class Dialog_Button{
    private:
    /**The attributes of the button.*/
    SDL_Rect box;
    int button;

    public:
    /**Initialize the variables.*/
    Dialog_Button(int x,int y,int w,int h,int which_button);
    void handle_events();
};

class Found_Button{
    private:
    /**The attributes of the button.*/
    SDL_Rect box;
    int button;

    public:
    /**Initialize the variables.*/
    Found_Button(int x,int y,int w,int h,int which_button);
    void handle_events();
};

class Moral_Button{
    private:
    /**The attributes of the button.*/
    SDL_Rect box;
    int choice;

    public:
    /**Initialize the variables.*/
    Moral_Button(int x,int y,int w,int h,int which_choice);
    /**Handles events and set the button's sprite region.*/
    void handle_events();
    /**Shows the button on the screen.*/
    void show();
};

class Days_Button{
    private:
    /**The attributes of the button.*/
    SDL_Rect box;
    int choice;

    public:
    /**Initialize the variables.*/
    Days_Button(int x,int y,int w,int h,int which_choice);
    /**Handles events and set the button's sprite region.*/
    void handle_events();
};

class City_Button{
    private:
    /**The attributes of the button.*/
    SDL_Rect box;
    int button;

    public:
    /**Initialize the variables.*/
    City_Button(int x,int y,int w,int h,int which_button);
    void handle_events();
};

class Stats_Button{
    private:
    /**The attributes of the button.*/
    SDL_Rect box;
    /**The part of the button sprite sheet that will be shown.*/
    SDL_Rect* clip;
    int sprite;
    int skill;/**Tells the button which stat it is tied to.*/

    public:
    /**Initialize the variables.*/
    Stats_Button(int x,int y,int w,int h,int which_sprite,int which_skill);
    /**Handles events and set the button's sprite region.*/
    void handle_events();
    /**Shows the button on the screen.*/
    void show();
};

#endif
