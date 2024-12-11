#include<iostream>
#include<graphics.h>
using namespace std;
/*
Program to draw 2-D object and perform following basic transformations, 
a) Scaling b) Translation c) Rotation. Apply the concept of operator overloading.
*/

class Shape{
    public:
    virtual void draw() = 0;
    virtual void scale(float) = 0;
    virtual void translate(int, int) = 0;
    virtual void rotate(int) = 0;
};

class Rectangle : public Shape{
    int x1, y1, x2, y2;
    public:
    Rectangle(int x1, int y1, int x2, int y2){
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }

    void draw(){
        rectangle(x1, y1, x2, y2);
    }

    void scale(float s){
        x1 *= s;
        y1 *= s;
        x2 *= s;
        y2 *= s;
    }

    void translate(int dx, int dy){
        x1 += dx;
        y1 += dy;
        x2 += dx;
        y2 += dy;
    }

    void rotate(int angle){
        float theta = angle * 3.14159 / 180;
        int x = (x1 + x2) / 2;
        int y = (y1 + y2) / 2;
        x1 = x + (x1 - x) * cos(theta) - (y1 - y) * sin(theta);
        y1 = y + (x1 - x) * sin(theta) + (y1 - y) * cos(theta);
        x2 = x + (x2 - x) * cos(theta) - (y2 - y) * sin(theta);
        y2 = y + (x2 - x) * sin(theta) + (y2 - y) * cos(theta);
    }
};

int main(){
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    Rectangle r(100, 100, 200, 200);
    r.draw();
    getch();

    r.scale(1.5);
    r.draw();
    getch();

    r.translate(50, 50);
    r.draw();
    getch();

    r.rotate(45);
    r.draw();
    getch();

    getch();
    closegraph();
    return 0;
}