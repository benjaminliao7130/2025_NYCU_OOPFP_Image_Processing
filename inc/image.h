#ifndef IMAGE_H_
#define IMAGE_H_

#include <string>
#include "../Data-Loader/data_loader.h"

class Image {
protected:
    int width;
    int height;
    Data_Loader loader;  

public:
    virtual bool LoadImage(std::string filename) = 0;
    virtual void DumpImage(std::string filename) = 0;
    virtual void Display_X_Server() = 0;
    virtual void Display_ASCII() = 0;
    virtual void Display_CMD() = 0;

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    virtual ~Image() {}
};

#endif
