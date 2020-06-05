#ifndef BITMAPHEADER_H_
#define BITMAPHEADER_H_
struct BITMAPINFOHEADER //Info header of BMP file.
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

    BITMAPINFOHEADER();
    BITMAPINFOHEADER(const unsigned short bCount, const int _width, const int _height); //Constructor for header
    BITMAPINFOHEADER operator=(const BITMAPINFOHEADER &other);
    ~BITMAPINFOHEADER();
};

struct BITMAPFILEHEADER //File header of BMP file.
{
    short int type;
    int size;
    short int reserved1;
    short int reserved2;
    int offsetBits;

    BITMAPFILEHEADER();
    BITMAPFILEHEADER(const unsigned short bCount, const int width, const int height); //Constructor for header
    ~BITMAPFILEHEADER();
};

struct RGBQUAD //Struct for storing 32bit pixel info.
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char reserved;
};

struct RGBTRIPLE //Struct for storing 24bit pixel info
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};
#endif // BITMAPHEADER_H_