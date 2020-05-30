#include <cstdio>
#include "image.h"

int main(int argc, char **argv)
{
	Image test("input1.bmp");
	Image img2;
	img2 = test;
	img2.writeImage("result1.bmp");
	return 0;
} // namespace App