#include<iostream>
#include<graphics.h>
#include<math.h>
using namespace std;
/*
Program to draw 2-D object and perform following basic transformations, 
a) Scaling b) Translation c) Rotation. Apply the concept of operator overloading.
*/


class Rec{
    int x1, y1, x2, y2;
    public:
    Rec(int x1, int y1, int x2, int y2){
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }

    void draw(){
        rectangle(x1, y1, x2, y2);
    }

    //overload * operator to scale
    Rec operator*(float s){
        return Rec(x1 * s, y1 * s, x2 * s, y2 * s);
    }

    //overload + operator to translate
    Rec operator+(int t){
        return Rec(x1 + t, y1 + t, x2 + t, y2 + t);
    }

    //overload % operator to rotate
    Rec operator%(int angle){
        float theta = angle * 3.14159 / 180;
        int x = (x1 + x2) / 2;
        int y = (y1 + y2) / 2;
        int x1 = x + (x1 - x) * cos(theta) - (y1 - y) * sin(theta);
        int y1 = y + (x1 - x) * sin(theta) + (y1 - y) * cos(theta);
        int x2 = x + (x2 - x) * cos(theta) - (y2 - y) * sin(theta);
        int y2 = y + (x2 - x) * sin(theta) + (y2 - y) * cos(theta);
        return Rec(x1, y1, x2, y2);
    }
};

int main(){
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    Rec r(100, 100, 200, 250);
    r.draw();
    getch();


    cleardevice();
    r = r + 50; //translate by 50 units, call overloaded + operator
    r.draw();
    getch();


    cleardevice();
    r = r * 2; //scale by 2, call overloaded * operator
    r.draw();
    getch();

    cleardevice();
    r = r % 60; //rotate by 60 degrees, call overloaded % operator
    r.draw();
    getch();

    closegraph();
    return 0;
}