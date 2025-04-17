#include "../include/Globals.h"
#include "../include/Calculations.h"

int main(const int argc, const char** argv)
{
    if (ArgCheck(argc) != OK) return ERROR;

    struct fps_t        fps      = {};
    struct lab_mode_t   lab_mode = {};

    sf::Image image;

    if (SetMode(argv, &lab_mode) != OK) return ERROR;

    if (lab_mode.mode == GRAPHICS)
    {
        image.create(WIDTH, HEIGHT, sf::Color::Black);

        sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "The Mandelbrot set");

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) window.close();
            }

            if (Calculate(&lab_mode, image, &fps) != OK) return ERROR;

            sf::Texture texture;
            texture.loadFromImage(image);

            sf::Sprite sprite(texture);

            window.clear();
            window.draw(sprite);
            window.display();
        }
    }
    else
    {
        if (Calculate(&lab_mode, image, &fps) != OK) return ERROR;

        // std::cout << "nframes = " << fps.nframes << ", total_time = " << fps.total_time << " / " << CLOCKS_PER_SEC << std::endl;
        std::cout << "FPS = " << fps.nframes * (coord_t)CLOCKS_PER_SEC / (coord_t)(fps.total_time) << std::endl;
    }

    return 0;
}

int ArgCheck(const int argc)
{
    if (argc < 2)
    {
        fprintf(stderr, "Too few arguments for main()\n");
        return ERROR;
    }

    return OK;
}

int SetMode(const char** argv, struct lab_mode_t* lab_mode)
{
    if (!argv || !lab_mode)
    {
        fprintf(stderr, "SetMode() error: argv = %p, &lab_mode =  %p\n", argv, lab_mode);
        return ERROR;
    }

    if (strcmp(argv[1], "--graphics") == 0)
    {
        lab_mode->mode = GRAPHICS;
    }
    else if (strcmp(argv[1], "--calculation") == 0)
    {
        lab_mode->mode = CALCULATIONS;
    }
    else
    {
        fprintf(stderr, "Wrong key for mode: \"%s\"\n", argv[1]);
        return ERROR;
    }

    if (strcmp(argv[2], "--simple") == 0)
    {
        lab_mode->version = SIMPLE;
    }
    else if (strcmp(argv[2], "--array") == 0)
    {
        lab_mode->version = ARRAY;
    }
    else if (strcmp(argv[2], "--simd") == 0)
    {
        lab_mode->version = SIMD;
    }
    else
    {
        fprintf(stderr, "Wrong key for version: \"%s\"\n", argv[2]);
        return ERROR;
    }

    return OK;
}

int Calculate(const lab_mode_t* lab_mode, sf::Image& image, fps_t* fps)
{
    if (!lab_mode)
    {
        fprintf(stderr, "Calculate() error: &lab_mode = %p\n", lab_mode);
        return ERROR;
    }

    switch(lab_mode->version)
    {
        case SIMPLE:
        {
            SimpleCalc(lab_mode->mode, image, fps);
            break;
        }

        case ARRAY:
        {
            ArrayCalc(lab_mode->mode, image, fps);
            break;
        }

        default:
        {
            fprintf(stderr, "Calculate() error: wrong version: %d\n", lab_mode->version);
            return ERROR;
        }
    }

    return OK;
}
