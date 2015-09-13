/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#include "time_of_day.h"
#include "variables.h"
#include "sdl.h"

using namespace std;

void display_time(){
    /**Display the date:*/
    string temp_msg="";
    switch(world_month){
        case 1:
        msg="Yanvar";
        break;
        case 2:
        msg="Fevral";
        break;
        case 3:
        msg="Mart";
        break;
        case 4:
        msg="Aprel";
        break;
        case 5:
        msg="Mai";
        break;
        case 6:
        msg="Aeyune";
        break;
        case 7:
        msg="Aeyule";
        break;
        case 8:
        msg="Avguust";
        break;
        case 9:
        msg="Sentyabre";
        break;
        case 10:
        msg="Oktyabre";
        break;
        case 11:
        msg="Noyabre";
        break;
        case 12:
        msg="Dekabre";
        break;
    }
    msg+=" ";
    ss.clear();ss.str("");ss<<world_day;ss>>temp_msg;
    msg+=temp_msg;
    if(world_day==1 || world_day==21){
        msg+="st, ";
    }
    else if(world_day==2 || world_day==22){
        msg+="nd, ";
    }
    else if(world_day==3 || world_day==23){
        msg+="rd, ";
    }
    else{
        msg+="th, ";
    }
    ss.clear();ss.str("");ss<<world_year;ss>>temp_msg;
    msg+=temp_msg;
    msg+=", ";
    if(world_month>=1 && world_month<=4){
        msg+="Veris";
    }
    if(world_month>=5 && world_month<=8){
        msg+="Aestas";
    }
    if(world_month>=9 && world_month<=12){
        msg+="Ambru";
    }
    msg_write(0,SCREEN_HEIGHT-50,36,msg,1);
}
