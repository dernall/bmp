#ifndef IMAGE_H_
#define IMAGE_H_

#include "bitmap_utils.h"
#include <iostream>

class Image
{
private:
    BITMAPINFOHEADER infoHeader;
    RGBQUAD **rgbQuad;
    RGBTRIPLE **rgbTriple;

public:
    Image();
    Image(const char mode, const unsigned short bCount, const int width, const int height);
    Image(const char *filename);
    Image(const Image &i);
    int loadImage(const char *filename);
    void writeImage(const char *filename);
    Image& operator=(const Image &other);
    ~Image();
};
#endif //IMAGE_H_