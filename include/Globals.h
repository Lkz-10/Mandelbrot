#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <iostream>
#include <string.h>
#include <math.h>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <xmmintrin.h>
#include <immintrin.h>

typedef float coord_t;

struct scale_t
{
    coord_t x0;
    coord_t y0;
    coord_t pxl_size;
};

struct cycles_t
{
    uint64_t start;
    uint64_t finish;
    uint64_t total_cycles;
    int      nframes;
    int      nframes_max;
};

struct lab_mode_t
{
    int mode;
    int version;
};

const coord_t   X0              = 400,
                Y0              = 300,
                PXL_PER_UNIT    = 260,
                R0_2            = 100,
                DELTA_X         = 25,
                DELTA_Y         = 25,
                DELTA_SCALE     = 25;

const int       ARGC_MIN        = 3,
                ARR_SIZE        = 16 / sizeof(coord_t), // HEIGHT % ARR_SIZE must equal 0
                MAX_ITERATIONS  = 256,
                WIDTH           = 600,
                HEIGHT          = 600,

                MIN_TIME        = 5 * CLOCKS_PER_SEC;

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
