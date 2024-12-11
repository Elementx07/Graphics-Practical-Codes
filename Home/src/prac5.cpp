#include <iostream>
#include <graphics.h>
using namespace std;
/*
Program to generate Hibert Curve using the concept of fractals
Hilbert Curve:--
    1. Start with a square of side length 2^n.
    2. Divide the square into 4 equal parts.
    3. Draw a curve in the following order:--
        a. Bottom left part
        b. Top left part
        c. Top right part
        d. Bottom right part
    4. Repeat the above steps for each part.
*/

// Function to move the cursor
void move(int &x, int &y, int dir, int len)
{
    switch(dir){
        case 1: y -= len; break;
        case 2: x += len; break;
        case 3: y += len; break;
        case 4: x -= len; break;
    }
    lineto(x, y); // Draw the line
}

// Function to draw the Hilbert Curve
void hilbert(int r, int d, int l, int u, int i, int h, int &x, int &y)
{
    if (i > 0)
    {
        i--; // Decrement recursion level

        // Draw smaller curves and move as per the Hilbert curve logic
        hilbert(d, r, u, l, i, h, x, y); // 1st quadrant
        move(x, y, r, h);
        hilbert(r, d, l, u, i, h, x, y); // 2nd quadrant
        move(x, y, d, h);
        hilbert(r, d, l, u, i, h, x, y); // 3rd quadrant
        move(x, y, l, h);
        hilbert(u, l, d, r, i, h, x, y); // 4th quadrant
    }
}

int main()
{
    int gd = DETECT, gm;
    int n = 4;
    int x0 = 50, y0 = 150, x, y, h = 10, r = 2, d = 3, l = 4, u = 1;
    x = x0;
    y = y0;


    initgraph(&gd, &gm, NULL);       // Initialize the graphics window
    moveto(x, y);                    // Move to the starting point
    hilbert(r, d, l, u, n, h, x, y); // Draw the Hilbert curve
    delay(100000);                   // Wait for some time
    getch();      // Wait for a key press
    closegraph(); // Close the graphics window
    return 0;
}