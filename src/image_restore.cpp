#include "image_restore.h"
#include <vector>
#include <algorithm>

using namespace std;

void ImageRestore::restoreGray(int** data, int width, int height) {
    vector<vector<int>> original(height, vector<int>(width));
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            original[i][j] = data[i][j];

    int kernel[3][3] = {
        { 0, -1,  0 },
        { -1, 5, -1 },
        { 0, -1,  0 }
    };

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            int sum = 0;
            for (int ki = -1; ki <= 1; ++ki)
                for (int kj = -1; kj <= 1; ++kj)
                    sum += kernel[ki+1][kj+1] * original[i+ki][j+kj];
            data[i][j] = min(255, max(0, sum));
        }
    }
}

void ImageRestore::restoreRGB(int*** data, int width, int height) {
    vector<vector<vector<int>>> original(height, vector<vector<int>>(width, vector<int>(3)));
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            for (int c = 0; c < 3; ++c)
                original[i][j][c] = data[i][j][c];

    int kernel[3][3] = {
        { 0, -1,  0 },
        { -1, 5, -1 },
        { 0, -1,  0 }
    };

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            for (int c = 0; c < 3; ++c) {
                int sum = 0;
                for (int ki = -1; ki <= 1; ++ki)
                    for (int kj = -1; kj <= 1; ++kj)
                        sum += kernel[ki+1][kj+1] * original[i+ki][j+kj][c];
                data[i][j][c] = min(255, max(0, sum));
            }
        }
    }
}
