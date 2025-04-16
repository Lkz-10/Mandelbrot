#ifndef __CALCULATIONS_H__
#define __CALCULATIONS_H__

#include "Globals.h"

int  ArgCheck   (const int argc);
int  SetMode    (const char** argv, struct lab_mode_t* lab_mode);
int  Calculate  (struct lab_mode_t* lab_mode, sf::Image& image, fps_t* fps);

int SimpleCalc (int mode, sf::Image& image, fps_t* fps);

int ArrayCalc(int mode, sf::Image& image, fps_t* fps);
inline void CountArray(coord_t* x0, coord_t* y0, coord_t xi, coord_t yi, int mode, sf::Image& image);
inline void CountPixel(coord_t* x, coord_t* y, coord_t* x0, coord_t* y0, coord_t xi, coord_t yi,
                       int num, int* mask, int cnt, int mode, sf::Image& image);

#endif
