#include <iostream>
#include <graphics.h>
#include <math.h>
using namespace std;
/*
Program to  to implement bouncing ball using sine wave form. Apply the concept of polymorphism.
*/

void drawBall(int x, int y, int r){
    circle(x, y, r);
    floodfill(x, y, WHITE);   
}

void drawWave(int x, int y, int r){
    for (int i = 0; i < 360; i++){
        int x1 = x + i;
        int y1 = y + r * sin(i * 3.14159 / 180);
        putpixel(x1, y1, YELLOW);
    }
}

void sineWave(int x, int y, int r){
    while(true){
        for (int i = 0; i < 360; i++){
            int x1 = x + i;
            int y1 = y + r * sin(i * 3.14159 / 180);

            drawWave(x, y, r);
            drawBall(x1, y1, 20);
            delay(10);
            cleardevice();
        }
    }
}

int main(){
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    sineWave(0, 100, 60);

    getch();
    closegraph();
    return 0;
}