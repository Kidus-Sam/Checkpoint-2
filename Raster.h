#ifndef RASTER_H
#define RASTER_H
#include "Color.h"
#include "Triangle2D.h"
class Raster{
    private:
        int width;
        int height;
        Color* pixels;
    public:
        Raster();
        Raster(int pwidth, int pheight, Color pfillColor);
        ~Raster();
        int getWidth();
        int getHeight();
        Color getColorPixel(int x, int y);
        void setColorPixel(int x, int y, Color pFillColor);
        void clear(Color pFillColor);
        void writeToPPM();
        void drawLine_DDA(float x1, float y1, float x2, float y2, Color pFillColor);
        void swap(float& x1, float& y1, float& x2, float& y2, float m);
        void check(float& x1, float& y1, float& x2, float& y2, float m);
        void drawLine_DDA_Interpolated(float x1,float y1, float x2, float y2, Color color1, Color color2);
        void DrawTriangle2D_DotProduct(Triangle2D triangle);
        bool inside(Triangle2D triangle,int x, int y);
        void drawTriangle_Barycentric(Triangle2D t);

};







#endif