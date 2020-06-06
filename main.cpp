#include "image.h"

int main(int argc, char **argv)
{
	// CREATION
	//Image test(char(15), 4, 7, 8);
	Image img24("input8BIT.bmp");
	//test = img24; Will be failed
	Image r = img24 / 4;
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