#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>

const double    X0              = 400,
                Y0              = 300,
                R0_2            = 100;

const int       N_ITERATIONS    = 256,
                WIDTH           = 600,
                HEIGHT          = 600,
                PXL_PER_UNIT    = 190;

const char*     WINDOW_NAME     = "The Mandelbrot set";

int main()
{
    sf::Image image;
    image.create(WIDTH, HEIGHT, sf::Color::Black);

    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), WINDOW_NAME);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        for (double xi = 0; xi < WIDTH; ++xi)
        {
            for (double yi = 0; yi < HEIGHT; ++yi)
            {
                double xi0 = (xi - X0) / PXL_PER_UNIT,
                       yi0 = (yi - Y0) / PXL_PER_UNIT,
                       x   = xi0,
                       y   = yi0;

                int i = 0;
                for ( ; i < N_ITERATIONS && x*x + y*y < R0_2; ++i)
                {
                    double old_x = x;
                    x = x*x - y*y + xi0;
                    y = 2*old_x*y + yi0;
                }

                if (i == N_ITERATIONS) continue;

                image.setPixel(xi, yi, sf::Color(i, 0, sqrt(255 - i)));
            }
        }

        sf::Texture texture;
        texture.loadFromImage(image);

        sf::Sprite sprite(texture);

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
