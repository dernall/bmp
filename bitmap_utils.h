#ifndef BITMAPHEADER_H_
#define BITMAPHEADER_H_
struct BITMAPINFOHEADER
{
    int size;
    int width;
    int height;
    short int planes;
    short int bitCount;
    int compression;
    int sizeImage;
    int XPelsPerMeter;
    int YPelsPerMeter;
    int colorUsed;
    int colorImportant;

    BITMAPINFOHEADER() : size(40), width(0), height(0), planes(1), bitCount(0), compression(0), sizeImage(0), XPelsPerMeter(0), YPelsPerMeter(0), colorUsed(0), colorImportant(0) {}

    BITMAPINFOHEADER(unsigned short bCount, int _width, int _height) : size(0), width(_width), height(_height), planes(1), bitCount(bCount), compression(0), XPelsPerMeter(0), YPelsPerMeter(0), colorUsed(0), colorImportant(0)
    {
        sizeImage = bitCount * this->height * this->width;
    }


    BITMAPINFOHEADER operator=(const BITMAPINFOHEADER &other)
    {
        if (this == &other)
            return *this;
        size = other.size;
        width = other.width;
        height = other.height;
        planes = other.planes;
        bitCount = other.bitCount;
        compression = other.compression;
        sizeImage = other.sizeImage;
        XPelsPerMeter = other.XPelsPerMeter;
        YPelsPerMeter = other.YPelsPerMeter;
        colorUsed = other.colorUsed;
        colorImportant = other.colorImportant;
        return *this;
    }
    ~BITMAPINFOHEADER() {}
};
struct BITMAPFILEHEADER
{
    short int type;
    int size;
    short int reserved1;
    short int reserved2;
    int offsetBits;

    BITMAPFILEHEADER() : type(0x4D42), size(0), reserved1(0), reserved2(0), offsetBits(0) {}

    BITMAPFILEHEADER(unsigned short bCount, int width, int height) : type(0x4D42), reserved1(0), reserved2(0), offsetBits(0)
    {
        size = bCount * width * height + offsetBits;
    }
    ~BITMAPFILEHEADER() {}
};

struct RGBQUAD
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char reserved;
};

struct RGBTRIPLE
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};
#endif // BITMAPHEADER_H_