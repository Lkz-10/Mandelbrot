#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <iostream>
#include <string.h>
#include <math.h>
#include <ctime>
#include <SFML/Graphics.hpp>

// #define _SSE_USED

struct fps_t
{
    int     nframes;
    clock_t start;
    clock_t finish;
    clock_t total_time;
};

struct lab_mode_t
{
    int mode;
    int version;
};

typedef float coord_t;

const coord_t   X0              = 400,
                Y0              = 300,
                R0_2            = 100;

const int       ARR_SIZE        = 16 / sizeof(coord_t),
                MAX_ITERATIONS  = 256,
                WIDTH           = 600,
                HEIGHT          = 600,
                PXL_PER_UNIT    = 260,
                MIN_TIME        = 5 * CLOCKS_PER_SEC;

// const char*     WINDOW_NAME         = "The Mandelbrot set";
// const char*     GRAPHICS_KEY        = "--graphics";
// const char*     CALCULATIONS_KEY    = "--calculate";
// const char*     SIMPLE_V_KEY        = "--simple";
// const char*     ARRAY_V_KEY         = "--array";
// const char*     SIMD_V_KEY          = "--simd";

enum err_codes
{
    ERROR = -1,
    OK    = 0
};

enum modes
{
    GRAPHICS        = 1,
    CALCULATIONS    = 2
};

enum versions
{
    SIMPLE = 1,
    ARRAY  = 2,
    SIMD   = 3
};

#endif
