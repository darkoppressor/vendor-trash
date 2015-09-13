/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#ifndef screen_draw_h
#define screen_draw_h

#include <string>

/**For some draw functions (currently draw_city(), draw(), and draw_main_menu()), there is no call to SDL_Flip() at the end. This is because that particular screen may sometimes have dialog boxes
displayed over it, and the call to SDL_Flip() is located at the end of them instead. This means that you must be sure to add a call to SDL_Flip() after any other
call to the function. In other words, when calling the function without it being followed by a draw_dialog function, be sure to add the call to SDL_Flip() after it yourself.*/

void draw();

void draw_battle();

void draw_city();

void draw_main_menu();

void draw_options();

void draw_about();

void draw_stats();

void draw_dialog_bank();

void draw_dialog_bank_transaction();

void draw_dialog_buy_items();

void draw_dialog_sell_items();

void draw_moral_dialog();

void draw_get_max_days();

void draw_dialog_message();

void draw_found_dialog_message();

void draw_new_game_dialog_message();

void draw_scores_display();

void draw_get_name();

#endif
