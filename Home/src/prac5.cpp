#include <iostream>
#include <graphics.h>
using namespace std;
/*
Program to generate Hibert Curve using the concept of fractals
Hilbert Curve:--
    1. Define a starting point and a direction.
    2. Divide the space into four quadrants.
    3. Recursively draw the curve in each quadrant.
    4. Move the cursor to the next quadrant.
    5. Repeat the process until the desired level of recursion is reached.
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
        delay(100);//delay to show step by step drawing
    }
}

int main()
{
    int gd = DETECT, gm;
    int n = 4;
    int x0 = 50, y0 = 150, x, y, h = 10, r = 2, d = 3, l = 4, u = 1;
    x = x0;
    y = y0;


    initgraph(&gd, &gm, NULL);       
    moveto(x, y);                    // Move to the starting point
    hilbert(r, d, l, u, n, h, x, y); // Draw the Hilbert curve recusively 
    getch();      // Wait for a key press
    closegraph(); // Close the graphics window
    return 0;
}