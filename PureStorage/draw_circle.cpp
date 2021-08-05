
// C-program for circle drawing 
// using Bresenham’s Algorithm 
// in computer-graphics 
#include <iostream>

using namespace std;

void putpixel(int x, int y) {
    cout<< x << "," << y << endl;
}
  
// Function to put pixels 
// at subsequence points 
void drawCircle(int xc, int yc, int x, int y) 
{ 
    putpixel(xc+x, yc+y); 
    putpixel(xc-x, yc+y); 
    putpixel(xc+x, yc-y); 
    putpixel(xc-x, yc-y); 
    putpixel(xc+y, yc+x); 
    putpixel(xc-y, yc+x); 
    putpixel(xc+y, yc-x); 
    putpixel(xc-y, yc-x); 
} 
  
// Function for circle-generation 
// using Bresenham's algorithm 
void circleBres(int xc, int yc, int r) 
{ 
    int x = 0, y = r; 
    int d = 3 - 2 * r; 
    drawCircle(xc, yc, x, y); 
    while (y >= x) 
    { 
        // for each pixel we will 
        // draw all eight pixels 
          
        x++; 
  
        // check for decision parameter 
        // and correspondingly  
        // update d, x, y 
        if (d > 0) 
        { 
            y--;  
            d = d + 4 * (x - y) + 10; 
        } 
        else
            d = d + 4 * x + 6; 
        drawCircle(xc, yc, x, y);
    } 
} 
  
  
// driver function 
int main() 
{ 
    int xc = 0, yc = 0, r2 = 10; 
    circleBres(xc, yc, r2);    // function call 
    return 0; 
}