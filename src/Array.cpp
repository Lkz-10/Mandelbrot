#include "../include/Calculations.h"

int ArrayCalc(const int mode, sf::Image& image, fps_t* fps)
{
    if (!fps)
    {
        fprintf(stderr, "ArrayCalc() error: &fps = %p\n", fps);
        return ERROR;
    }

    fps->start = clock();

    for (coord_t xi = 0; xi < WIDTH; ++xi)
    {
        coord_t xi0[ARR_SIZE] = {};
        for (int i = 0; i < ARR_SIZE; ++i)
        {
            xi0[i] = (xi - X0) / PXL_PER_UNIT;
        }

        for (coord_t yi = 0; yi < HEIGHT; yi += ARR_SIZE)
        {
            coord_t yi0[ARR_SIZE] = {};
            for (int i = 0; i < ARR_SIZE; ++i)
            {
                yi0[i] = (yi + i - Y0) / PXL_PER_UNIT;
            }

            CountArray(xi0, yi0, xi, yi, mode, image);
        }
    }

    fps->finish = clock();

    fps->total_time += fps->finish - fps->start;
    (fps->nframes)++;

    if (mode == CALCULATIONS && fps->total_time < MIN_TIME) ArrayCalc(mode, image, fps);

    return OK;
}

inline void CountArray(const coord_t* x0, const coord_t* y0, const coord_t xi, const coord_t yi,
                       const int mode, sf::Image& image)
{
    int cnt = 0, mask = 0;

    volatile coord_t x[ARR_SIZE] = {},
                     y[ARR_SIZE] = {};

    for (int i = 0; i < ARR_SIZE; ++i)
    {
        x[i] = x0[i];
        y[i] = y0[i];
    }

    for ( ; cnt < MAX_ITERATIONS && mask != (1 << ARR_SIZE) - 1; ++cnt)
    {
        for (int i = 0; i < ARR_SIZE; ++i)
        {
            CountPixel(x, y, x0, y0, xi, yi + i, i, &mask, cnt, mode, image);
        }
    }
}

inline void CountPixel(volatile coord_t* x, volatile coord_t* y, const coord_t* x0,
                       const coord_t* y0, const coord_t xi, const coord_t yi, const int num,
                       int* mask, const int cnt, const int mode, sf::Image& image)

{
    if (!(*mask & (1 << num)))
    {
        coord_t old_x = x[num];

        x[num] = x[num] * x[num] - y[num] * y[num] + x0[num];
        y[num] = 2 * old_x * y[num] + y0[num];

        if (x[num] * x[num] + y[num] * y[num] > R0_2)
        {
            *mask |= (1 << num);
            if (mode == GRAPHICS)
            {
                image.setPixel(xi, yi, sf::Color((cnt*10) % 256, 0, (255-cnt) / 3));
            }
        }
    }
}
