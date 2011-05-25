/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include "options.h"
#include "variables.h"

#include <fstream>

using namespace std;

bool options_load(){
    ifstream load("options.cfg");
        if(load!=NULL){
            load >> fullscreen;
            load >> get_player_name.str;
            if(load.fail()==true){
                return false;
            }
            load.close();
        }
        else{
            /**Save options to options.cfg.*/
            if(options_save()==false){
                return false;
            }
        }
    return true;
}

bool options_save(){
    ofstream save("options.cfg");
    save << fullscreen;
    save << "\n";
    save << get_player_name.str;
    if(save.fail()==true){
        return false;
    }
    save.close();
    return true;
}
