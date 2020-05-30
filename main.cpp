#include <cstdio>
#include "image.h"

int main(int argc, char **argv)
{
	Image test("input1.bmp");
	// Image test('b', 24, 600, 400);
	Image img2;
	img2 = test;
	// test.writeImage("resultzhopa.bmp");
	img2.writeImage("resultzhopa.bmp");
	return 0;
} // namespace App