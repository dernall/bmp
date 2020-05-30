#include <cstdio>
#include "image.h"

int main(int argc, char **argv)
{

	Image test("input2.bmp");
	Image img2('b', 24, 1028, 1364); //downscale 2x hor
	test /= img2;
	test.writeImage("result1.bmp");
	return 0;
} // namespace App