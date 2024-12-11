#include <iostream>
#include <graphics.h>
using namespace std;
/*Program  to implement Cohen Southerland line clipping algorithm.
    ALGORITHM :-
    STEP 1: Define the region codes for the endpoints of the line.
    STEP 2: If both region codes are 0000, then the line is completely inside the window.
    STEP 3: If the bitwise AND of the region codes is not 0000, then the line is completely outside the window.
    STEP 4: If the bitwise AND of the region codes is 0000, then the line may be partially inside the window.
    STEP 5: Find the intersection points of the line with the window.
    STEP 6: Clip the line using the intersection points.
*/
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

int x_min = 100, y_min = 100, x_max = 300, y_max = 300;


// Function to compute the region code for a point (x, y)
int region_codes(double x, double y)
{
    int code = INSIDE;

    if (x < x_min)
        code |= LEFT;
    if (x > x_max)
        code |= RIGHT;
    if (y < y_min)
        code |= BOTTOM;
    if (y > y_max)
        code |= TOP;
    return code;
}

void clipping(double x1, double y1, double x2, double y2){
    int code1 = region_codes(x1, y1);
    int code2 = region_codes(x2, y2);

    bool accept = false;

    line(x1, y1, x2, y2);
    
    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            // If both endpoints lie within rectangle
            accept = true;
            break;
        }
        else if (code1 & code2) {
            // If both endpoints are outside rectangle,
            // in same region
            break;
        }
        else {
            // Some segment of line lies within the
            // rectangle
            int code_out;
            double x, y;

            // At least one endpoint is outside the
            // rectangle, pick it.
            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            // Find intersection point;
            // using formulas y = y1 + slope * (x - x1),
            // x = x1 + (1 / slope) * (y - y1)
            if (code_out & TOP) {
                // point is above the clip rectangle
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            }
            else if (code_out & BOTTOM) {
                // point is below the rectangle
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            }
            else if (code_out & RIGHT) {
                // point is to the right of rectangle
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            }
            else if (code_out & LEFT) {
                // point is to the left of rectangle
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            // Now intersection point x, y is found
            // We replace point outside rectangle
            // by intersection point
            if (code_out == code1) {
                x1 = x;
                y1 = y;
                code1 = region_codes(x1, y1);
            }
            else {
                x2 = x;
                y2 = y;
                code2 = region_codes(x2, y2);
            }
        }
    }
    if (accept) {
        cout << "Line accepted from (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ")" << endl;
        //clear screen
        getch();
        cleardevice();
        setcolor(WHITE);
        rectangle(x_min, y_min, x_max, y_max);
        setcolor(GREEN);
        line(x1, y1, x2, y2);
        setcolor(WHITE);
    } else {
        cout << "Line rejected" << endl;
        setcolor(RED); // Set line color to red for the rejected line
        line(x1, y1, x2, y2);
    }
}

int main(){
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    // Draw the window
    rectangle(100, 100, 300, 300);
    // draw and clip
    clipping(50, 50, 150, 150);
    getch();
    clipping(200, 200, 350, 350);
    getch();
    clipping(50, 50, 400, 400);
    getch();
    closegraph();
    return 0;
}