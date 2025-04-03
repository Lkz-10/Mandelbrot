#include <iostream>
#include <math.h>
#include <ctime>
#include <SFML/Graphics.hpp>

#define _SSE_USED

typedef double coord_t;

const coord_t   X0              = 400,
                Y0              = 300,
                R0_2            = 100;

const int       SSE_ARR_SIZE    = 16 / sizeof(coord_t),
                MAX_ITERATIONS  = 256,
                WIDTH           = 600,
                HEIGHT          = 600,
                PXL_PER_UNIT    = 260;

const char*     WINDOW_NAME     = "The Mandelbrot set";

int main()
{
    sf::Image image;
    image.create(WIDTH, HEIGHT, sf::Color::Black);

    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), WINDOW_NAME);

    int nframes = 0;
    clock_t start = clock();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

#ifdef _SSE_USED

        coord_t xi0     [SSE_ARR_SIZE] = {},
                yi0     [SSE_ARR_SIZE] = {},
                x       [SSE_ARR_SIZE] = {},
                y       [SSE_ARR_SIZE] = {},
                old_x   [SSE_ARR_SIZE] = {};
        int     i       [SSE_ARR_SIZE] = {};


        for (coord_t xi = 0; xi < WIDTH; ++xi)
        {
            // !!! HEIGHT % SSE_ARR_SIZE must be 0 !!!
            for (coord_t yi = 0; yi < HEIGHT; yi += SSE_ARR_SIZE)
            {


                for (int j = 0; j < SSE_ARR_SIZE; ++j) xi0[j] = (xi     - X0) / PXL_PER_UNIT;
                for (int j = 0; j < SSE_ARR_SIZE; ++j) yi0[j] = (yi + j - Y0) / PXL_PER_UNIT;

                for (int j = 0; j < SSE_ARR_SIZE; ++j) x[j] = xi0[j];
                for (int j = 0; j < SSE_ARR_SIZE; ++j) y[j] = yi0[j];

                for (int j = 0; j < SSE_ARR_SIZE; ++j) i[j] = 0;

                for (int j = 0; j < SSE_ARR_SIZE; ++j)
                {
                    for ( ; i[j] < MAX_ITERATIONS && (x[j] * x[j]) + (y[j] * y[j]) < R0_2; ++(i[j]))
                    {
                        old_x[j] = x[j];

                        x[j] = (x[j] * x[j]) - (y[j] * y[j]) + xi0[j];
                        y[j] = (2 * old_x[j] * y[j])         + yi0[j];
                    }

                    if (i[j] == MAX_ITERATIONS) continue;

                    image.setPixel(xi, yi + j, sf::Color((i[j] * 10) % 256, 0, (255 - i[j]) / 3));
                }
            }
        }

#else

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

                if (i == MAX_ITERATIONS) continue;

                image.setPixel(xi, yi, sf::Color((i*10) % 256, 0, (255-i) / 3));
            }
        }

#endif

        sf::Texture texture;
        texture.loadFromImage(image);

        sf::Sprite sprite(texture);

        window.clear();
        window.draw(sprite);
        window.display();

        nframes++;
    }

    clock_t end = clock();

    std::cerr << "fps: " << nframes * CLOCKS_PER_SEC / (coord_t)(end - start) << std::endl;

    return 0;
}
