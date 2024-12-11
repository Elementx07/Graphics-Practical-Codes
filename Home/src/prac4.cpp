#include <iostream>
#include <graphics.h>
#include<vector>
#include <math.h>
using namespace std;
/*
Program to draw 2-D object and perform following basic transformations,
a) Scaling b) Translation c) Rotation. Apply the concept of operator overloading.
*/

class Object
{
    vector <int> points;
    int n;
    int pivotX, pivotY;


public:
    Object(vector <int> p)
    {
        points = p;
        n = p.size();
        pivotX = points[0];
        pivotY = points[1];
    }

    void draw()
    {
        for (int i = 0; i < n; i += 2)
        {
            line(points[i], points[i + 1], points[(i + 2) % n], points[(i + 3) % n]);
        }
    }

    // overload * operator to scale
    Object operator*(float s)
    {
        vector <int> p;
        for (int i = 0; i < n; i+=2)
        {
            p.push_back(pivotX + (points[i] - pivotX) * s);
            p.push_back(pivotY + (points[i + 1] - pivotY) * s);
        }
        return Object(p);
    }

    // overload + operator to translate
    Object operator+(int t)
    {
        vector <int> p;
        for (int i = 0; i < n; i += 2)
        {
            p.push_back(points[i] + t);
            p.push_back(points[i + 1] + t);
        }
        return Object(p);
    }

    // overload % operator to rotate
    Object operator%(int angle)
    {
        vector <int> p;
        float rad = angle * 3.14159 / 180;
        for (int i = 0; i < n; i += 2)
        {
            // rotate about pivot point
            p.push_back(pivotX + (points[i] - pivotX) * cos(rad) - (points[i + 1] - pivotY) * sin(rad));
            p.push_back(pivotY + (points[i] - pivotX) * sin(rad) + (points[i + 1] - pivotY) * cos(rad));
        }
        return Object(p);
    }
};

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    vector <int> p = {100, 100, 200, 100, 200, 200, 100, 200};
    Object r(p);
    r.draw();
    getch();

    cleardevice();
    r = r + 50; // translate by 50 units, call overloaded + operator
    r.draw();
    getch();


    cleardevice();
    r = r * 2; // scale by 2, call overloaded * operator
    r.draw();
    getch();

    cleardevice();
    r = r % 30; // rotate by 30 degrees, call overloaded % operator
    r.draw();
    getch();

    closegraph();
    return 0;
}