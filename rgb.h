#ifndef RGB
#define RGB

#define class_size 100

// Structure of colors
typedef struct
{
    char class[class_size]; // Whether the color is dark or light
    int R, G, B;            // Co-ordinate of the color in the RGB model
    double distance;        // Distance from the subject point
} Color;

// // Function to sort an array of colors by distance
void sortByDistance(Color *, int);

// This function finds classification of a color 'c' using
// k nearest neighbour algorithm. It classes the color as either
// 'dark' or 'light'.
void classifyAColor(Color *, int, Color *);

void fillColor(char *, Color *, int *);

// Import samples from the csv dataset and returns number of colors
int readColorsFromCSV(char *, Color *, int *);

#endif