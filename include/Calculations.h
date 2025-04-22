#ifndef __CALCULATIONS_H__
#define __CALCULATIONS_H__

#include "Globals.h"

//==================================== main.cpp ==========================================
int         ArgCheck        (const int argc);
int         ScaleCtor       (scale_t* scale);
int         SetMode         (const char** argv, struct lab_mode_t* lab_mode);
int         HandleGraphics  (scale_t* scale, fps_t* fps, const lab_mode_t lab_mode,
                             sf::Image& image);
int         MoveImage       (int key, scale_t* scale);
int         Calculate       (const lab_mode_t* lab_mode, const scale_t scale,
                             sf::Image& image, fps_t* fps);

//=================================== Simple.cpp =========================================
int         SimpleCalc  (const int mode, const scale_t scale, sf::Image& image, fps_t* fps);

//=================================== Array.cpp ==========================================
int         ArrayCalc   (const int mode, const scale_t scale, sf::Image& image, fps_t* fps);

inline void CountArray  (const coord_t* x0, const coord_t* y0, const coord_t xi, const coord_t yi,
                         const int mode, sf::Image& image);

inline void CountPixel  (volatile coord_t* x, volatile coord_t* y, const coord_t* x0,
                         const coord_t* y0, const coord_t xi, const coord_t yi, const int num,
                         int* mask, const int cnt, const int mode, sf::Image& image);

//==================================== SIMD.cpp ==========================================
// coord_t must be float!!!
int         SIMDCalc    (const int mode, const scale_t scale, sf::Image& image, fps_t* fps);

#endif
