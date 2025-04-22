#include "../include/Calculations.h"

int ArgCheck(const int argc)
{
    if (argc < 2)
    {
        fprintf(stderr, "Too few arguments for main()\n");
        return ERROR;
    }

    return OK;
}

int ScaleCtor(scale_t* scale)
{
    if (!scale)
    {
        fprintf(stderr, "ScaleCtor() error: NULL-pointer\n");
        return ERROR;
    }

    scale->x0       = X0;
    scale->y0       = Y0;
    scale->pxl_size = PXL_PER_UNIT;

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

int HandleGraphics(scale_t* scale, fps_t* fps, const lab_mode_t lab_mode, sf::Image& image)
{
    image.create(WIDTH, HEIGHT, sf::Color::Black);

    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "The Mandelbrot set");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                MoveImage(event.key.code, scale);
            }
        }

        if (Calculate(&lab_mode, *scale, image, fps) != OK) return ERROR;

        sf::Texture texture;
        texture.loadFromImage(image);

        sf::Sprite sprite(texture);

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return OK;
}

int MoveImage(int key, scale_t* scale)
{
    if (!scale)
    {
        fprintf(stderr, "MoveImage() error: NULL-pointer\n");
        return ERROR;
    }

    switch(key)
    {
        case sf::Keyboard::Left:
        {
            scale->x0 += DELTA_X;
            break;
        }

        case sf::Keyboard::Right:
        {
            scale->x0 -= DELTA_X;
            break;
        }

        case sf::Keyboard::Up:
        {
            scale->y0 += DELTA_Y;
            break;
        }

        case sf::Keyboard::Down:
        {
            scale->y0 -= DELTA_Y;
            break;
        }

        case sf::Keyboard::Z:
        {
            scale->pxl_size += DELTA_SCALE;
            break;
        }

        case sf::Keyboard::X:
        {
            scale->pxl_size -= DELTA_SCALE;
            break;
        }

        case sf::Keyboard::Escape:
        {
            scale->x0       = X0;
            scale->y0       = Y0;
            scale->pxl_size = PXL_PER_UNIT;
            break;
        }
        default:
            break;
    }

    return OK;
}

int Calculate(const lab_mode_t* lab_mode, const scale_t scale, sf::Image& image, fps_t* fps)
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
            SimpleCalc(lab_mode->mode, scale, image, fps);
            break;
        }

        case ARRAY:
        {
            ArrayCalc(lab_mode->mode, scale, image, fps);
            break;
        }

        case SIMD:
        {
            SIMDCalc(lab_mode->mode, scale, image, fps);
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
