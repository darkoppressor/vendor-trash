/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include <fstream>

#include "quit.h"
#include "sdl.h"
#include "variables.h"
#include "options.h"

using namespace std;

void quit_game(){
    clean_up();

    /**Save options to options.cfg.*/
    if(options_save()==false){
        printf("\nFailed to save options.cfg.");
    }

    exit(EXIT_SUCCESS);
}
