#include <cstdio>
#include "image.h"

int main(int argc, char **argv)
{
	// Image *test = new Image();
	// test->loadImage("input1.bmp");
	Image test("input2.bmp");
	// Image test('w', 24, 300, 400);
	// Image img2('b', 24, 1028, 341); //upscale 2x hor 1028
	// Image img2('b', 24, 2056, 1364); //upscale 4x 1364
	Image img2('b', 24, 1028, 1364); //downscale 2x hor
	// Image img2('b', 24, 1028, 682); //downscale 2x
	// Image img2('b', 24, 514, 341); //downscale 4x

	test /= img2;
	test.writeImage("result1.bmp");
	return 0;
} // namespace App