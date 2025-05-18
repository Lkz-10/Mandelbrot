#include "../include/Calculations.h"

int main(const int argc, const char** argv)
{
    if (ArgCheck(argc) != OK) return ERROR;

    struct scale_t      scale    = {};
    struct cycles_t     cycles   = {};
    struct lab_mode_t   lab_mode = {};

    if (ScaleCtor(&scale) != OK) return ERROR;

    sf::Image image;

    if (SetMode(argc, argv, &lab_mode, &cycles) != OK) return ERROR;

    if (lab_mode.mode == GRAPHICS)
    {
        if (HandleGraphics(&scale, lab_mode, image) != OK) return ERROR;
    }
    else
    {
        for (int i = 0; i < cycles.nframes_max; ++i)
        {
            cycles.start = _rdtsc();

            if (Calculate(&lab_mode, scale, image) != OK) return ERROR;

            cycles.finish        = _rdtsc();
            cycles.total_cycles += cycles.finish - cycles.start;
            cycles.nframes++;
        }

        std::cout << (double)(cycles.total_cycles) / (double)(cycles.nframes) << " cycles" << std::endl;
    }

    return 0;
}
