

## Computer Graphics Practicals

This repository contains implementations of various graphics algorithms using C++ and the graphics.h library. The project includes algorithms for line clipping, polygon filling, fractal generation, and more.

## Algorithms Implemented

1. **Scanline Polygon Fill** (prac1.cpp)
2. **Cohen-Sutherland Line Clipping** (prac2.cpp)
3. **DDA Line Drawing and Bresenham's Circle Drawing** (prac3.cpp)
4. **2D Transformations (Scaling, Translation, Rotation)** (prac4.cpp)
5. **Hilbert Curve Generation** (prac5.cpp)
6. **Bouncing Ball using Sine Wave** (prac7.cpp)

### Build

```sh
g++ Home/src/prac1.cpp -o Home/build/prac1.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
```

### Run

```sh
Home/build/prac1.exe
```

## Dependencies

- [graphics.h](https://www.cs.colorado.edu/~main/bgi/doc/)
- GCC or compatible C++ compiler
