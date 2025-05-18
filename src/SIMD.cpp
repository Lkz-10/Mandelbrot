#include "../include/Calculations.h"

int SIMDCalc(const int mode, const scale_t scale, sf::Image& image)
{
    __m128 _R0_2 = _mm_set_ps1(R0_2);

    for (coord_t yi = 0; yi < HEIGHT; ++yi)
    {
        __m128 yi0 = _mm_set_ps1((yi - scale.y0) / scale.pxl_size);

        for (coord_t xi = 0; xi < WIDTH; xi += ARR_SIZE)
        {
            __m128 xi0 = _mm_set_ps((xi + 3 - scale.x0) / scale.pxl_size,
                                    (xi + 2 - scale.x0) / scale.pxl_size,
                                    (xi + 1 - scale.x0) / scale.pxl_size,
                                    (xi     - scale.x0) / scale.pxl_size);

            volatile __m128 x = xi0, y = yi0;
            __m128i iter = _mm_setzero_si128();

            int mask = 0;
            __m128i max_iter = _mm_set_epi32(MAX_ITERATIONS, MAX_ITERATIONS, MAX_ITERATIONS, MAX_ITERATIONS);

            while (_mm_movemask_ps(_mm_castsi128_ps(_mm_cmplt_epi32(iter, max_iter))) &&
                   mask != (1 << ARR_SIZE) - 1)
            {
                __m128 x2 = _mm_mul_ps(x, x);
                __m128 y2 = _mm_mul_ps(y, y);
                __m128 xy = _mm_mul_ps(x, y);

                x = _mm_add_ps(_mm_sub_ps(x2, y2), xi0);
                y = _mm_add_ps(_mm_mul_ps(xy, _mm_set_ps1(2.f)), yi0);

                __m128 r2 = _mm_add_ps(x2, y2);

                __m128 cmp = _mm_cmpge_ps(r2, _R0_2);

                int new_mask = _mm_movemask_ps(cmp);
                int new_pixels = new_mask & (~mask);

                if (new_pixels)
                {
                    for (int i = 0; i < ARR_SIZE; ++i)
                    {
                        if (new_pixels & (1 << i))
                        {
                            mask |= (1 << i);

                            if (mode == CALCULATIONS) continue;

                            int n_iter = _mm_extract_epi16(iter, 0);

                            image.setPixel(xi + i, yi, sf::Color((n_iter * 10) % 256, 0, (255 - n_iter) / 3));
                        }
                    }
                }

                iter = _mm_add_epi32(iter, _mm_set_epi32(1, 1, 1, 1));
            }

            if (mode == GRAPHICS && mask != (1 << ARR_SIZE) - 1)
            {
                for (int i = 0; i < ARR_SIZE; ++i)
                {
                    if (!(mask & (1 << i)))
                    {
                        image.setPixel(xi + i, yi, sf::Color::Black);
                    }
                }
            }
        }
    }

    return OK;
}
