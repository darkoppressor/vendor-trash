/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include <SDL_mixer.h>

#include "sdl.h"
#include "variables.h"

using namespace std;

/**This little function loads an image, and then returns the optimized version of that image. We are going to use it instead of IMG_Load to load images in the program.*/
SDL_Surface *load_image(string filename){
    SDL_Surface* loaded_image=NULL;/**Temporary storage for the image being loaded.*/
    SDL_Surface* optimized_image=NULL;/**The optimized image that will be used.*/
    loaded_image=IMG_Load(filename.c_str());/**Load the image.*/
    if(loaded_image != NULL){/**Make sure nothing went wrong loading the image.*/
        optimized_image=SDL_DisplayFormatAlpha(loaded_image);/**Create the optimized image.*/
        SDL_FreeSurface(loaded_image);/**Free the old surface.*/
//This commented out section can be used for color keying, if that becomes needed.
//        if(optimized_image != NULL){/**If the image was optimized successfully.*/
//            SDL_SetColorKey(optimized_image,SDL_SRCCOLORKEY,SDL_MapRGB(optimized_image->format,0,0xFF,0xFF));/**Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent.*/
//        }
    }
    return optimized_image;/**Return the optimized image.*/
}

/**x offset, y offset, source surface, destination surface, clipping SDL_Rect, change offsets to center source surface somewhere?*/
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* surface_clip = NULL,int centered=0){
    SDL_Rect offset;/**Mske a temporary rectangle to hold the offsets.*/
    if(centered==1){/**Set centered==1 for top centered text.*/
        x=(SCREEN_WIDTH-source->w)/2;
    }
    /**Give the offsets to the rectangle.*/
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source,surface_clip,destination,&offset);/**Blit the surface.*/
}

void msg_write(int a,int b,int font_size,string msg,int centered=0){
    if(font_size==42){
        message=TTF_RenderText_Solid(font_42,msg.c_str(),text_color);
    }
    if(font_size==36){
        message=TTF_RenderText_Solid(font_36,msg.c_str(),text_color);
    }
    if(font_size==30){
        message=TTF_RenderText_Solid(font_30,msg.c_str(),text_color);
    }
    if(font_size==24){
        message=TTF_RenderText_Solid(font_24,msg.c_str(),text_color);
    }
    if(font_size==18){
        message=TTF_RenderText_Solid(font_18,msg.c_str(),text_color);
    }
    if(centered!=0){
        apply_surface(a,b,message,screen,NULL,centered);
    }
    else{
        apply_surface(a,b,message,screen,NULL,0);
    }
    SDL_FreeSurface(message);
}

/**Here we initialize all of the SDL stuff.*/
bool init(){
    if(SDL_Init(SDL_INIT_EVERYTHING)==-1){/**Initialize all of the standard SDL stuff, and return false if it did not initialize properly.*/
        printf("Unable to init SDL: %s\n",SDL_GetError());
        return false;
    }
    if(TTF_Init()==-1){/**Initialize the SDL_ttf stuff, and return false if it did not initialize properly.*/
        printf("Unable to init SDL_ttf: %s\n",TTF_GetError());
        return false;
    }

    /**Load and */
    icon=SDL_LoadBMP("data/images/icon.bmp");
    SDL_WM_SetIcon(icon,NULL);

    /**Set up the screen.*/
    if(fullscreen==false){
        screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);
        b_fullscreen.sprite=0;
    }
    if(fullscreen==true){
        screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE|SDL_FULLSCREEN);
        b_fullscreen.sprite=1;
    }
    if(!screen){/**Return false if the screen could not be set up.*/
        printf("Unable to set video mode: %s\n",SDL_GetError());
        return false;
    }
    if(Mix_OpenAudio(22050,AUDIO_S16,2,4096)==-1){/**Start up the audio system.*/
        /**Turn off audio option.*/
    }
    SDL_WM_SetCaption("Vendor Trash",NULL);/**Set the window caption.*/
    SDL_ShowCursor(0);/**Hide the mouse cursor, so that the custom one can be displayed.*/
    return true;
}

bool load_files(){
    font_42=TTF_OpenFont("data/fonts/orangekid.ttf",42);
    if(!font_42){
        printf("Unable to load font: %s\n",TTF_GetError());
        return false;
    }
    font_36=TTF_OpenFont("data/fonts/orangekid.ttf",36);
    if(!font_36){
        printf("Unable to load font: %s\n",TTF_GetError());
        return false;
    }
    font_30=TTF_OpenFont("data/fonts/orangekid.ttf",30);
    if(!font_30){
        printf("Unable to load font: %s\n",TTF_GetError());
        return false;
    }
    font_24=TTF_OpenFont("data/fonts/orangekid.ttf",24);
    if(!font_24){
        printf("Unable to load font: %s\n",TTF_GetError());
        return false;
    }
    font_18=TTF_OpenFont("data/fonts/orangekid.ttf",18);
    if(!font_18){
        printf("Unable to load font: %s\n",TTF_GetError());
        return false;
    }
    /**Load the images.*/
    select_menu=load_image("data/images/select_menu.png");
    menu_background=load_image("data/images/menu_background.png");
    city_background=load_image("data/images/city_background.png");
    dialog=load_image("data/images/dialog.png");
    overworld=load_image("data/images/overworld.png");
    city_icon_small=load_image("data/images/city_icon_small.png");
    city_icon_medium=load_image("data/images/city_icon_medium.png");
    city_icon_large=load_image("data/images/city_icon_large.png");
    clouds=load_image("data/images/clouds.png");
    player=load_image("data/images/player.png");
    arrows=load_image("data/images/arrows.png");
    options_items=load_image("data/images/options_items.png");
    cursor=load_image("data/images/cursor.png");
    stats_background=load_image("data/images/stats_background.png");
    stats_items=load_image("data/images/stats_items.png");
    moral_choice=load_image("data/images/moral_choice.png");
    about_background=load_image("data/images/about_background.png");
    b_buy=load_image("data/images/b_buy.png");
    select_item=load_image("data/images/select_item.png");
    waves=load_image("data/images/waves.png");
    time_back=load_image("data/images/time_back.png");
    hitbox=load_image("data/images/hitbox.png");
    lighthouse=load_image("data/images/lighthouse.png");

    /**Load the music and sound effects:*/
    music_menu=Mix_LoadMUS("data/music/menu.ogg");

    //World collision boxes.
    hitboxes.clear();
    hitboxes.push_back(Hitbox(145,86));
    hitboxes.push_back(Hitbox(175,86));
    hitboxes.push_back(Hitbox(205,86));
    hitboxes.push_back(Hitbox(235,86));
    hitboxes.push_back(Hitbox(245,86));
    hitboxes.push_back(Hitbox(125,91));
    hitboxes.push_back(Hitbox(115,95));
    hitboxes.push_back(Hitbox(105,99));
    hitboxes.push_back(Hitbox(95,103));
    hitboxes.push_back(Hitbox(85,107));
    hitboxes.push_back(Hitbox(75,111));
    hitboxes.push_back(Hitbox(65,115));
    hitboxes.push_back(Hitbox(45,107));
    hitboxes.push_back(Hitbox(15,107));
    hitboxes.push_back(Hitbox(0,137));
    hitboxes.push_back(Hitbox(0,167));
    hitboxes.push_back(Hitbox(0,197));
    hitboxes.push_back(Hitbox(0,227));
    hitboxes.push_back(Hitbox(15,247));
    hitboxes.push_back(Hitbox(15,277));
    hitboxes.push_back(Hitbox(0,307));
    hitboxes.push_back(Hitbox(0,337));
    hitboxes.push_back(Hitbox(15,367));
    hitboxes.push_back(Hitbox(93,366));
    hitboxes.push_back(Hitbox(35,366));
    hitboxes.push_back(Hitbox(63,366));
    hitboxes.push_back(Hitbox(123,366));
    hitboxes.push_back(Hitbox(159,366));
    hitboxes.push_back(Hitbox(183,390));
    hitboxes.push_back(Hitbox(213,390));
    hitboxes.push_back(Hitbox(243,366));
    hitboxes.push_back(Hitbox(248,360));
    hitboxes.push_back(Hitbox(278,360));
    hitboxes.push_back(Hitbox(308,360));
    hitboxes.push_back(Hitbox(328,365));
    hitboxes.push_back(Hitbox(338,370));
    hitboxes.push_back(Hitbox(368,340));
    hitboxes.push_back(Hitbox(358,310));
    hitboxes.push_back(Hitbox(368,280));
    hitboxes.push_back(Hitbox(362,285));
    hitboxes.push_back(Hitbox(378,290));
    hitboxes.push_back(Hitbox(368,250));
    hitboxes.push_back(Hitbox(368,240));
    hitboxes.push_back(Hitbox(408,290));
    hitboxes.push_back(Hitbox(428,285));
    hitboxes.push_back(Hitbox(438,280));
    hitboxes.push_back(Hitbox(448,275));
    hitboxes.push_back(Hitbox(468,245));
    hitboxes.push_back(Hitbox(472,215));
    hitboxes.push_back(Hitbox(485,195));
    hitboxes.push_back(Hitbox(490,190));
    hitboxes.push_back(Hitbox(495,185));
    hitboxes.push_back(Hitbox(522,155));
    hitboxes.push_back(Hitbox(532,125));
    hitboxes.push_back(Hitbox(542,105));
    hitboxes.push_back(Hitbox(552,85));
    hitboxes.push_back(Hitbox(552,55));
    hitboxes.push_back(Hitbox(552,25));
    hitboxes.push_back(Hitbox(522,10));
    hitboxes.push_back(Hitbox(492,0));
    hitboxes.push_back(Hitbox(462,0));
    hitboxes.push_back(Hitbox(432,0));
    hitboxes.push_back(Hitbox(432,30));
    hitboxes.push_back(Hitbox(442,60));
    hitboxes.push_back(Hitbox(465,70));
    hitboxes.push_back(Hitbox(462,105));
    hitboxes.push_back(Hitbox(457,125));
    hitboxes.push_back(Hitbox(450,130));
    hitboxes.push_back(Hitbox(420,135));
    hitboxes.push_back(Hitbox(420,150));
    hitboxes.push_back(Hitbox(400,155));
    hitboxes.push_back(Hitbox(390,160));
    hitboxes.push_back(Hitbox(380,165));
    hitboxes.push_back(Hitbox(370,170));
    hitboxes.push_back(Hitbox(360,175));
    hitboxes.push_back(Hitbox(330,175));
    hitboxes.push_back(Hitbox(315,205));
    hitboxes.push_back(Hitbox(315,235));
    hitboxes.push_back(Hitbox(310,240));
    hitboxes.push_back(Hitbox(295,255));
    hitboxes.push_back(Hitbox(290,285));
    hitboxes.push_back(Hitbox(260,293));
    hitboxes.push_back(Hitbox(230,293));
    hitboxes.push_back(Hitbox(200,293));
    hitboxes.push_back(Hitbox(170,293));
    hitboxes.push_back(Hitbox(140,293));
    hitboxes.push_back(Hitbox(110,297));
    hitboxes.push_back(Hitbox(100,297));
    hitboxes.push_back(Hitbox(80,268));
    hitboxes.push_back(Hitbox(70,268));
    hitboxes.push_back(Hitbox(70,238));
    hitboxes.push_back(Hitbox(85,230));
    hitboxes.push_back(Hitbox(95,230));
    hitboxes.push_back(Hitbox(125,225));
    hitboxes.push_back(Hitbox(155,215));
    hitboxes.push_back(Hitbox(185,205));
    hitboxes.push_back(Hitbox(170,205));
    hitboxes.push_back(Hitbox(215,205));
    hitboxes.push_back(Hitbox(220,200));
    hitboxes.push_back(Hitbox(225,195));
    hitboxes.push_back(Hitbox(230,190));
    hitboxes.push_back(Hitbox(240,175));
    hitboxes.push_back(Hitbox(270,175));
    hitboxes.push_back(Hitbox(300,175));
    hitboxes.push_back(Hitbox(330,150));
    hitboxes.push_back(Hitbox(310,170));
    hitboxes.push_back(Hitbox(335,120));
    hitboxes.push_back(Hitbox(335,90));
    hitboxes.push_back(Hitbox(305,65));
    hitboxes.push_back(Hitbox(275,65));

    return true;
}

void clean_up(){
    while(!Mix_FadeOutMusic(1000) && Mix_PlayingMusic()){
        SDL_Delay(100);
    }
    Mix_HaltMusic();

    Mix_FreeMusic(music_menu);

    SDL_FreeSurface(select_menu);
    SDL_FreeSurface(menu_background);
    SDL_FreeSurface(city_background);
    SDL_FreeSurface(dialog);
    SDL_FreeSurface(overworld);
    SDL_FreeSurface(city_icon_small);
    SDL_FreeSurface(city_icon_medium);
    SDL_FreeSurface(city_icon_large);
    SDL_FreeSurface(clouds);
    SDL_FreeSurface(player);
    SDL_FreeSurface(arrows);
    SDL_FreeSurface(options_items);
    SDL_FreeSurface(cursor);
    SDL_FreeSurface(icon);
    SDL_FreeSurface(stats_background);
    SDL_FreeSurface(stats_items);
    SDL_FreeSurface(moral_choice);
    SDL_FreeSurface(about_background);
    SDL_FreeSurface(b_buy);
    SDL_FreeSurface(select_item);
    SDL_FreeSurface(waves);
    SDL_FreeSurface(time_back);
    SDL_FreeSurface(hitbox);
    SDL_FreeSurface(lighthouse);

    TTF_CloseFont(font_42);
    font_42=NULL;
    TTF_CloseFont(font_36);
    font_36=NULL;
    TTF_CloseFont(font_30);
    font_30=NULL;
    TTF_CloseFont(font_24);
    font_24=NULL;
    TTF_CloseFont(font_18);
    font_18=NULL;
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    printf("Exited cleanly!\n");
}
