#include "rgb.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define line_size 300
#define colors_size 100

// Radius
#define k 4

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
// 'dark' or 'light'.

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
        if (strcmp((colors + i)->class, "dark") == 0)
            frequencyOfNeibouringDarkColors++;
        else if (strcmp((colors + i)->class, "light") == 0)
            frequencyOfNeibouringLightColors++;
    }

    if (frequencyOfNeibouringDarkColors > frequencyOfNeibouringLightColors)
        strcpy(c->class, "dark");
    else
        strcpy(c->class, "light");
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
    strncpy(c.class, values[0], 20);
    strtok(c.class, "\n");
    c.R = atoi(values[1]);
    c.G = atoi(values[2]);
    c.B = atoi(values[3]);
    *(color + *p) = c;
    (*p)++;
}

// Fetch colors from the csv dataset and returns number of colors
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