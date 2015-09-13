/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include "scores.h"
#include "variables.h"
#include "input.h"
#include "screen_draw.h"

#include <fstream>

using namespace std;

void scores_load(){
    ifstream load("highscores");
        if(load!=NULL){
            for(int x=0;x<10;x++){
                load >> score_name[x];
                load >> score[x];
                load >> score_days[x];
                load >> score_level[x];
            }
            load.close();
        }
        else{
            /**Save scores to scores.cfg.*/
            scores_save();
        }
}

void scores_save(){
    ofstream save("highscores");
    for(int x=0;x<10;x++){
        save << score_name[x];
        save << "\n";
        save << score[x];
        save << "\n";
        save << score_days[x];
        save << "\n";
        save << score_level[x];
        save << "\n";
    }
    save.close();
}

void scores_display(){
    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,100);

    bool loop=true;
    /**Reset the selection bar.*/
    b_select_menu.box.x=-1;

    current_menu=4;

    scores_load();

    while(loop==true){
        input_scores_display();
        if(confirm==true){
            confirm=false;
            return;
        }
        draw_main_menu();
        draw_scores_display();
    }
}
