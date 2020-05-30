#include "image.h"
Image::Image() : rgbQuad(NULL)
{
}

Image::Image(char mode, unsigned short bCount, int width, int height)
{
    infoHeader.bitCount = bCount;
    infoHeader.width = width;
    infoHeader.height = height;
    rgbQuad = new RGBQUAD *[infoHeader.height];
    for (int i = 0; i < infoHeader.height; ++i)
        rgbQuad[i] = new RGBQUAD[infoHeader.width];

    for (int i = 0; i < infoHeader.height; ++i)
        for (int j = 0; j < infoHeader.width; ++j)
        {
            rgbQuad[i][j].red = mode;
            rgbQuad[i][j].green = mode;
            rgbQuad[i][j].blue = mode;
            rgbQuad[i][j].reserved = 0;
        }
}
Image &Image::operator=(const Image &other)
{
    if (this == &other)
        return *this;

    for (int i = 0; i < infoHeader.height; ++i)
    {
        delete rgbTriple[i];
        delete rgbQuad[i];
    }
    delete[] rgbTriple;
    delete[] rgbQuad;

    infoHeader = other.infoHeader;
    rgbQuad = new RGBQUAD *[infoHeader.height];
    rgbTriple = new RGBTRIPLE *[infoHeader.height];
    for (int i = 0; i < infoHeader.height; ++i)
    {
        rgbQuad[i] = new RGBQUAD[infoHeader.width];
        rgbTriple[i] = new RGBTRIPLE[infoHeader.width];
    }

    for (int i = 0; i < infoHeader.height; ++i)
    {
        for (int j = 0; j < infoHeader.width; ++j)
        {
            rgbQuad[i][j] = other.rgbQuad[i][j];
            rgbTriple[i][j] = other.rgbTriple[i][j];
        }
    }
    return *this;
}
Image::Image(const Image &other)
{
    infoHeader = other.infoHeader;
    rgbQuad = new RGBQUAD *[infoHeader.height];
    for (int i = 0; i < infoHeader.height; ++i)
    {
        rgbQuad[i] = new RGBQUAD[infoHeader.width];
    }
    for (int i = 0; i < infoHeader.height; ++i)
    {
        for (int j = 0; j < infoHeader.width; ++j)
        {
            rgbQuad[i][j] = other.rgbQuad[i][j];
        }
    }
}
Image::Image(const char *filename)
{
    loadImage(filename);
}
Image::~Image()
{
    for (int i = 0; i < infoHeader.height; ++i)
    {
        delete rgbQuad[i];
        delete rgbTriple[i];
    }
    delete[] rgbQuad;
    delete[] rgbTriple;
}

int Image::loadImage(const char *filename)
{
    BITMAPFILEHEADER bfh;
    FILE *file;
    file = fopen(filename, "rb");
    if (file == NULL)
    {
        std::cout << "File(input) reading error" << '\n';
        return -3; //TODO EXCEPTIONS
    }

    int tryToRead = 0;
    tryToRead = fread(&bfh, sizeof(BITMAPFILEHEADER) - 2, 1, file);
    if (tryToRead == 0)
    {
        std::cout << "Reading error. Your file is not .bmp"
                  << "\n";
        return -2;
    }
    tryToRead = fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file);
    if (tryToRead == 0)
    {
        std::cout << "Reading error"
                  << "\n";
        return -2;
    }
    rgbTriple = new RGBTRIPLE *[infoHeader.height];
    rgbQuad = new RGBQUAD *[infoHeader.height];
    for (int i = 0; i < infoHeader.height; ++i)
    {
        rgbTriple[i] = new RGBTRIPLE[infoHeader.width];
        rgbQuad[i] = new RGBQUAD[infoHeader.width];
    }
    int alignment = 4 - (infoHeader.width * 3) % 4;
    for (int i = 0; i < infoHeader.height; ++i)
    {
        if (infoHeader.bitCount == 24)
        {
            fread(rgbTriple[i], sizeof(RGBTRIPLE), infoHeader.width, file);
        }
        else if (infoHeader.bitCount == 32)
        {
            fread(rgbQuad[i], sizeof(RGBQUAD), infoHeader.width, file);
        }
        if (alignment != 4)
        {
            fseek(file, alignment, SEEK_CUR);
        }
    }
    return 0;
}

void Image::writeImage(const char *filename)
{
    FILE *file;
    file = fopen(filename, "wb");
    if (file == NULL)
    {
        std::cout << "File(ouptut) reading error" << '\n';
        exit(0); //TODO EXCEPTIONS
    }

    // infoHeader.bitCount = 32;
    // infoHeader.sizeImage = infoHeader.bitCount * infoHeader.height * infoHeader.width;

    BITMAPFILEHEADER bfh(infoHeader.bitCount, infoHeader.width, infoHeader.height);
    char buf = 0;
    int alignment = 4 - (infoHeader.width * 3) % 4;
    fwrite(&bfh, sizeof(BITMAPFILEHEADER) - 2, 1, file);
    fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file);
    for (int i = 0; i < infoHeader.height; i++)
    {
        if (infoHeader.bitCount == 24)
        {
            fwrite(rgbTriple[i], sizeof(RGBTRIPLE), infoHeader.width, file);
        }
        else if (infoHeader.bitCount == 32)
        {
            fwrite(rgbQuad[i], sizeof(RGBQUAD), infoHeader.width, file);
        }
        if (alignment != 4)
        {
            fwrite(&buf, 1, alignment, file);
        }
    }
    std::cout << "PIZDA" << infoHeader.bitCount << std::endl;
}