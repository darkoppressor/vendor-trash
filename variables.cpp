/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include "variables.h"

using namespace std;

/**Screen dimensions and bpp:*/
int SCREEN_WIDTH=640;
int SCREEN_HEIGHT=480;
int SCREEN_BPP=0;/**We set the screen's bpp to 0 to make it set to the current screen bpp of the computer.*/

/**Options:*/
bool fullscreen=false;

/**Player variables:*/
const int PLAYER_WIDTH=20;
const int PLAYER_HEIGHT=20;
const int PLAYER_LEFT=1;
const int PLAYER_UP=2;
const int PLAYER_RIGHT=3;
const int PLAYER_DOWN=4;
const int PLAYER_LEFTUP=5;
const int PLAYER_RIGHTUP=6;
const int PLAYER_RIGHTDOWN=7;
const int PLAYER_LEFTDOWN=8;
const float PLAYER_SPEED=100.0f;/**The pixels per second the player is able to move.*/

Player character;

Random_Number_Generator rng;

/**Player Stats:*/
long level=0;
long experience=0;
long experience_max=0;
long health=0;
long health_max=0;
long skill_points=0;
long cart_size=0;
long haggling=0;
long banking=0;
long strength=0;
long stamina=0;
long luck=0;
int morality=0;
int battles_won=0;
int battles_lost=0;
int sales=0;
int purchases=0;
/**Player Information, etc.:*/
bool gender=true;/**true=male. false=female. Not currently implemented.*/
string name="";
long gold=0;
long debt=0;
long savings=0;
long inventory=0;
long inventory_max=0;
/**Player Inventory:*/
long inv_weapons=0;
long inv_armor=0;
long inv_accessories=0;
long inv_magicalitems=0;
long inv_revives=0;
long inv_manapotions=0;
long inv_healthpotions=0;
long inv_antidotes=0;
/**Player Equipment:*/
long equip_attack=0;
long equip_defense=0;
string weapon_name="";
string armor_name="";
int equip_found=0;
string equip_found_name="";
long equip_found_attack=0;
long equip_found_defense=0;
/**Coordinates of the player's home city:*/
float home_x=0;
float home_y=0;
/**Trade variables that need to be global:*/
long max_trade=0;/**Max amount of current item that can be traded.*/
long current_item_price=0;/**Price of current item.*/
long current_trade=0;/**How many of current item you want to buy.*/
int bank_mode=0;/**Used to tell bank_transaction() what kind of transaction is being done.*/
string item_name="";/**Set in buy_items() and sell_items() and used to tell draw_dialog_message() what item is being clicked.*/

/**Battle variables:*/
string enemy_name="";
long enemy_health=0;
long enemy_health_max=0;
long enemy_attack=0;
long enemy_experience=0;
long enemy_gold=0;
bool turn=true;/**This tells us whose turn it is during battle. true=player's, false=enemie's.*/

/**Game variables:*/
bool game_in_progress=false;
long days=0;
long days_max=0;
int current_city=0;
string city_name="";
int city[9];
int last_city=0;

/**World variables*/
int world_year=0;
int world_month=0;
int world_day=0;
int world_hour=0;
int world_scenario=0;/**This is what Problem scenario the game will be using.*/
int good_vs_evil=0;
string world_homeland="";/**The homeland of the player. This is where the entire game will take place.*/
/**These variables will not all be used in every game, because it depends on which scenario is being played.*/
string world_evil="";
string world_other_kingdom="";
string world_king="";
string world_artifact="";
string world_hero="";

/**World Map Animations:*/
float anim_waves_counter=0;
int anim_waves_frame=0;
float anim_lighthouse_counter=0;
int anim_lighthouse_frame=0;


/**Random event variables:*/
int re_city_item_zero=0;/**Used in events_city() to determine if the player has just entered a city in which an item is not being traded.*/
int re_city_item_cheap=0;
int re_city_item_expensive=0;
bool re_moral=false;
long re_gold_good=0;
long re_gold_neutral=0;
long re_gold_bad=0;

/**Highscores:*/
long score[10]={1000,5000,10000,50000,100000,500000,1000000,5000000,10000000,50000000};
long score_days[10]={25,25,50,50,75,75,100,100,150,200};
long score_level[10]={5,5,15,15,25,25,40,40,65,80};
string score_name[10]={"Mortimer","Luther","MrBear","Freddi","Professor","Penny","Fox","Sam","Kevin","Keen"};

/**Cities:*/
City city1(510,61,1);
City city2(431,240,2);
City city3(200,350,3);
City city4(33,323,4);
City city5(152,127,5);
City city6(299,114,6);
City city7(200,160,7);
City city8(95,193,8);

/**Clouds:*/
Cloud cloud1;
Cloud cloud2;
Cloud cloud3;

/**Item prices:*/
long price_weapons;
long price_armor;
long price_accessories;
long price_magicalitems;
long price_revives;
long price_manapotions;
long price_healthpotions;
long price_antidotes;

/**Item buttons:*/
Item_Button b_buy_weapons(15,60,40,20,0);
Item_Button b_buy_armor(15,100,40,20,1);
Item_Button b_buy_accessories(15,140,40,20,2);
Item_Button b_buy_magicalitems(15,180,40,20,3);
Item_Button b_buy_revives(15,220,40,20,4);
Item_Button b_buy_manapotions(15,260,40,20,5);
Item_Button b_buy_healthpotions(15,300,40,20,6);
Item_Button b_buy_antidotes(15,340,40,20,7);
Item_Button b_sell_weapons(55,60,40,20,8);
Item_Button b_sell_armor(55,100,40,20,9);
Item_Button b_sell_accessories(55,140,40,20,10);
Item_Button b_sell_magicalitems(55,180,40,20,11);
Item_Button b_sell_revives(55,220,40,20,12);
Item_Button b_sell_manapotions(55,260,40,20,13);
Item_Button b_sell_healthpotions(55,300,40,20,14);
Item_Button b_sell_antidotes(55,340,40,20,15);

/**City buttons:*/
City_Button b_bank(SCREEN_WIDTH-270,205,BUTTON_WIDTH,BUTTON_HEIGHT,0);
City_Button b_travel(SCREEN_WIDTH-270,165,BUTTON_WIDTH,BUTTON_HEIGHT,1);
City_Button b_stats(SCREEN_WIDTH-270,245,BUTTON_WIDTH,BUTTON_HEIGHT,2);
City_Button b_menu(SCREEN_WIDTH-270,285,BUTTON_WIDTH,BUTTON_HEIGHT,3);

/**These two item variables tell the game which item is being bought or sold when calling buy_items() or sell_items().*/
int trading=0;/**This variable tells the game which item is being bought or sold when calling buy_items() or sell_items().*/
bool confirm=false;/**Used in dialogs to tell the dialog that the player has clicked the confirm button.*/

/**Dialog specific stuff:*/
Arrow_Button b_arrowdown((SCREEN_WIDTH-30)/2-60,SCREEN_HEIGHT/2,30,30,2);
Arrow_Button b_arrowup((SCREEN_WIDTH-30)/2+60,SCREEN_HEIGHT/2,30,30,0);
Dialog_Button b_ok(50,SCREEN_HEIGHT-BUTTON_HEIGHT-10,BUTTON_WIDTH,BUTTON_HEIGHT,0);
Dialog_Button b_cancel(SCREEN_WIDTH-BUTTON_WIDTH-83,SCREEN_HEIGHT-BUTTON_HEIGHT-10,BUTTON_WIDTH,BUTTON_HEIGHT,1);
Dialog_Button b_ok_dialog_message((SCREEN_WIDTH-BUTTON_WIDTH)/2,SCREEN_HEIGHT-BUTTON_HEIGHT-10,BUTTON_WIDTH,BUTTON_HEIGHT,0);

/**Moral dialog buttons:*/
Moral_Button b_moral_good(0,SCREEN_HEIGHT-140,600,BUTTON_HEIGHT,0);
Moral_Button b_moral_neutral(0,SCREEN_HEIGHT-95,600,BUTTON_HEIGHT,1);
Moral_Button b_moral_bad(0,SCREEN_HEIGHT-50,600,BUTTON_HEIGHT,2);

/**Bank buttons:*/
Bank_Button b_deposit((SCREEN_WIDTH-BUTTON_WIDTH)/2,75,BUTTON_WIDTH,BUTTON_HEIGHT,0);
Bank_Button b_withdraw((SCREEN_WIDTH-BUTTON_WIDTH)/2,75+BUTTON_HEIGHT,BUTTON_WIDTH,BUTTON_HEIGHT,1);
Bank_Button b_paydebt((SCREEN_WIDTH-BUTTON_WIDTH)/2,75+(BUTTON_HEIGHT*2),BUTTON_WIDTH,BUTTON_HEIGHT,2);
Bank_Button b_back_bank((SCREEN_WIDTH-BUTTON_WIDTH)/2,SCREEN_HEIGHT-BUTTON_HEIGHT-10,BUTTON_WIDTH,BUTTON_HEIGHT,3);

/**Stats buttons:*/
Stats_Button b_cart_size(SCREEN_WIDTH-235,92,30,30,0,0);
Stats_Button b_haggling(SCREEN_WIDTH-235,142,30,30,0,1);
Stats_Button b_banking(SCREEN_WIDTH-235,192,30,30,0,2);
Stats_Button b_strength(SCREEN_WIDTH-235,242,30,30,0,3);
Stats_Button b_stamina(SCREEN_WIDTH-235,292,30,30,0,4);
Stats_Button b_luck(SCREEN_WIDTH-235,342,30,30,0,5);
Stats_Button b_potion(10,230,BUTTON_WIDTH,BUTTON_HEIGHT,0,6);

/**Main menu specific stuff:*/
int current_menu=0;/**0=main menu. 1=options. 2=about.*/
/**These constants define the dimensions of the buttons on the main menu.*/
const int BUTTON_WIDTH=230;
const int BUTTON_HEIGHT=40;
/**Here we make the buttons that will be displayed by draw_main_menu().*/
Menu_Button b_continue((SCREEN_WIDTH-BUTTON_WIDTH)/2,(SCREEN_HEIGHT/2)-(BUTTON_HEIGHT*3)+20,BUTTON_WIDTH,BUTTON_HEIGHT,5);
Menu_Button b_newgame((SCREEN_WIDTH-BUTTON_WIDTH)/2,(SCREEN_HEIGHT/2)-(BUTTON_HEIGHT*2)+20,BUTTON_WIDTH,BUTTON_HEIGHT,0);
Menu_Button b_highscores((SCREEN_WIDTH-BUTTON_WIDTH)/2,(SCREEN_HEIGHT/2)-(BUTTON_HEIGHT)+20,BUTTON_WIDTH,BUTTON_HEIGHT,6);
Menu_Button b_options((SCREEN_WIDTH-BUTTON_WIDTH)/2,(SCREEN_HEIGHT/2)+20,BUTTON_WIDTH,BUTTON_HEIGHT,1);
Menu_Button b_about((SCREEN_WIDTH-BUTTON_WIDTH)/2,(SCREEN_HEIGHT/2)+(BUTTON_HEIGHT)+20,BUTTON_WIDTH,BUTTON_HEIGHT,2);
Menu_Button b_quit((SCREEN_WIDTH-BUTTON_WIDTH)/2,SCREEN_HEIGHT/2+(BUTTON_HEIGHT*2)+20,BUTTON_WIDTH,BUTTON_HEIGHT,3);
Menu_Button b_back((SCREEN_WIDTH-BUTTON_WIDTH)/2,SCREEN_HEIGHT-BUTTON_HEIGHT-10,BUTTON_WIDTH,BUTTON_HEIGHT,4);

/**Selection bars:*/
Selection_Menu b_select_menu(-1,0,BUTTON_WIDTH,BUTTON_HEIGHT);
Selection_Item b_select_item(-1,0,40,20);

/**Options menu buttons:*/
Options_Button b_fullscreen((SCREEN_WIDTH+155)/2,(BUTTON_HEIGHT*2)+30,50,50,0);

/**Battle buttons:*/
Battle_Button b_attack((SCREEN_WIDTH-BUTTON_WIDTH)/2,SCREEN_HEIGHT-110-BUTTON_HEIGHT*2,BUTTON_WIDTH,BUTTON_HEIGHT,0);
Battle_Button b_healthpotion((SCREEN_WIDTH-BUTTON_WIDTH)/2,SCREEN_HEIGHT-110-BUTTON_HEIGHT,BUTTON_WIDTH,BUTTON_HEIGHT,1);
Battle_Button b_flee((SCREEN_WIDTH-BUTTON_WIDTH)/2,SCREEN_HEIGHT-110,BUTTON_WIDTH,BUTTON_HEIGHT,2);

/**Found equipment buttons:*/
Found_Button b_yes(70,SCREEN_HEIGHT-BUTTON_HEIGHT-10,BUTTON_WIDTH,BUTTON_HEIGHT,0);
Found_Button b_no(SCREEN_WIDTH-BUTTON_WIDTH-83,SCREEN_HEIGHT-BUTTON_HEIGHT-10,BUTTON_WIDTH,BUTTON_HEIGHT,1);

/**Days buttons:*/
Days_Button b_days_1(100,SCREEN_HEIGHT-BUTTON_HEIGHT-230,BUTTON_WIDTH*2,BUTTON_HEIGHT,0);
Days_Button b_days_2(100,SCREEN_HEIGHT-BUTTON_HEIGHT-185,BUTTON_WIDTH*2,BUTTON_HEIGHT,1);
Days_Button b_days_3(100,SCREEN_HEIGHT-BUTTON_HEIGHT-140,BUTTON_WIDTH*2,BUTTON_HEIGHT,2);
Days_Button b_days_4(100,SCREEN_HEIGHT-BUTTON_HEIGHT-95,BUTTON_WIDTH*2,BUTTON_HEIGHT,3);
Days_Button b_days_5(100,SCREEN_HEIGHT-BUTTON_HEIGHT-50,BUTTON_WIDTH*2,BUTTON_HEIGHT,4);
Days_Button b_days_6(100,SCREEN_HEIGHT-BUTTON_HEIGHT-5,BUTTON_WIDTH*2,BUTTON_HEIGHT,5);

/**Used to get the player's name, obviously.*/
string_input get_player_name;

//World collision boxes.
vector<Hitbox> hitboxes;
bool option_dev=false;
int frame_count=0;
int frame_rate=0;
float ms_per_frame=0;

/**SDL Specific variables:*/
/**The surfaces that we will be using.*/
SDL_Surface *screen=NULL;/**The screen surface.*/
SDL_Surface *message=NULL;/**This surface is used when rendering text.*/
SDL_Surface *select_menu=NULL;
SDL_Surface *menu_background=NULL;
SDL_Surface *city_background=NULL;
SDL_Surface *dialog=NULL;
SDL_Surface *overworld=NULL;
SDL_Surface *city_icon_small=NULL;
SDL_Surface *city_icon_medium=NULL;
SDL_Surface *city_icon_large=NULL;
SDL_Surface *clouds=NULL;
SDL_Surface *player=NULL;
SDL_Surface *arrows=NULL;
SDL_Surface *options_items=NULL;
SDL_Surface *cursor=NULL;
SDL_Surface *icon=NULL;
SDL_Surface *stats_background=NULL;
SDL_Surface *stats_items=NULL;
SDL_Surface *moral_choice=NULL;
SDL_Surface *about_background=NULL;
SDL_Surface *b_buy=NULL;
SDL_Surface *select_item=NULL;
SDL_Surface *waves=NULL;
SDL_Surface *time_back=NULL;
SDL_Surface *hitbox=NULL;
SDL_Surface *lighthouse=NULL;
/**Used to poll for events.*/
SDL_Event event;
/**Sprite sheets.*/
SDL_Rect clip_arrows[4];
SDL_Rect clip_clouds[4];/**The clip regions of the sprite sheet for clouds.*/
SDL_Rect clip_options_items[2];
SDL_Rect clip_stats_items[2];
SDL_Rect clip_waves[2];
SDL_Rect clip_lighthouse[4];
/**The clip regions of the sprite sheet for the player.*/
SDL_Rect clip_player_right[2];
SDL_Rect clip_player_left[2];
SDL_Rect clip_player_up[2];
SDL_Rect clip_player_down[2];
SDL_Rect clip_player_leftup[2];
SDL_Rect clip_player_rightup[2];
SDL_Rect clip_player_rightdown[2];
SDL_Rect clip_player_leftdown[2];
/**Used to determine font color when rendering text.*/
SDL_Color text_color={255,255,255};
SDL_Color text_color_black={0,0,0};
SDL_Color text_color_white={255,255,255};
SDL_Color text_color_yellow={253,255,84};
SDL_Color text_color_blue={0,169,211};
/**The fonts that we will be using.*/
TTF_Font *font_42 = NULL;
TTF_Font *font_36 = NULL;
TTF_Font *font_30 = NULL;
TTF_Font *font_24 = NULL;
TTF_Font *font_18 = NULL;
/**The music and sound effects:*/
Mix_Music *music_menu = NULL;

stringstream ss("");/**String stream used to easily render ints and stuff as strings.*/
string msg="";/**ss passes its information into this string for output with msg_write.*/
/**These additional strings are used with dialog_message() to display dialog message with more than one line.*/
string msg1="0";
string msg2="0";
string msg3="0";
string msg4="0";
string msg5="0";
string msg6="0";
string msg7="0";
string msg8="0";
/**These strings are used by moral_dialog_message().*/
string msg_good="";
string msg_neutral="";
string msg_bad="";
