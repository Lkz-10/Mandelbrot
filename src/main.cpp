#include "../include/Calculations.h"

int main(const int argc, const char** argv)
{
    if (ArgCheck(argc) != OK) return ERROR;

    struct scale_t      scale    = {};
    struct fps_t        fps      = {};
    struct lab_mode_t   lab_mode = {};

    if (ScaleCtor(&scale) != OK) return ERROR;

    sf::Image image;

    if (SetMode(argv, &lab_mode) != OK) return ERROR;

    if (lab_mode.mode == GRAPHICS)
    {
        if (HandleGraphics(&scale, &fps, lab_mode, image) != OK) return ERROR;
    }
    else
    {
        if (Calculate(&lab_mode, scale, image, &fps) != OK) return ERROR;

        std::cout << "FPS = " << fps.nframes * (coord_t)CLOCKS_PER_SEC / (coord_t)(fps.total_time) << std::endl;
    }

    return 0;
}
