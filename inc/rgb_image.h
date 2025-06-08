#ifndef RGB_IMAGE_H
#define RGB_IMAGE_H

#include "image.h"

class RGBImage : public Image {
public:
    RGBImage();
    ~RGBImage();

    bool LoadImage(std::string filename) override;
    void DumpImage(std::string filename) override;
    void Display_X_Server() override;
    void Display_ASCII() override;
    void Display_CMD() override;

    void applyFilters(int bitfield);
    void applyFlip();
    void applyMosaic(int blockSize = 4);
    void applyGaussian();
    void applyLaplacian();

    int*** getData() const { return data; }

    void setSize(int width, int height);

private:
    int*** data;
};

#endif
