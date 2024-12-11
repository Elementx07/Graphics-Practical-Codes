#include<iostream>
#include<graphics.h>
using namespace std;
/*
    DDA LINE DRAWING ALGORITHM:--
    1. Start with the first point (x1, y1) and calculate the slope m = (y2 - y1) / (x2 - x1).
    2. If the slope is less than 1, then increment x by 1 and calculate y using the formula y = y + m.
    3. If the slope is greater than 1, then increment y by 1 and calculate x using the formula x = x + 1 / m.
    4. Repeat the above steps until the second point (x2, y2) is reached.

    BRESENHAMS CIRCLE DRAWING ALGORITHM:--
    1. Start with the first point (x, y) and calculate the decision parameter P = 3 - 2 * r.
    2. If P < 0, then increment x by 1 and calculate P = P + 4 * x + 6.
    3. If P >= 0, then increment x by 1 and y by -1 and calculate P = P + 4 * (x - y) + 10.
    4. Repeat the above steps until x <= y.
    5. Reflect the points in all octants to draw the complete circle.
*/

//Encsapsulating the Line and Circle classes

class Line{
    int x1, y1, x2, y2;
    public:
    // Constructor to initialize the line coordinates
    Line(int x1, int y1, int x2, int y2){
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }

    // Function to draw the line using DDA algorithm
    void draw(){
        // Calculate the change in x and y
        int dx = x2 - x1;
        int dy = y2 - y1;

        // Calculate the length of the line
        int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

        // Calculate the increment in x and y
        float x_inc = dx / (float)steps;
        float y_inc = dy / (float)steps;

        // Initialize the starting point
        float x = x1;
        float y = y1;

        // Plot the points of the line
        for(int i = 0; i <= steps; i++){
            putpixel(x, y, WHITE);
            x += x_inc;
            y += y_inc;
        }
    }
};

class Circle{
    int x, y, r;
    public:
    // Constructor to initialize the circle coordinates
    Circle(int x, int y, int r){
        this->x = x;
        this->y = y;
        this->r = r;
    }

    // Function to draw the circle using Bresenham's algorithm
    void draw(){
        int x = 0, y = r;

        // Calculate the decision parameter
        int d = 3 - 2 * r;

        // Loop to plot the points of the circle
        while(x <= y){
            putpixel(x + this->x, y + this->y, WHITE);
            putpixel(y + this->x, x + this->y, WHITE);
            putpixel(-x + this->x, y + this->y, WHITE);
            putpixel(-y + this->x, x + this->y, WHITE);
            putpixel(-x + this->x, -y + this->y, WHITE);
            putpixel(-y + this->x, -x + this->y, WHITE);
            putpixel(x + this->x, -y + this->y, WHITE);
            putpixel(y + this->x, -x + this->y, WHITE);

            // Update the decision parameter
            if(d < 0){
                d += 4 * x + 6;
            }else{
                d += 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    }
};


int main(){
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    Line l1(102,150,198,150);
    Line l2(102,150,150,236);
    Line l3(150,236,198,150);
    l1.draw();
    l2.draw();
    l3.draw();

    Circle c1(150,180,57);
    //Divide the radius by 2 to draw a smaller inner circle
    Circle c2(150,180,57/2);
    c1.draw();
    c2.draw();

    getch();
    closegraph();
    return 0;
}