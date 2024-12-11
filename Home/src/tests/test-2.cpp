#include <iostream>
#include <graphics.h>
using namespace std;
/*my while logic:
// while (true){
    //     // if both region codes are 0000, then line is completely inside the window
    //     if ((code1 == 0) && (code2 == 0)){
    //         accept = true;
    //         break;
    //     }

    //     // if bitwise AND of region codes is not 0000, then line is completely outside the window
    //     else if (code1 & code2){
    //         break;
    //     }
    //     // if bitwise AND of region codes is 0000, then line may be partially inside the window
    //     else{
    //         int code_out;
    //         int x, y;

    //         // Select an outside point
    //         if (code1 != 0) {
    //             code_out = code1;
    //         } else {
    //             code_out = code2;
    //         }
    //         // find the intersection point with the window
    //         // FORMULA : y = y1 + slope * (x-x1)
    //         // check for intersection with top edge
    //         // Find the intersection point
    //         if (code_out & TOP) {
    //             // Point is above the clip rectangle
    //             x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
    //             y = y_max;
    //         } else if (code_out & BOTTOM) {
    //             // Point is below the clip rectangle
    //             x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
    //             y = y_min;
    //         } else if (code_out & RIGHT) {
    //             // Point is to the right of the clip rectangle
    //             y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
    //             x = x_max;
    //         } else if (code_out & LEFT) {
    //             // Point is to the left of the clip rectangle
    //             y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
    //             x = x_min;
    //         }

    //         // Replace the outside point with the intersection point
    //         if (code1 == code2){
    //             x1 = x;
    //             y1 = y;
    //             code1 = region_codes(x1, y1);
    //         }
    //         else{
    //             x2 = x;
    //             y2 = y;
    //             code2 = region_codes(x2, y2);
    //         }
    //     }
    //     cout<<"log: "<<code1<<" "<<code2<<endl;
    // }
*/
// Defining region codes
const int INSIDE = 0; // 0000
const int LEFT = 1; // 0001
const int RIGHT = 2; // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8; // 1000

// Defining x_max, y_max and x_min, y_min for
// clipping rectangle. Since diagonal points are
// enough to define a rectangle
int x_min = 100, y_min = 100, x_max = 300, y_max = 300;


// Function to compute region code for a point(x, y)
int computeCode(double x, double y)
{
    // initialized as being inside
    int code = INSIDE;

    if (x < x_min) // to the left of rectangle
        code |= LEFT;
    else if (x > x_max) // to the right of rectangle
        code |= RIGHT;
    if (y < y_min) // below the rectangle
        code |= BOTTOM;
    else if (y > y_max) // above the rectangle
        code |= TOP;

    return code;
}

// Implementing Cohen-Sutherland algorithm
// Clipping a line from P1 = (x2, y2) to P2 = (x2, y2)
void cohenSutherlandClip(double x1, double y1,
                         double x2, double y2)
{
    
    // Compute region codes for P1, P2
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);

    // Initialize line as outside the rectangular window
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
                code1 = computeCode(x1, y1);
            }
            else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }
    if (accept) {
        cout << "Line accepted from " << x1 << ", "
             << y1 << " to " << x2 << ", " << y2 << endl;
        //clear screen
        getch();
        cleardevice();
        setcolor(WHITE);
        rectangle(x_min, y_min, x_max, y_max);
        setcolor(GREEN);
        line(x1, y1, x2, y2);
        setcolor(WHITE);
    }
    else
        cout << "Line rejected" << endl;
}

// Driver code
int main()
{
    //draw line and rectangle
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    rectangle(x_min, y_min, x_max, y_max);
    //draw line
    // First Line segment
    cohenSutherlandClip(50, 50, 150, 150);
    getch();
    // Second Line segment
    cohenSutherlandClip(200, 200, 350, 350);
    getch();
    // Third Line segment
    cohenSutherlandClip(50, 50, 400, 400);
    getch();
    return 0;
}