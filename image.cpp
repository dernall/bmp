#include "image.h"

/**
*An empty constructor
*/

Image::Image() : rgbQuad(NULL)
{
}

/**
*A constructor
*taking four arguments and returning an image
*param mode a color of pixels
*param bCount a number of bits per one pixel
*param width a width of the image
*param height a height of the image
*/

Image::Image(const char mode, const unsigned short bCount, const int width, const int height)
{
    assert((width > 0 && height > 0) && "Incorrect dimentions");
    assert((bCount == 4 || bCount == 8 || bCount == 24 || bCount == 32) && "Incorrect number of bits per one pixel");
    infoHeader.bitCount = bCount;
    infoHeader.width = width;
    infoHeader.height = height;
    infoHeader.sizeImage = bCount * height * width;

    rgbQuad = new RGBQUAD *[infoHeader.height];
    for (int i = 0; i < infoHeader.height; ++i)
        rgbQuad[i] = new RGBQUAD[infoHeader.width];

    if (infoHeader.bitCount == 4 || infoHeader.bitCount == 8)
    {
        int num = pow(2, infoHeader.bitCount);
        palette = new RGBQUAD[num];
        for (int i = 0; i < num; ++i)
        {
            if (infoHeader.bitCount == 8)
                palette[i].red = palette[i].green = palette[i].blue = i;

            if (infoHeader.bitCount == 4)
            {
                int temp = i * 17;
                palette[i].red = palette[i].green = palette[i].blue = temp;
            }
        }
    }

    for (int i = 0; i < infoHeader.height; ++i)
        for (int j = 0; j < infoHeader.width; ++j)
        {
            rgbQuad[i][j].red = mode;
            rgbQuad[i][j].green = mode;
            rgbQuad[i][j].blue = mode;
            rgbQuad[i][j].reserved = 0;
        }
}

/**
*An assignment operator
*taking one argument and returning an image equal to the image from an argument
*param other an image that should be assigned
*/

Image &Image::operator=(const Image &other)
{
    assert(infoHeader.sizeImage == 0 && "Could not define this image to iamge that is initialised");

    for (int i = 0; i < infoHeader.height; ++i)
    {
        delete rgbQuad[i];
    }
    delete[] rgbQuad;

    infoHeader = other.infoHeader;
    rgbQuad = new RGBQUAD *[infoHeader.height];
    for (int i = 0; i < infoHeader.height; ++i)
        rgbQuad[i] = new RGBQUAD[infoHeader.width];

    if (infoHeader.bitCount == 4 || infoHeader.bitCount == 8)
    {
        int num = pow(2, infoHeader.bitCount);
        palette = new RGBQUAD[num];
        for (int i = 0; i < num; ++i)
            palette[i].red = palette[i].green = palette[i].blue = other.palette[i].red;
    }

    for (int i = 0; i < infoHeader.height; ++i)
        for (int j = 0; j < infoHeader.width; ++j)
            rgbQuad[i][j] = other.rgbQuad[i][j];
    return *this;
}

/**
*A copy constructor
*taking one argument and returning an image equal to the image from an argument
*param other the image that should be copied
*/

Image::Image(const Image &other)
{
    infoHeader = other.infoHeader;
    rgbQuad = new RGBQUAD *[infoHeader.height];
    for (int i = 0; i < infoHeader.height; ++i)
        rgbQuad[i] = new RGBQUAD[infoHeader.width];

    if (infoHeader.bitCount == 4 || infoHeader.bitCount == 8)
    {
        int num = pow(2, infoHeader.bitCount);
        palette = new RGBQUAD[num];
        for (int i = 0; i < num; ++i)
            palette[i].red = palette[i].green = palette[i].blue = other.palette[i].red;
    }

    for (int i = 0; i < infoHeader.height; ++i)
        for (int j = 0; j < infoHeader.width; ++j)
            rgbQuad[i][j] = other.rgbQuad[i][j];
}

/**
*A constructor
*taking one argument and returning an image generated from .bmp file
*param filename the name of file
*/

Image::Image(const char *filename)
{
    loadImage(filename);
}

/**
*A destructor
*/

Image::~Image()
{
    for (int i = 0; i < infoHeader.height; ++i)
        delete rgbQuad[i];
    delete[] rgbQuad;
    if (infoHeader.bitCount == 4 || infoHeader.bitCount == 8)
        delete[] palette;
}

/**
*A method that generate an image from the file
*taking one argument and returning an image generated from .bmp file
*param filename the name of file
*/

int Image::loadImage(const char *filename)
{
    BITMAPFILEHEADER bfh;
    FILE *file;
    file = fopen(filename, "rb");
    assert(file != NULL && "Error with opening a file");

    int tryToRead = 0;
    tryToRead = fread(&bfh, sizeof(BITMAPFILEHEADER) - 2, 1, file);

    assert(tryToRead != 0 && "Reading error. Your file is not .bmp");
    tryToRead = fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file);

    assert(tryToRead != 0 && "Reading error");

    rgbQuad = new RGBQUAD *[infoHeader.height];
    for (int i = 0; i < infoHeader.height; ++i)
        rgbQuad[i] = new RGBQUAD[infoHeader.width];
    int alignment = 4 - (infoHeader.width * 3) % 4;

    if (infoHeader.bitCount == 4 || infoHeader.bitCount == 8)
    {
        int num = pow(2, infoHeader.bitCount);
        palette = new RGBQUAD[num];
        for (int i = 0; i < num; ++i)
            fread(&palette[i], sizeof(RGBQUAD), 1, file);
        for (int i = 0; i < infoHeader.height; ++i)
        {
            for (int j = 0; j < infoHeader.width;)
            {
                if (infoHeader.bitCount == 4)
                {
                    unsigned char pix = 0;
                    int mask = 0xF0;
                    fread(&pix, sizeof(unsigned char), 1, file);
                    rgbQuad[i][j].red = rgbQuad[i][j].blue = rgbQuad[i][j].green = (pix & mask) >> 4;
                    rgbQuad[i][j + 1].red = rgbQuad[i][j + 1].blue = rgbQuad[i][j + 1].green = pix & (mask >> 4);
                    j += 2;
                }
                else if (infoHeader.bitCount == 8)
                {
                    unsigned char pix = 0;
                    fread(&pix, sizeof(unsigned char), 1, file);
                    rgbQuad[i][j].red = rgbQuad[i][j].blue = rgbQuad[i][j].green = pix;
                    ++j;
                }
            }
            if (alignment != 4)
                fseek(file, alignment, SEEK_CUR);
        }
        fclose(file);
        return 1;
    }
    else
    {

        RGBTRIPLE rgbTriple;
        for (int i = 0; i < infoHeader.height; ++i)
        {
            if (infoHeader.bitCount == 24)
            {
                for (int j = 0; j < infoHeader.width; ++j)
                {
                    fread(&rgbTriple, sizeof(RGBTRIPLE), 1, file);
                    rgbQuad[i][j].red = rgbTriple.red;
                    rgbQuad[i][j].green = rgbTriple.green;
                    rgbQuad[i][j].blue = rgbTriple.blue;
                    rgbQuad[i][j].reserved = 0;
                }
            }
            else if (infoHeader.bitCount == 32)
                fread(rgbQuad[i], sizeof(RGBQUAD), infoHeader.width, file);

            if (alignment != 4)
                fseek(file, alignment, SEEK_CUR);
        }
    }
    fclose(file);
    return 1;
}

/**
*A method that save an image to the file
*taking one argument
*param filename the name of file
*/

void Image::writeImage(const char *filename) const
{
    assert(infoHeader.sizeImage != 0 && "Invalid operation with empty image");
    FILE *file;
    file = fopen(filename, "wb");
    assert(file != NULL && "Error with opening a file");

    BITMAPFILEHEADER bfh(infoHeader.bitCount, infoHeader.width, infoHeader.height);
    if (infoHeader.bitCount == 8)
        bfh.reserved2 = 1078;

    if (infoHeader.bitCount == 4)
        bfh.reserved2 = 118;

    char buf = 0;
    int alignment = 4 - (infoHeader.width * 3) % 4;
    fwrite(&bfh, sizeof(BITMAPFILEHEADER) - 2, 1, file);
    fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file);
    if (infoHeader.bitCount == 4 || infoHeader.bitCount == 8)
    {
        if (infoHeader.bitCount == 8)
            alignment = (infoHeader.width * 3) % 4;
        else if (infoHeader.bitCount == 4)
            if (infoHeader.width % 2 == 0)
                alignment = (4 - (infoHeader.width / 2) % 4) % 4;
            else
                alignment = (4 - ((int)trunc(infoHeader.width / 2) + 1) % 4) % 4;
        unsigned char pix = 0;
        for (int i = 0; i < pow(2, infoHeader.bitCount); ++i)
            fwrite(&palette[i], sizeof(RGBQUAD), 1, file);
        for (int i = 0; i < infoHeader.height; ++i)
        {
            for (int j = 0; j < infoHeader.width;)
            {
                pix = 0;
                if (infoHeader.bitCount == 4)
                {
                    pix = rgbQuad[i][j].red << 4;
                    pix += rgbQuad[i][j + 1].red;
                    j += 2;
                }
                else
                {
                    pix = rgbQuad[i][j].red;
                    ++j;
                }
                fwrite(&pix, sizeof(unsigned char), 1, file);
            }
            if (alignment != 4)
                fwrite(&buf, 1, alignment, file);
        }
    }
    else
    {
        RGBTRIPLE rgbTriple;
        for (int i = 0; i < infoHeader.height; ++i)
        {
            if (infoHeader.bitCount == 24)
            {
                for (int j = 0; j < infoHeader.width; ++j)
                {
                    rgbTriple.red = rgbQuad[i][j].red;
                    rgbTriple.green = rgbQuad[i][j].green;
                    rgbTriple.blue = rgbQuad[i][j].blue;
                    fwrite(&rgbTriple, sizeof(RGBTRIPLE), 1, file);
                }
            }
            else if (infoHeader.bitCount == 32)
                fwrite(rgbQuad[i], sizeof(RGBQUAD), infoHeader.width, file);

            if (alignment != 4)
                fwrite(&buf, 1, alignment, file);
        }
    }
    fclose(file);
}

/**
*Scaling operator
*taking one argument and returning an image scaled to the image from argument
*param other the image with target mentions
*/

Image &Image::operator/=(const Image &other)
{
    assert(infoHeader.sizeImage != 0 && "Invalid operation with empty image");
    assert(((other.infoHeader.width % this->infoHeader.width == 0 &&
             other.infoHeader.height % this->infoHeader.height == 0) ||
            (this->infoHeader.width % other.infoHeader.width == 0 &&
             this->infoHeader.height % other.infoHeader.height == 0)) &&
           "Resizing is unpredictable");

    Image *temp = new Image();
    temp->infoHeader = other.infoHeader;
    int tempI = 0;

    if (other.infoHeader.width >= this->infoHeader.width && other.infoHeader.height >= this->infoHeader.height)
    {
        int repeatX = other.infoHeader.width / this->infoHeader.width;
        int repeatY = other.infoHeader.height / this->infoHeader.height;

        temp->rgbQuad = new RGBQUAD *[other.infoHeader.height];
        for (int i = 0; i < other.infoHeader.height; ++i)
            temp->rgbQuad[i] = new RGBQUAD[other.infoHeader.width];
        for (int i = 0; i < other.infoHeader.height; ++i)
        {
            for (int rY = 0; rY < repeatY; ++rY)
            {
                int tempJ = 0;
                for (int j = 0; j < other.infoHeader.width; ++j)
                {
                    for (int rX = 0; rX < repeatX; ++rX)
                        temp->rgbQuad[i + rY][j + rX] = this->rgbQuad[tempI][tempJ];
                    j += repeatX - 1;
                    ++tempJ;
                }
                tempJ = 0;
            }
            i += repeatY - 1;
            ++tempI;
        }
    }
    else if (other.infoHeader.width <= this->infoHeader.width && other.infoHeader.height <= this->infoHeader.height)
    {
        int repeatX = this->infoHeader.width / other.infoHeader.width;
        int repeatY = this->infoHeader.height / other.infoHeader.height;

        temp->rgbQuad = new RGBQUAD *[other.infoHeader.height];
        for (int i = 0; i < other.infoHeader.height; ++i)
            temp->rgbQuad[i] = new RGBQUAD[other.infoHeader.width];

        for (int i = 0; i < other.infoHeader.height; ++i)
        {
            int tempJ = 0;
            for (int j = 0; j < other.infoHeader.width; ++j)
            {
                temp->rgbQuad[i][j] = this->rgbQuad[tempI][tempJ];
                tempJ += repeatX;
            }
            tempI += repeatY;
        }
    }

    this->rgbQuad = temp->rgbQuad;
    this->infoHeader = temp->infoHeader;
    return *this;
}

/**
*Changing depth operator
*taking one argument and returning an image with a new depth
*param depth new depth of pixels
*/

Image &Image::operator/(const short depth)
{
    assert(infoHeader.sizeImage != 0 && "Invalid operation with empty image");
    int num = pow(2, depth);
    if (infoHeader.bitCount == 8 || infoHeader.bitCount == 32 || infoHeader.bitCount == 24)
    {
        if (infoHeader.bitCount == 8)
            delete[] palette;
        palette = new RGBQUAD[num];
        for (int i = 0; i < num; ++i)
        {
            if (depth == 4)
            {
                int temp = i * 17;
                palette[i].red = palette[i].green = palette[i].blue = temp;
            }
            else
                palette[i].red = palette[i].green = palette[i].blue = i;
        }
        for (int i = 0; i < infoHeader.height; ++i)
            for (int j = 0; j < infoHeader.width; ++j)
            {
                int pix = (int)(0.299 * rgbQuad[i][j].red + 0.597 * rgbQuad[i][j].green + 0.114 * rgbQuad[i][j].blue);

                if (pix == 0)
                    ++pix;
                if (depth == 8)
                    rgbQuad[i][j].red = rgbQuad[i][j].blue = rgbQuad[i][j].green = pix - 1;
                if (depth == 4)
                    rgbQuad[i][j].red = rgbQuad[i][j].blue = rgbQuad[i][j].green = (int)trunc(pix / 17);
            }
        infoHeader.bitCount = depth;
        infoHeader.colorUsed = num;
    }
    return *this;
}
