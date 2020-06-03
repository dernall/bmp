#include "image.h"

int main(int argc, char **argv)
{
	// CREATION
	//Image test(char(1), 1, 2304, 1296);
	Image img24("alallal.bmp");
	//Image img2("input.bmp");
	//test = img24; Will be failed
	Image r = img24 / 1;
	//Image img = img24;
	//Image imag(img);
	//img24.writeImage("zhopa.bmp");
	//img.writeImage("operator=.bmp");
	//imag.writeImage("copyConstructor.bmp");
	r.writeImage("test1.bmp");

	//RESIZING
	//Image test('r', 1, 1028, 341);
	//Image img = img24 /= test;
	//img.writeImage("=).bmp");
	return 0;
} // namespace App