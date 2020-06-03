#ifndef IMAGE_H_
#define IMAGE_H_

#include "bitmap_utils.h"
#include <iostream>
#include <cassert>
#include <cmath>

class Image
{
private:
    BITMAPINFOHEADER infoHeader;
    RGBQUAD **rgbQuad;
    RGBQUAD *palette;

public:
    Image();
    Image(const char mode, const unsigned short bCount, const int width, const int height);
    Image(const char *filename);
    Image(const Image &other);
    int loadImage(const char *filename);
    void writeImage(const char *filename) const;
    Image &operator=(const Image &other);
    Image &operator/=(const Image &other);
    Image &operator/(const short depth);
    ~Image();
};
#endif //IMAGE_H_