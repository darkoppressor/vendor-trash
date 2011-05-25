/* Copyright (c) 2011 Kevin Wells */
/* Vendor Trash may be freely redistributed.  See license for details. */

#ifndef random_number_generator_h
#define random_number_generator_h

#include "MersenneTwister.h"

#include <stdint.h>

class Random_Number_Generator{
    private:
    public:
    MTRand mrand_main;
};

uint32_t random_range(int lownum,int highnum);

#endif
