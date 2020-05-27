#include "image.h"
Image::Image()
{
    infoHeader = new BITMAPINFOHEADER();
    rgbQuad = NULL;
}

Image::Image(char mode, unsigned short bCount, int width, int height)
{
    infoHeader = new BITMAPINFOHEADER(bCount, width, height);
    rgbQuad = new RGBQUAD *[infoHeader->height];
    for (int i = 0; i < infoHeader->height; ++i)
        rgbQuad[i] = new RGBQUAD[infoHeader->width]; //TODO NOT A POINTER

    for (int i = 0; i < infoHeader->height; ++i)
        for (int j = 0; j < infoHeader->width; ++j)
        {
            rgbQuad[i][j].red = mode;
            rgbQuad[i][j].green = mode;
            rgbQuad[i][j].blue = mode;
            rgbQuad[i][j].reserved = 0;
        }
}

Image::~Image()
{
    for (int i = 0; i < infoHeader->height; ++i)
        delete rgbQuad[i];
    delete[] rgbQuad;
    delete infoHeader;
}

Image Image::operator=(const Image other)
{
    this->infoHeader = other.infoHeader; //TODO MEMORY LEAK
    this->rgbQuad = other.rgbQuad;
    return *this;
    //TODO
}

int Image::loadImage(const char *filename)
{
    BITMAPFILEHEADER *bfh = new BITMAPFILEHEADER();

    FILE *file;
    file = fopen(filename, "rb");
    if (file == NULL)
    {
        std::cout << "File(input) reading error" << '\n';
        return -3; //TODO EXCEPTIONS
    }

    int tryToRead = 0;
    tryToRead = fread(&bfh, sizeof(bfh) - 2, 1, file);
    if (tryToRead == 0)
    {
        std::cout << "Reading error. Your file is not .bmp"
                  << "\n";
        return -2;
    }

    tryToRead = fread(infoHeader, sizeof(infoHeader), 1, file);
    if (tryToRead == 0)
    {
        std::cout << "Reading error"
                  << "\n";
        return -2;
    }

    rgbQuad = new RGBQUAD *[infoHeader->height];
    for (int i = 0; i < infoHeader->height; ++i)
        rgbQuad[i] = new RGBQUAD[infoHeader->width];

    int alignment = 4 - (infoHeader->width * 3) % 4;
    for (int i = 0; i < infoHeader->height; ++i)
    {
        fread(rgbQuad, sizeof(RGBQUAD), infoHeader->width, file);
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
    file = fopen(filename, "rb");
    if (file == NULL)
    {
        std::cout << "File(input) reading error" << '\n';
        exit(0); //TODO EXCEPTIONS
    }
    BITMAPFILEHEADER *bfh = new BITMAPFILEHEADER(infoHeader->bitCount, infoHeader->width, infoHeader->height);
    char buf = 0;
    int alignment = 4 - (infoHeader->width * 3) % 4;
    fwrite(&bfh, sizeof(bfh) - 2, 1, file);
    fwrite(infoHeader, sizeof(infoHeader), 1, file);
    for (int i = 0; i < infoHeader->height; ++i)
    {
        fwrite(rgbQuad[i], sizeof(RGBQUAD), infoHeader->width, file);
        if (alignment != 4)
        {
            fwrite(&buf, 1, alignment, file);
        }
    }
}