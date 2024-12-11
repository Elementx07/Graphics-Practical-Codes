#include<iostream>
#include<graphics.h>
#include<math.h>
using namespace std;

int main(){
    int gd = DETECT, gm;
    

    initgraph(&gd, &gm, NULL);
    

    getch();
    closegraph();
    return 0;
}