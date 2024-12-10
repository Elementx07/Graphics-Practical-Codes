#include<iostream>
#include<graphics.h>
using namespace std;
/*Program to fill a concave polygon using scan line algorithm
    ALGORITHM :-
    STEP 1: Find the minimum and maximum y-coordinates of the polygon.
    STEP 2: For each scan line between ymin and ymax, find the intersections of the polygon with the scan line.
    STEP 3: Sort the intersections array.
    STEP 4: Fill the pixels between pairs of intersections.
*/

void scanlinefill(int points[], int n){
    //find minimum and maximum y-coordinates
    int ymin, ymax;
    for(int i = 1; i < n; i+=2){
        if(i == 1){
            ymin = points[i];
            ymax = points[i];
        }
        else{
            ymin = min(ymin, points[i]);
            ymax = max(ymax, points[i]);
        }
    }
    // find intersections of polygon with scan line
    //start from ymin and go upto ymax
    for(int i=ymin; i<=ymax; i++){
        int intersections[10];//array to store x-coordinates of intersections
        int count = 0;//count of intersections
        
        for(int j = 0; j <n; j+=2){
            int x1 = points[j];
            int y1 = points[j+1];
            int x2 = points[(j+2)%n];
            int y2 = points[(j+3)%n];
            //check if edge is not horizontal and intersects with scan line
            if(y1 != y2 && i >= min(y1, y2) && i <= max(y1, y2)){
                //calculate x-coordinate of intersection 
                //FORMULA : x = x1 + slope * (y-y1)
                int x = x1 + (x2-x1)/(y2-y1) * (i-y1);
                intersections[count++] = x; //store intersection in array
            }
        }

        //sort intersections array
        for(int j = 0; j < count; j++){
            for(int k = 0; k < count-j-1; k++){
                if(intersections[k] > intersections[k+1]){
                    swap(intersections[k], intersections[k+1]);
                }
            }
        }

        //fill the pixels between pairs of intersections
        for (int j = 0; j < count; j+=2){
            //color the pixels between intersections
            for(int k = intersections[j]; k <= intersections[j+1]; k++){
                putpixel(k, i, CYAN);
            }
            
        }
    }

}
int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int points[] = {100, 200, 200, 200, 200, 100};
    //size of points array
    int n = sizeof(points)/sizeof(points[0]);
    //draw the polygon
    for(int i = 0; i < n; i+=2)
    {
        line(points[i], points[i+1], points[(i+2)%n], points[(i+3)%n]);
    }
    //fill the polygon
    scanlinefill(points, n);
    getch();
   closegraph();
}