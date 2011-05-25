/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#ifndef variables_h
#define variables_h

#include <string>/**We are declaring a string variable.*/
#include <sstream>/**We are declaring a string stream.*/
#include <vector>

#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "buttons.h"
#include "player.h"
#include "clouds.h"
#include "city.h"
#include "string_input.h"
#include "world.h"
#include "random_number_generator.h"

/**Screen dimensions and bpp:*/
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int SCREEN_BPP;

/**Options:*/
extern bool fullscreen;

/**Player variables:*/
extern const int PLAYER_WIDTH;
extern const int PLAYER_HEIGHT;
extern const int PLAYER_RIGHT;
extern const int PLAYER_LEFT;
extern const int PLAYER_UP;
extern const int PLAYER_DOWN;
extern const int PLAYER_LEFTUP;
extern const int PLAYER_RIGHTUP;
extern const int PLAYER_RIGHTDOWN;
extern const int PLAYER_LEFTDOWN;
extern const float PLAYER_SPEED;

extern Player character;

extern Random_Number_Generator rng;

/**Player Stats:*/
extern long level;
extern long experience;
extern long experience_max;
extern long health;
extern long health_max;
extern long skill_points;
extern long cart_size;
extern long haggling;
extern long banking;
extern long strength;
extern long stamina;
extern long luck;
extern int morality;
extern int battles_won;
extern int battles_lost;
extern int sales;
extern int purchases;
/**Player Information, etc.:*/
extern bool gender;/**true=male. false=female. Not currently implemented.*/
extern std::string name;
extern long gold;
extern long debt;
extern long savings;
extern long inventory;
extern long inventory_max;
/**Player Inventory:*/
extern long inv_weapons;
extern long inv_armor;
extern long inv_accessories;
extern long inv_magicalitems;
extern long inv_revives;
extern long inv_manapotions;
extern long inv_healthpotions;
extern long inv_antidotes;
/**Player Equipment:*/
extern long equip_attack;
extern long equip_defense;
extern std::string weapon_name;
extern std::string armor_name;
extern int equip_found;
extern std::string equip_found_name;
extern long equip_found_attack;
extern long equip_found_defense;
/**Coordinates of the player's home city:*/
extern float home_x;
extern float home_y;
/**Trade variables that need to be global:*/
extern long max_trade;/**Max amount of current item that can be traded.*/
extern long current_item_price;/**Price of current item.*/
extern long current_trade;/**How many of current item you want to buy.*/
extern int bank_mode;/**Used to tell bank_transaction() what kind of transaction is being done.*/
extern std::string item_name;/**Set in buy_items() and sell_items() and used to tell draw_dialog_message() what item is being clicked.*/

/**Battle variables:*/
extern std::string enemy_name;
extern long enemy_health;
extern long enemy_health_max;
extern long enemy_attack;
extern long enemy_experience;
extern long enemy_gold;
extern bool turn;/**This tells us whose turn it is during battle. true=player's, false=enemie's.*/

/**Game variables:*/
extern bool game_in_progress;
extern long days;
extern long days_max;
extern int current_city;/**0=overworld. 1-8=city1-8.*/
extern std::string city_name;
extern int city[];
extern int last_city;

/**World variables*/
extern int world_year;
extern int world_month;
extern int world_day;
extern int world_hour;
extern int world_scenario;/**This is what Problem scenario the game will be using.*/
extern int good_vs_evil;
extern std::string world_homeland;/**The homeland of the player. This is where the entire game will take place.*/
/**These variables will not all be used in every game, because it depends on which scenario is being played.*/
extern std::string world_evil;
extern std::string world_other_kingdom;
extern std::string world_king;
extern std::string world_artifact;
extern std::string world_hero;

/**World Map Animations:*/
extern float anim_waves_counter;
extern int anim_waves_frame;
extern float anim_lighthouse_counter;
extern int anim_lighthouse_frame;

/**Random event variables:*/
extern int re_city_item_zero;/**Used in events_city() to determine if the player has just entered a city in which an item is not being traded.*/
extern int re_city_item_cheap;
extern int re_city_item_expensive;
extern bool re_moral;
extern long re_gold_good;
extern long re_gold_neutral;
extern long re_gold_bad;

/**Highscores:*/
extern long score[];
extern long score_days[];
extern long score_level[];
extern std::string score_name[];

/**Cities:*/
extern City city1;
extern City city2;
extern City city3;
extern City city4;
extern City city5;
extern City city6;
extern City city7;
extern City city8;

/**Clouds:*/
extern Cloud cloud1;
extern Cloud cloud2;
extern Cloud cloud3;

/**Item prices:*/
extern long price_weapons;
extern long price_armor;
extern long price_accessories;
extern long price_magicalitems;
extern long price_revives;
extern long price_manapotions;
extern long price_healthpotions;
extern long price_antidotes;

/**Item buttons:*/
extern Item_Button b_buy_weapons;
extern Item_Button b_buy_armor;
extern Item_Button b_buy_accessories;
extern Item_Button b_buy_magicalitems;
extern Item_Button b_buy_revives;
extern Item_Button b_buy_manapotions;
extern Item_Button b_buy_healthpotions;
extern Item_Button b_buy_antidotes;
extern Item_Button b_sell_weapons;
extern Item_Button b_sell_armor;
extern Item_Button b_sell_accessories;
extern Item_Button b_sell_magicalitems;
extern Item_Button b_sell_revives;
extern Item_Button b_sell_manapotions;
extern Item_Button b_sell_healthpotions;
extern Item_Button b_sell_antidotes;

/**City buttons:*/
extern City_Button b_bank;
extern City_Button b_travel;
extern City_Button b_stats;
extern City_Button b_casino;
extern City_Button b_menu;

extern int trading;/**This variable tells the game which item is being bought or sold when calling buy_items() or sell_items().*/
extern bool confirm;/**Used in dialogs to tell the dialog that the player has clicked the confirm button.*/

/**Dialog specific stuff:*/
extern Arrow_Button b_arrowdown;
extern Arrow_Button b_arrowup;
extern Dialog_Button b_ok;
extern Dialog_Button b_cancel;
extern Dialog_Button b_ok_dialog_message;

/**Moral dialog buttons:*/
extern Moral_Button b_moral_good;
extern Moral_Button b_moral_neutral;
extern Moral_Button b_moral_bad;

/**Bank buttons:*/
extern Bank_Button b_deposit;
extern Bank_Button b_withdraw;
extern Bank_Button b_paydebt;
extern Bank_Button b_back_bank;

/**Stats buttons:*/
extern Stats_Button b_cart_size;
extern Stats_Button b_haggling;
extern Stats_Button b_banking;
extern Stats_Button b_strength;
extern Stats_Button b_stamina;
extern Stats_Button b_luck;
extern Stats_Button b_potion;

/**Main menu specific stuff:*/
extern int current_menu;
/**These constants define the dimensions of the buttons on the main menu.*/
extern const int BUTTON_WIDTH;
extern const int BUTTON_HEIGHT;
/**Here we make the buttons that will be displayed by draw_main_menu().*/
extern Menu_Button b_continue;
extern Menu_Button b_newgame;
extern Menu_Button b_highscores;
extern Menu_Button b_options;
extern Menu_Button b_about;
extern Menu_Button b_quit;
extern Menu_Button b_back;

/**Selection bars:*/
extern Selection_Menu b_select_menu;
extern Selection_Item b_select_item;

/**Options menu buttons:*/
extern Options_Button b_fullscreen;

/**Battle buttons:*/
extern Battle_Button b_attack;
extern Battle_Button b_healthpotion;
extern Battle_Button b_flee;

/**Found equipment buttons:*/
extern Found_Button b_yes;
extern Found_Button b_no;

/**Days buttons:*/
extern Days_Button b_days_1;
extern Days_Button b_days_2;
extern Days_Button b_days_3;
extern Days_Button b_days_4;
extern Days_Button b_days_5;
extern Days_Button b_days_6;

/**Used to get the player's name, obviously.*/
extern string_input get_player_name;

//World collision boxes.
extern std::vector<Hitbox> hitboxes;
extern bool option_dev;
extern int frame_count;
extern int frame_rate;
extern float ms_per_frame;

/**SDL Specific variables:*/
/**The surfaces that we will be using.*/
extern SDL_Surface *screen;
extern SDL_Surface *message;
extern SDL_Surface *select_menu;
extern SDL_Surface *menu_background;
extern SDL_Surface *city_background;
extern SDL_Surface *dialog;
extern SDL_Surface *overworld;
extern SDL_Surface *city_icon_small;
extern SDL_Surface *city_icon_medium;
extern SDL_Surface *city_icon_large;
extern SDL_Surface *clouds;
extern SDL_Surface *player;
extern SDL_Surface *arrows;
extern SDL_Surface *options_items;
extern SDL_Surface *cursor;
extern SDL_Surface *icon;
extern SDL_Surface *stats_background;
extern SDL_Surface *stats_items;
extern SDL_Surface *moral_choice;
extern SDL_Surface *about_background;
extern SDL_Surface *b_buy;
extern SDL_Surface *select_item;
extern SDL_Surface *waves;
extern SDL_Surface *time_back;
extern SDL_Surface *hitbox;
extern SDL_Surface *lighthouse;
/**Used to poll for events.*/
extern SDL_Event event;
/**Sprite sheets.*/
extern SDL_Rect clip_arrows[];
extern SDL_Rect clip_clouds[];
extern SDL_Rect clip_options_items[];
extern SDL_Rect clip_stats_items[];
extern SDL_Rect clip_waves[];
extern SDL_Rect clip_lighthouse[];
/**The clip regions of the sprite sheet for the player.*/
extern SDL_Rect clip_player_right[];
extern SDL_Rect clip_player_left[];
extern SDL_Rect clip_player_up[];
extern SDL_Rect clip_player_down[];
extern SDL_Rect clip_player_leftup[];
extern SDL_Rect clip_player_rightup[];
extern SDL_Rect clip_player_rightdown[];
extern SDL_Rect clip_player_leftdown[];
/**Used to determine font color when rendering text.*/
extern SDL_Color text_color;
extern SDL_Color text_color_black;
extern SDL_Color text_color_white;
extern SDL_Color text_color_yellow;
extern SDL_Color text_color_blue;
/**The fonts that we will be using.*/
extern TTF_Font *font_42;
extern TTF_Font *font_36;
extern TTF_Font *font_30;
extern TTF_Font *font_24;
extern TTF_Font *font_18;
/**The music and sound effects:*/
extern Mix_Music *music_menu;

extern std::stringstream ss;
extern std::string msg;
extern std::string msg1;
extern std::string msg2;
extern std::string msg3;
extern std::string msg4;
extern std::string msg5;
extern std::string msg6;
extern std::string msg7;
extern std::string msg8;
/**These strings are used by moral_dialog_message().*/
extern std::string msg_good;
extern std::string msg_neutral;
extern std::string msg_bad;

#endif
