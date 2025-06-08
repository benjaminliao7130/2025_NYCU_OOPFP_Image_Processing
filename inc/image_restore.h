#ifndef IMAGE_RESTORE_H
#define IMAGE_RESTORE_H

#define FILTER_UNSHARP 16

class ImageRestore {
public:
    void restoreGray(int** data, int width, int height);
    void restoreRGB(int*** data, int width, int height);
};

#endif
