#include<iostream>
#include<graphics.h>
#include<math.h>
using namespace std;
/*
Program to  to implement bouncing ball using sine wave form. Apply the concept of polymorphism. 
*/

void drawBall(int x, int y, int r){
    circle(x, y, r);
    floodfill(x, y, WHITE);
}


void sineWave(int x, int y, int r){
    while(true){
        for(int i = 0; i < 360; i++){
            int x1 = x + i;
            int y1 = y + r * sin(i * 3.14159 / 180);
            
            putpixel(x1, y1, YELLOW);
            putpixel(x1, y1 + 1, YELLOW);
            putpixel(x1, y1 - 1, YELLOW);

            drawBall(x1, y1, 20);
            cleardevice();
            delay(10);
        }
    }
}

int main(){
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    sineWave(100, 100, 40);
    
    getch();
    closegraph();
    return 0;
}