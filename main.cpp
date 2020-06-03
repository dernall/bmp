#include "image.h"

int main(int argc, char **argv)
{
	// CREATION
	Image test(char(1), 1, 100, 100);
	Image img24("input.bmp");
	//test = img24; Will be failed
	Image img = img24;
	Image imgt = img24/1;
	Image imag(img);
	imgt.writeImage("alallal.bmp");
	//img.writeImage("operator=.bmp");
	//imag.writeImage("copyConstructor.bmp");
	test.writeImage("test.bmp");

	//RESIZING
	return 0;
} // namespace App