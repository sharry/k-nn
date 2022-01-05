// C program to classify colors
// using k-nearest-neighbors algorithm.

#include <stdio.h>
#include "rgb.h"

#define colors_size 100

int main()
{
	int p = 0;
	Color colors[colors_size];
	int n = readColorsFromCSV("data.csv", colors, &p);
	printf("%d", n);

	// Testing subject
	printf("Find whether a color belongs to light colors or dark colors using k-nn algorithm.\n");
	printf("\nDefine your color (RGB)\n\n");
	int r, g, b;
	do
	{
		printf("Red value\t(0 - 255) :\t");
		scanf("%d", &r);
	} while (r < 0 || r > 255);
	do
	{
		printf("Green value\t(0 - 255) :\t");
		scanf("%d", &g);
	} while (g < 0 || g > 255);
	do
	{
		printf("Blue value\t(0 - 255) :\t");
		scanf("%d", &b);
	} while (b < 0 || b > 255);

	// Apply algorithm:
	Color subject;
	subject.R = r;
	subject.G = g;
	subject.B = b;
	classifyAColor(colors, n, &subject);
	printf("\nThis color (#%02X%02X%02X) is a %s color.",
		   subject.R,
		   subject.G,
		   subject.B,
		   subject.class);

	return 0;
}
