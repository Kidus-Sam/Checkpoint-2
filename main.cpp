
#include <iostream>
#include "Color.h"
#include "Raster.h"
#include "Vector2.h"
#include "Triangle2D.h"
using namespace std;

    int main()
    {
        Raster myRaster= Raster(100,100,White);
        Triangle2D myTriangle(Vector2(-8,15),Vector2(118,-10), Vector2(45,80), Green, Black, Blue);
        myRaster.drawTriangle_Barycentric(myTriangle);
        myRaster.writeToPPM();
    }
