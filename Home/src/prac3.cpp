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
class Line{
    int x1, y1, x2, y2;
    public:
    Line(int x1, int y1, int x2, int y2){
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }
    void draw(){
        int dx = x2 - x1;
        int dy = y2 - y1;
        int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
        float x_inc = dx / (float)steps;
        float y_inc = dy / (float)steps;
        float x = x1;
        float y = y1;
        for(int i = 0; i <= steps; i++){
            putpixel(x, y, WHITE);
            x += x_inc;
            y += y_inc;
        }
    }
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    int x1, y1, x2, y2;
    cout << "Enter the coordinates of the first point: ";
    cin >> x1 >> y1;
    cout << "Enter the coordinates of the second point: ";
    cin >> x2 >> y2;
    getch();
    closegraph();
    return 0;
}