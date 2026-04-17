#pragma once

#include "pixel.hpp"
#include <algorithm>

// Clamp helper
int clamp(int value) {
    return std::max(0, std::min(255, value));
}

// Apply one 3x3 box blur pass
Image blurPass(const Image& img) {
    int height = img.size();
    int width = img[0].size();

    Image result = img;

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {

            int sumR = 0, sumG = 0, sumB = 0;

            // 3x3 kernel
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    const Pixel& p = img[y + ky][x + kx];
                    sumR += p.r;
                    sumG += p.g;
                    sumB += p.b;
                }
            }

            result[y][x].r = clamp(sumR / 9);
            result[y][x].g = clamp(sumG / 9);
            result[y][x].b = clamp(sumB / 9);
        }
    }

    return result;
}