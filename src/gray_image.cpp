#include "gray_image.h"
#include "bit_field_filter.h"
#include <iostream>
#include <vector>
#include <algorithm>

GrayImage::GrayImage() : data(nullptr) {}

GrayImage::~GrayImage() {
    if (data) {
        for (int i = 0; i < height; ++i) delete[] data[i];
        delete[] data;
    }
}

bool GrayImage::LoadImage(std::string filename) {
    data = loader.Load_Gray(filename, &width, &height);
    return data != nullptr;
}

void GrayImage::DumpImage(std::string filename) {
    loader.Dump_Gray(width, height, data, filename);
}

void GrayImage::Display_X_Server() {
    loader.Display_Gray_X_Server(width, height, data);
}

void GrayImage::Display_ASCII() {
    loader.Display_Gray_ASCII(width, height, data);
}

void GrayImage::Display_CMD() {
    Display_ASCII();
}

void GrayImage::applyFilters(int bitfield) {
    printEnabledFilters(bitfield);
    if (isFilterEnabled(bitfield, FILTER_FLIP)) applyFlip();
    if (isFilterEnabled(bitfield, FILTER_MOSAIC)) applyMosaic();
    if (isFilterEnabled(bitfield, FILTER_GAUSSIAN)) applyGaussian();
    if (isFilterEnabled(bitfield, FILTER_LAPLACIAN)) applyLaplacian();
}

void GrayImage::applyFlip() {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width / 2; ++j)
            std::swap(data[i][j], data[i][width - j - 1]);
}

void GrayImage::applyMosaic(int blockSize) {
    for (int i = 0; i < height; i += blockSize) {
        for (int j = 0; j < width; j += blockSize) {
            int sum = 0, count = 0;
            for (int bi = 0; bi < blockSize && i + bi < height; ++bi)
                for (int bj = 0; bj < blockSize && j + bj < width; ++bj) {
                    sum += data[i + bi][j + bj];
                    ++count;
                }
            int avg = sum / count;
            for (int bi = 0; bi < blockSize && i + bi < height; ++bi)
                for (int bj = 0; bj < blockSize && j + bj < width; ++bj)
                    data[i + bi][j + bj] = avg;
        }
    }
}

void GrayImage::applyGaussian() {
    std::vector<std::vector<int>> kernel = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };
    int **new_data = new int*[height];
    for (int i = 0; i < height; ++i) new_data[i] = new int[width];

    for (int i = 1; i < height - 1; ++i)
        for (int j = 1; j < width - 1; ++j) {
            int val = 0;
            for (int ki = -1; ki <= 1; ++ki)
                for (int kj = -1; kj <= 1; ++kj)
                    val += kernel[ki + 1][kj + 1] * data[i + ki][j + kj];
            new_data[i][j] = val / 16;
        }

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            data[i][j] = new_data[i][j];

    for (int i = 0; i < height; ++i) delete[] new_data[i];
    delete[] new_data;
}

void GrayImage::applyLaplacian() {
    int kernel[3][3] = {
        {-1, -1, -1},
        {-1,  9, -1},
        {-1, -1, -1}
    };

    int** new_data = new int*[height];
    for (int i = 0; i < height; ++i)
        new_data[i] = new int[width]{};

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            int val = 0;
            for (int ki = -1; ki <= 1; ++ki)
                for (int kj = -1; kj <= 1; ++kj)
                    val += kernel[ki + 1][kj + 1] * data[i + ki][j + kj];
            new_data[i][j] = std::max(0, std::min(255, val));
        }
    }

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            data[i][j] = new_data[i][j];

    for (int i = 0; i < height; ++i)
        delete[] new_data[i];
    delete[] new_data;
}


void GrayImage::setSize(int w, int h) {
    width = w;
    height = h;

    if (data) {
        for (int i = 0; i < height; ++i) delete[] data[i];
        delete[] data;
    }

    data = new int*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new int[width];
        memset(data[i], 0, sizeof(int) * width);
    }
}


