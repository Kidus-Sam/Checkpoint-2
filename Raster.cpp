#include "Color.h"
#include "Raster.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include "Vector2.h"
Raster::Raster(){
    width = 0;
    height = 0;
    pixels = NULL;
}

Raster::Raster(int pWidth, int pHeight, Color pFillColor){
    width = pWidth;
    height = pHeight;
    pixels = new Color[width*height];
    for(int i = 0; i < width*height; i++){
        pixels[i] = pFillColor;
    }
}

Raster::~Raster(){
    delete[] pixels;
}

int Raster::getWidth(){
    return width;
}

int Raster::getHeight(){
    return height;
}

Color Raster::getColorPixel(int x, int y){
    int origin= (width*height)-width;
    return pixels[origin + x - (y*width)];
}

void Raster::setColorPixel(int x, int y, Color pFillColor){
    int origin= (width*height)-width;
    pixels[origin + x - (y*width)]=pFillColor;
}

void Raster::clear(Color pFillColor){
    for(int i = 0; i < width*height; i++){
        pixels[i] = pFillColor;
    }
}


//some code taken/adapted from video tutorial "https://www.youtube.com/watch?v=6byB1jX3Fnk" 
void Raster::writeToPPM(){
    std::ofstream fout("FRAME_BUFFER.ppm");
    if(fout.fail()){std::cout<<"The file could not be opened."<<std::endl; exit(1);}
    fout<<"P3"<<std::endl;
    fout<<width<<" "<<height<<std::endl;
    fout<<"255"<<std::endl;
    for(int i = height-1; i >=0; i--){
        for(int j = 0; j <width; j++){
            Color temp = getColorPixel(j, i);
            fout<<int(temp.red*255)<<" "<<int(temp.green*255)<<" "<<int(temp.blue*255)<<" ";
        }
        fout<<std::endl;
    }
}


void Raster::drawLine_DDA(float x1, float y1, float x2, float y2, Color pFillColor){
    float dx= x2-x1;
    float dy= y2-y1;
    float m = dy/dx;
    swap(x1,y1,x2,y2,m);
    check(x1,y1,x2,y2,m);
    std::cout<<"m:"<<m<<std::endl;
    std::cout<<"X1: "<<x1<<" Y1: "<<y1<<" X2: "<<x2<<" Y2: "<< y2<<std::endl;
    if(fabs(m)<=1){
        std::cout<<"X:"<<x1<<std::endl;
        float y = y1;
        for(int x=x1; x<=float(round(x2)); x++){
            setColorPixel(x, float(round(y)), pFillColor);
            y+=m;
        }
        std::cout<<"Using y=mx+b"<<std::endl;
    }
    else{
        float x=x1;
        m = dx/dy;
        for(int y=y1; y>=float(round(y2)); y--){
            setColorPixel(float(round(x)), y, pFillColor);
            x-=m;
        }
        std::cout<<"Using x=my+b"<<std::endl;
    }

}

void Raster::swap(float& x1, float& y1, float& x2, float& y2, float m){
    if(fabs(m)>1){
        if(y2>y1){
            std::swap(x1,x2);
            std::swap(y1,y2);
        }
    }
    else{
        std::cout<<"slope is less than 1"<<std::endl;
        if(x1>x2){
            std::swap(x1,x2);
            std::swap(y1,y2);
        }
    }
}

void Raster::check(float& x1, float& y1, float& x2, float& y2, float m){
    //calculate the y and x intercepts depending on the slope
    float xIntercept;
    float yIntercept;
    std::cout<<"Entered the check method"<<std::endl;
    //for the formula y=mx+b
    if(fabs(m)<=1){
        yIntercept= y1 - m*x1;
        xIntercept= -yIntercept/m;
        std::cout<<"xintercept:"<<xIntercept<<std::endl;
        std::cout<<"yintercept:"<<yIntercept<<std::endl;
        if(x1<0 && y1>0){
            x1=0;
            y1= yIntercept;
            std::cout<<"x1 is less than 0 and y1 is greater than 0"<<std::endl;
        }
        if(x1<0&&y1<0&&yIntercept>=0){
            x1=0;
            y1= yIntercept;
            std::cout<<"x1 is less than 0 and y1 is less than 0 and Xintercept is greater than 0"<<std::endl;
        }
        if(x1<0&&y1<0&&yIntercept<=0){
            x1=xIntercept;
            y1= 0;
            std::cout<<"x1 is less than 0 and y1 is less than 0 and Xintercept is less than 0"<<std::endl;
        }
        if(x2>=width&&y2<0){
            x2=width-1;
            y2= m*width + yIntercept;
            std::cout<<"x2 is greater than width and y2 is less than 0"<<std::endl;
        }
        if(y1>=height&&x1<0){
            y1=height;
            x1= (height-yIntercept)/m;
            std::cout<<"y1 is greater than height and x1 is less than 0"<<std::endl;
        }
        if(y2<0&&x2<width){
            y2=0;
            x2= (0-yIntercept)/m;
            std::cout<<"y2 is less than 0 and x2 is less than width"<<std::endl;
        }
        if(x2>=width&&y2<=height){
            x2=width-1;
            y2= m*width + yIntercept;
            std::cout<<"x2 is greater than width and y2 is less than or equal to height"<<std::endl;
        }
        if(x2>=width&&y2>=height){
            x2=width-1;
            y2=m*width + yIntercept;
            std::cout<<"x2 is greater than width and y2 is greater than height"<<std::endl;
        }
    }
    //for the formula x=my+b
    else{
        m=(x1-x2)/(y1-y2);
        xIntercept= x1 - m*y1;
        yIntercept= -xIntercept/m;
        std::cout<<"xintercept:"<<xIntercept<<std::endl;
        std::cout<<"yintercept:"<<yIntercept<<std::endl;
        std::cout<<"m-corrected:"<<m<<std::endl;
        if(x2<0&&y2>0&&xIntercept>=0){
            x2= xIntercept;
            y2=0;
            std::cout<<"x2 is less than 0 and y2 is greater than 0 and xintercept is greater than 0"<<std::endl;
        }
        if(x2<0&&y2>0&&xIntercept<0){
            x2=0;
            y2= yIntercept;
            std::cout<<"x2 is less than 0 and y2 is greater than 0 and Xintercept is less than 0"<<std::endl;
        }
        if(x2<0&&y2<0&&yIntercept>=0){
            x2=0;
            y2= yIntercept;
            std::cout<<"x2 is less than 0 and y2 is less than 0 and the yintercept is greater than 0"<<std::endl;
        }
        else if(x2<0&&y2<0&&yIntercept<0){
            x2= xIntercept;
            y2=0;
            std::cout<<"x2 is less than 0 and y2 is less than 0 and yintercept is less than 0"<<std::endl;
        }
        if(x2>=width&&y2<0){
            x2= width-1;
            y2= (x2-xIntercept)/m;
            std::cout<<"x1 is greater than width and y1 is less than 0"<<std::endl;
        }
        if(y2>=height&&x2<0){
            y2=height;
            x2= m*height + xIntercept;
            std::cout<<"y2 is greater than height and x2 is less than 0"<<std::endl;
        }
        if(y1<0&&x1<width){
            y1=height;
            x1= m*height + xIntercept;
            std::cout<<"y1 is less than 0 and x1 is less than width"<<std::endl;
        }
        if(y1>=height&&x1>=width&&(m*height + xIntercept)<height){
            y1=height;
            x1= m*height + xIntercept;
            std::cout<<"y1 is greater than height and x1 is greater than width"<<std::endl;
        }
        if(y1>=height&&x1>=width&&(m*height + xIntercept)>height){
            y1=(height-xIntercept)/m;
            x1=width-1;
            std::cout<<"y1 is greater than height and x1 is greater than width"<<std::endl;
        }
        if(x1<0&&y1>=height&&yIntercept<height){
            x1=0;
            y1= yIntercept;
            std::cout<<"x1 is less than 0 and y1 is greater than height"<<std::endl;
        }
        if(x1<0&&y1>=height&&yIntercept>height){
            x1= (height-yIntercept)/m;
            y1=height;
            std::cout<<"x1 is less than 0 and y1 is greater than height"<<std::endl;
        }
    }
}


void Raster::drawLine_DDA_Interpolated(float x1, float y1, float x2, float y2, Color color1, Color color2){
    float dx= x2-x1;
    float dy= y2-y1;
    float m = dy/dx;
    swap(x1,y1,x2,y2,m);
    check(x1,y1,x2,y2,m);
    std::cout<<"m:"<<m<<std::endl;
    std::cout<<"X1: "<<x1<<" Y1: "<<y1<<" X2: "<<x2<<" Y2: "<< y2<<std::endl;
    Vector2 myVect= Vector2(x2-x1, y2-y1);
    if(fabs(m)<=1){
        std::cout<<"X:"<<x1<<std::endl;
        float y = y1;
        for(int x=x1; x<=float(round(x2)); x++){
            Vector2 point=Vector2(x1-x,y1-y);
            float ratio=point.magnitude()/myVect.magnitude();
            Color pFillColor=color2*ratio +color1*(1-ratio);
            setColorPixel(x, float(round(y)), pFillColor);
            y+=m;
        }
        std::cout<<"Using y=mx+b"<<std::endl;
    }
    else{
        float x=x1;
        m = dx/dy;
        for(int y=y1; y>=float(round(y2)); y--){
            Vector2 point=Vector2(x1-x,y1-y);
            float ratio=point.magnitude()/myVect.magnitude();
            Color pFillColor=color2*ratio +color1*(1-ratio);
            setColorPixel(float(round(x)), y, pFillColor);
            x-=m;
        }
        std::cout<<"Using x=my+b"<<std::endl;
    }

}


void Raster::DrawTriangle2D_DotProduct(Triangle2D triangle){
    float minx=fmin(triangle.v1.x,triangle.v2.x);
    minx=fmin(minx,triangle.v3.x);
    float maxx=fmax(triangle.v1.x,triangle.v2.x);
    maxx=fmax(maxx,triangle.v3.x);
    float miny=fmin(triangle.v1.y,triangle.v2.y);
    miny=fmin(miny,triangle.v3.y);
    float maxy=fmax(triangle.v1.y,triangle.v2.y);
    maxy=fmax(maxy,triangle.v3.y);

    for(int x=minx; x<=maxx; x++){
        for(int y=miny;y<=maxy;y++){
            if(inside(triangle, x, y)){
                setColorPixel(x,y,triangle.c1);
            }
        }
    }
}

bool Raster::inside(Triangle2D triangle, int x, int y){
    Vector2 P=Vector2(x,y);
    Vector2 e1=triangle.v2-triangle.v1;
    Vector2 perp0=e1.perpendicular();
    Vector2 g0=P-triangle.v1;
    float result0=perp0.dot(g0);


    Vector2 e2=triangle.v3-triangle.v2;
    Vector2 perp1=e2.perpendicular();
    Vector2 g1=P-triangle.v2;
    float result1=perp1.dot(g1);

    Vector2 e3=triangle.v1-triangle.v3;
    Vector2 perp2=e3.perpendicular();
    Vector2 g2=P-triangle.v3;
    float result2=perp2.dot(g2);

    if(result0>=0 && result1>=0 && result2>=0 && P.x>=0 && P.y>=0 && P.x<width && P.y<height){
        return true;
    }
    else{
        return false;
    }
}

void Raster::drawTriangle_Barycentric(Triangle2D t){
    float minx=fmin(t.v1.x,t.v2.x);
    minx=fmin(minx,t.v3.x);
    float maxx=fmax(t.v1.x,t.v2.x);
    maxx=fmax(maxx,t.v3.x);
    float miny=fmin(t.v1.y,t.v2.y);
    miny=fmin(miny,t.v3.y);
    float maxy=fmax(t.v1.y,t.v2.y);
    maxy=fmax(maxy,t.v3.y);
    float lambda1;
    float lambda2;
    float lambda3;

    for(int x=minx; x<=maxx; x++){
        for(int y=miny;y<=maxy;y++){
            t.calculateBarycentricCoordinates(Vector2(x,y),lambda1,lambda2,lambda3);
            if(lambda1>=0&&lambda2>=0&&lambda3>=0&&x>=0&&x<width&&y>=0&&y<width){
                // Color mycolor(lambda1,lambda2,lambda3);
                Color myColor= (t.c1*lambda1)+(t.c2*lambda2)+(t.c3*lambda3);
                setColorPixel(x,y, myColor);
            }
        }
    }
}
