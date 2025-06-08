#include "rgb_image.h"
#include "bit_field_filter.h"
#include <iostream>
#include <algorithm>
#include <vector>

RGBImage::RGBImage() {
    data = nullptr;
}

RGBImage::~RGBImage() {
    if (data) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                delete[] data[i][j];
            }
            delete[] data[i];
        }
        delete[] data;
    }
}

bool RGBImage::LoadImage(std::string filename) {
    Data_Loader loader;
    data = loader.Load_RGB(filename, &width, &height);
    return data != nullptr;
}

void RGBImage::DumpImage(std::string filename) {
    Data_Loader loader;
    loader.Dump_RGB(width, height, data, filename);
}

void RGBImage::Display_X_Server() {
    Data_Loader loader;
    loader.Display_RGB_X_Server(width, height, data);
}

void RGBImage::Display_ASCII() {
    Data_Loader loader;
    loader.Display_RGB_ASCII(width, height, data);
}

void RGBImage::Display_CMD() {
    Display_ASCII();
}

void RGBImage::applyFilters(int bitfield) {
    printEnabledFilters(bitfield);
    if (isFilterEnabled(bitfield, FILTER_FLIP)) applyFlip();
    if (isFilterEnabled(bitfield, FILTER_MOSAIC)) applyMosaic();
    if (isFilterEnabled(bitfield, FILTER_GAUSSIAN)) applyGaussian();
    if (isFilterEnabled(bitfield, FILTER_LAPLACIAN)) applyLaplacian();
}

void RGBImage::applyFlip() {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width / 2; ++j)
            for (int c = 0; c < 3; ++c)
                std::swap(data[i][j][c], data[i][width - j - 1][c]);
}

void RGBImage::applyMosaic(int blockSize) {
    for (int i = 0; i < height; i += blockSize) {
        for (int j = 0; j < width; j += blockSize) {
            int sum[3] = {0, 0, 0}, count = 0;
            for (int bi = 0; bi < blockSize && i + bi < height; ++bi)
                for (int bj = 0; bj < blockSize && j + bj < width; ++bj) {
                    for (int c = 0; c < 3; ++c)
                        sum[c] += data[i + bi][j + bj][c];
                    ++count;
                }

            int avg[3] = {sum[0] / count, sum[1] / count, sum[2] / count};

            for (int bi = 0; bi < blockSize && i + bi < height; ++bi)
                for (int bj = 0; bj < blockSize && j + bj < width; ++bj)
                    for (int c = 0; c < 3; ++c)
                        data[i + bi][j + bj][c] = avg[c];
        }
    }
}

void RGBImage::applyGaussian() {
    int kernel[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };

    int*** new_data = new int**[height];
    for (int i = 0; i < height; ++i) {
        new_data[i] = new int*[width];
        for (int j = 0; j < width; ++j) {
            new_data[i][j] = new int[3]{};
        }
    }

    for (int i = 1; i < height - 1; ++i)
        for (int j = 1; j < width - 1; ++j)
            for (int c = 0; c < 3; ++c) {
                int val = 0;
                for (int ki = -1; ki <= 1; ++ki)
                    for (int kj = -1; kj <= 1; ++kj)
                        val += kernel[ki + 1][kj + 1] * data[i + ki][j + kj][c];
                new_data[i][j][c] = val / 16;
            }

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            for (int c = 0; c < 3; ++c)
                data[i][j][c] = new_data[i][j][c];

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) delete[] new_data[i][j];
        delete[] new_data[i];
    }
    delete[] new_data;
}

void RGBImage::applyLaplacian() {
    int kernel[3][3] = {
        {-1, -1, -1},
        {-1,  9, -1},
        {-1, -1, -1}
    };

    int*** new_data = new int**[height];
    for (int i = 0; i < height; ++i) {
        new_data[i] = new int*[width];
        for (int j = 0; j < width; ++j)
            new_data[i][j] = new int[3]{};
    }

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            for (int c = 0; c < 3; ++c) {
                int val = 0;
                for (int ki = -1; ki <= 1; ++ki)
                    for (int kj = -1; kj <= 1; ++kj)
                        val += kernel[ki + 1][kj + 1] * data[i + ki][j + kj][c];
                new_data[i][j][c] = std::max(0, std::min(255, val));
            }
        }
    }

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            for (int c = 0; c < 3; ++c)
                data[i][j][c] = new_data[i][j][c];

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j)
            delete[] new_data[i][j];
        delete[] new_data[i];
    }
    delete[] new_data;
}

void RGBImage::Resize(int newW, int newH) {
    if (data) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j)
                delete[] data[i][j];
            delete[] data[i];
        }
        delete[] data;
    }
    width = newW;
    height = newH;
    data = new int**[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new int*[width];
        for (int j = 0; j < width; ++j)
            data[i][j] = new int[3]{};
    }
}

void RGBImage::setSize(int w, int h) {
    width = w;
    height = h;

    if (data) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) delete[] data[i][j];
            delete[] data[i];
        }
        delete[] data;
    }

    data = new int**[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new int*[width];
        for (int j = 0; j < width; ++j) {
            data[i][j] = new int[3];
            memset(data[i][j], 0, sizeof(int) * 3);
        }
    }
}

