#include "../include/Calculations.h"

int SimpleCalc(int mode, sf::Image& image, fps_t* fps)
{
    if (!fps)
    {
        fprintf(stderr, "SimpleCalc() error: &fps = %p\n", fps);
        return ERROR;
    }

    fps->start = clock();

    for (coord_t xi = 0; xi < WIDTH; ++xi)
    {
        for (coord_t yi = 0; yi < HEIGHT; ++yi)
        {
            coord_t xi0 = (xi - X0) / PXL_PER_UNIT,
                    yi0 = (yi - Y0) / PXL_PER_UNIT,
                    x   = xi0,
                    y   = yi0;

            int i = 0;
            for ( ; i < MAX_ITERATIONS && x*x + y*y < R0_2; ++i)
            {
                coord_t old_x = x;

                x = x*x - y*y + xi0;
                y = 2*old_x*y + yi0;
            }

            if (mode == CALCULATIONS || i == MAX_ITERATIONS) continue;

            image.setPixel(xi, yi, sf::Color((i*10) % 256, 0, (255-i) / 3));
        }
    }

    fps->finish = clock();

    fps->total_time += fps->finish - fps->start;
    (fps->nframes)++;

    //std::cerr << "fps: " << nframes * CLOCKS_PER_SEC / (coord_t)(end - start) << std::endl;

    return OK;
}
