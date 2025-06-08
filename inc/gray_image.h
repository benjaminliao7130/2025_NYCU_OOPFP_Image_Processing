#ifndef GRAY_IMAGE_H_
#define GRAY_IMAGE_H_

#include "image.h"

class GrayImage : public Image {
private:
    int **data;

public:
    GrayImage();
    ~GrayImage();
    
    bool LoadImage(std::string filename) override;
    void DumpImage(std::string filename) override;
    void Display_X_Server() override;
    void Display_ASCII() override;
    void Display_CMD() override;

    void applyFilters(int bitfield);
    void applyMosaic(int blockSize = 8);  
    void applyFlip();
    void applyGaussian();
    void applyLaplacian();
    
    int** getData() const { return data; }
    
    void Resize(int newW, int newH);
    void setSize(int width, int height);
};

#endif
