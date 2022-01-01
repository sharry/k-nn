// C program to classify colors
// using k-nearest-neighbour algorithm.

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define line_size 300
#define mode_size 100
#define colors_size 100

// Radius
#define k 4

// Structure of colors
typedef struct
{
	char mode[mode_size]; // Whether the color is dark or light
	int R, G, B;		  // Co-ordinate of the color in the RGB model
	double distance;	  // Distance from the subject point
} Color;

// Function to sort an array of colors by distance
void sortByDistance(Color *colors, int n)
{
	int i, j;
	Color temp;
	for (i = 0; i < n - 1; i++)
		for (j = i + 1; j < n; j++)
			if ((colors + i)->distance > (colors + j)->distance)
			{
				temp = *(colors + i);
				*(colors + i) = *(colors + j);
				*(colors + j) = temp;
			}
}

// This function finds classification of a color 'c' using
// k nearest neighbour algorithm. It classes the color as either
// a 'dark mode color' or a 'light mode colors'.

void classifyAColor(Color *colors, int n, Color *c)
{
	// Fill distances of all points from c.
	// Using euclidean distance calculation:
	// d = ((x₂ - x₁)² + (y₂ - y₁)² + (z₂ - z₁)²)½
	for (int i = 0; i < n; i++)
		(colors + i)->distance =
			sqrt(((colors + i)->R - c->R) * ((colors + i)->R - c->R) +
				 ((colors + i)->G - c->G) * ((colors + i)->G - c->G) +
				 ((colors + i)->B - c->B) * ((colors + i)->B - c->B));

	// Sort the colors by distance
	sortByDistance(colors, n);

	// Now consider the first k elements

	int frequencyOfNeibouringDarkColors = 0;
	int frequencyOfNeibouringLightColors = 0;

	for (int i = 0; i < k; i++)
	{
		if (strcmp((colors + i)->mode, "dark") == 0)
			frequencyOfNeibouringDarkColors++;
		else if (strcmp((colors + i)->mode, "light") == 0)
			frequencyOfNeibouringLightColors++;
	}

	if (frequencyOfNeibouringDarkColors > frequencyOfNeibouringLightColors)
		strcpy(c->mode, "dark");
	else
		strcpy(c->mode, "light");
}

void fillColor(char *line, Color *color, int *p)
{
	char *token = strtok(line, ",");
	Color c;
	char *values[colors_size];
	int i = 0;
	while (token != NULL)
	{
		values[i++] = token;
		token = (char *)strtok(NULL, ",");
	}
	strncpy(c.mode, values[0], 20);
	strtok(c.mode, "\n");
	c.R = atoi(values[1]);
	c.G = atoi(values[2]);
	c.B = atoi(values[3]);
	*(color + *p) = c;
	(*p)++;
}

int readColorsFromCSV(char *filename, Color *color, int *p)
{
	FILE *stream = fopen(filename, "r");
	char line[line_size];
	fgets(line, line_size, stream);
	int n = 0;
	while (fgets(line, line_size, stream))
	{
		char *tmp = strdup(line);
		fillColor(tmp, color, p);
		free(tmp);
		n++;
	}
	return n;
}

int main()
{
	int p = 0;
	Color colors[colors_size];
	int n = readColorsFromCSV("data.csv", colors, &p);
	printf("%d", n);

	// Testing subject
	printf("Find whether a color belongs to light mode or dark mode using k-nn algorithm.\n");
	printf("\nDefine your color (RGB)\n\n");
	int r, g, b;
	do
	{
		printf("Red value (0 - 255):\t");
		scanf("%d", &r);
	} while (r < 0 || r > 255);
	do
	{
		printf("Green value (0 - 255):\t");
		scanf("%d", &g);
	} while (g < 0 || g > 255);
	do
	{
		printf("Blue value (0 - 255):\t");
		scanf("%d", &b);
	} while (b < 0 || b > 255);

	// Apply algorithm:
	Color subject;
	subject.R = r;
	subject.G = g;
	subject.B = b;
	classifyAColor(colors, n, &subject);
	printf("\nThis color (#%02X%02X%02X) is suitable for %s mode theme.",
		   subject.R,
		   subject.G,
		   subject.B,
		   subject.mode);

	return 0;
}
