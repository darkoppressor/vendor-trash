/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include "sprites.h"
#include "variables.h"

using namespace std;

void sprite_sheet_clouds(){
    clip_clouds[0].x=0;
    clip_clouds[0].y=0;
    clip_clouds[0].w=40;
    clip_clouds[0].h=25;

    clip_clouds[1].x=40;
    clip_clouds[1].y=0;
    clip_clouds[1].w=40;
    clip_clouds[1].h=25;

    clip_clouds[2].x=0;
    clip_clouds[2].y=25;
    clip_clouds[2].w=40;
    clip_clouds[2].h=25;

    clip_clouds[3].x=40;
    clip_clouds[3].y=25;
    clip_clouds[3].w=40;
    clip_clouds[3].h=25;
}

void sprite_sheet_player(){
    /**Right.*/
    clip_player_right[0].x=0;
    clip_player_right[0].y=0;
    clip_player_right[0].w=PLAYER_WIDTH;
    clip_player_right[0].h=PLAYER_HEIGHT;

    clip_player_right[1].x=PLAYER_WIDTH;
    clip_player_right[1].y=0;
    clip_player_right[1].w=PLAYER_WIDTH;
    clip_player_right[1].h=PLAYER_HEIGHT;

    /**Left.*/
    clip_player_left[0].x=0;
    clip_player_left[0].y=PLAYER_HEIGHT;
    clip_player_left[0].w=PLAYER_WIDTH;
    clip_player_left[0].h=PLAYER_HEIGHT;

    clip_player_left[1].x=PLAYER_WIDTH;
    clip_player_left[1].y=PLAYER_HEIGHT;
    clip_player_left[1].w=PLAYER_WIDTH;
    clip_player_left[1].h=PLAYER_HEIGHT;

    /**Down.*/
    clip_player_down[0].x=0;
    clip_player_down[0].y=PLAYER_HEIGHT * 2;
    clip_player_down[0].w=PLAYER_WIDTH;
    clip_player_down[0].h=PLAYER_HEIGHT;

    clip_player_down[1].x=PLAYER_WIDTH;
    clip_player_down[1].y=PLAYER_HEIGHT * 2;
    clip_player_down[1].w=PLAYER_WIDTH;
    clip_player_down[1].h=PLAYER_HEIGHT;

    /**Up.*/
    clip_player_up[0].x=0;
    clip_player_up[0].y=PLAYER_HEIGHT * 3;
    clip_player_up[0].w=PLAYER_WIDTH;
    clip_player_up[0].h=PLAYER_HEIGHT;

    clip_player_up[1].x=PLAYER_WIDTH;
    clip_player_up[1].y=PLAYER_HEIGHT * 3;
    clip_player_up[1].w=PLAYER_WIDTH;
    clip_player_up[1].h=PLAYER_HEIGHT;

    /**Left Up.*/
    clip_player_leftup[0].x=0;
    clip_player_leftup[0].y=PLAYER_HEIGHT * 4;
    clip_player_leftup[0].w=PLAYER_WIDTH;
    clip_player_leftup[0].h=PLAYER_HEIGHT;

    clip_player_leftup[1].x=PLAYER_WIDTH;
    clip_player_leftup[1].y=PLAYER_HEIGHT * 4;
    clip_player_leftup[1].w=PLAYER_WIDTH;
    clip_player_leftup[1].h=PLAYER_HEIGHT;

    /**Right Up.*/
    clip_player_rightup[0].x=0;
    clip_player_rightup[0].y=PLAYER_HEIGHT * 5;
    clip_player_rightup[0].w=PLAYER_WIDTH;
    clip_player_rightup[0].h=PLAYER_HEIGHT;

    clip_player_rightup[1].x=PLAYER_WIDTH;
    clip_player_rightup[1].y=PLAYER_HEIGHT * 5;
    clip_player_rightup[1].w=PLAYER_WIDTH;
    clip_player_rightup[1].h=PLAYER_HEIGHT;

    /**Right Down.*/
    clip_player_rightdown[0].x=0;
    clip_player_rightdown[0].y=PLAYER_HEIGHT * 6;
    clip_player_rightdown[0].w=PLAYER_WIDTH;
    clip_player_rightdown[0].h=PLAYER_HEIGHT;

    clip_player_rightdown[1].x=PLAYER_WIDTH;
    clip_player_rightdown[1].y=PLAYER_HEIGHT * 6;
    clip_player_rightdown[1].w=PLAYER_WIDTH;
    clip_player_rightdown[1].h=PLAYER_HEIGHT;

    /**Left Down.*/
    clip_player_leftdown[0].x=0;
    clip_player_leftdown[0].y=PLAYER_HEIGHT * 7;
    clip_player_leftdown[0].w=PLAYER_WIDTH;
    clip_player_leftdown[0].h=PLAYER_HEIGHT;

    clip_player_leftdown[1].x=PLAYER_WIDTH;
    clip_player_leftdown[1].y=PLAYER_HEIGHT * 7;
    clip_player_leftdown[1].w=PLAYER_WIDTH;
    clip_player_leftdown[1].h=PLAYER_HEIGHT;
}

void sprite_sheet_arrows(){
    clip_arrows[0].x=0;
    clip_arrows[0].y=0;
    clip_arrows[0].w=30;
    clip_arrows[0].h=30;

    clip_arrows[1].x=0;
    clip_arrows[1].y=30;
    clip_arrows[1].w=30;
    clip_arrows[1].h=30;

    clip_arrows[2].x=0;
    clip_arrows[2].y=60;
    clip_arrows[2].w=30;
    clip_arrows[2].h=30;

    clip_arrows[3].x=0;
    clip_arrows[3].y=90;
    clip_arrows[3].w=30;
    clip_arrows[3].h=30;
}

void sprite_sheet_options(){
    clip_options_items[0].x=0;
    clip_options_items[0].y=0;
    clip_options_items[0].w=50;
    clip_options_items[0].h=50;

    clip_options_items[1].x=0;
    clip_options_items[1].y=50;
    clip_options_items[1].w=50;
    clip_options_items[1].h=50;
}

void sprite_sheet_stats(){
    clip_stats_items[0].x=0;
    clip_stats_items[0].y=0;
    clip_stats_items[0].w=30;
    clip_stats_items[0].h=30;

    clip_stats_items[1].x=0;
    clip_stats_items[1].y=30;
    clip_stats_items[1].w=30;
    clip_stats_items[1].h=30;
}

void sprite_sheet_waves(){
    clip_waves[0].x=0;
    clip_waves[0].y=0;
    clip_waves[0].w=640;
    clip_waves[0].h=480;

    clip_waves[1].x=0;
    clip_waves[1].y=480;
    clip_waves[1].w=640;
    clip_waves[1].h=480;
}

void sprite_sheet_lighthouse(){
    clip_lighthouse[0].x=0;
    clip_lighthouse[0].y=0;
    clip_lighthouse[0].w=640;
    clip_lighthouse[0].h=480;

    clip_lighthouse[1].x=0;
    clip_lighthouse[1].y=480;
    clip_lighthouse[1].w=640;
    clip_lighthouse[1].h=480;

    clip_lighthouse[2].x=0;
    clip_lighthouse[2].y=960;
    clip_lighthouse[2].w=640;
    clip_lighthouse[2].h=480;

    clip_lighthouse[3].x=0;
    clip_lighthouse[3].y=1440;
    clip_lighthouse[3].w=640;
    clip_lighthouse[3].h=480;
}
