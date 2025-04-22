#include "../include/Calculations.h"

int SimpleCalc(const int mode, const scale_t scale, sf::Image& image, fps_t* fps)
{
    if (!fps)
    {
        fprintf(stderr, "SimpleCalc() error: &fps = %p\n", fps);
        return ERROR;
    }

    fps->start = clock();

    for (coord_t yi = 0; yi < HEIGHT; ++yi)
    {
        for (coord_t xi = 0; xi < WIDTH; ++xi)
        {
            coord_t xi0 = (xi - scale.x0) / scale.pxl_size,
                    yi0 = (yi - scale.y0) / scale.pxl_size,
                    x   = xi0,
                    y   = yi0;

            int i = 0;
            for ( ; i < MAX_ITERATIONS && x*x + y*y < R0_2; ++i)
            {
                coord_t old_x = x;

                x = x*x - y*y + xi0;
                y = 2*old_x*y + yi0;
            }

            if (mode == CALCULATIONS) continue;

            if (i == MAX_ITERATIONS)
            {
                image.setPixel(xi, yi, sf::Color::Black);
                continue;
            }

            image.setPixel(xi, yi, sf::Color((i*10) % 256, 0, (255-i) / 3));
        }
    }

    fps->finish = clock();

    fps->total_time += fps->finish - fps->start;
    (fps->nframes)++;

    if (mode == CALCULATIONS && fps->total_time < MIN_TIME) SimpleCalc(mode, scale, image, fps);

    return OK;
}
