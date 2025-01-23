
#include <iostream>
#include "Color.h"
#include "Raster.h"
#include "Vector.h"
#include "Triangle.h"
#include "Matrix.h"
#include "Model.h"

#define WIDTH 100
#define HEIGHT 100

using namespace std;

int main()
{
        Raster myRaster(WIDTH,HEIGHT, White);
        Model teapot, bunny;
        teapot.readFromOBJFile("./teapot.obj",Red);
    //    bunny.readFromOBJFile("./bunny.obj", Blue);


        Matrix4 modelMatrixTeapot = translate3D(50,50,-30) * rotateZ3D(45.0) * scale3D(0.5,0.5,0.5);
    //    Matrix4 modelMatrixBunny = translate3D(70,30,-60) * rotateZ3D(-20.0) * scale3D(500,500,500);
        Vector4 eye(50,50,30,1);
        Vector4 spot(50,50,-30,1);
        teapot.performBackfaceCulling(eye,spot);

        Matrix4 viewMatrix = lookAt(eye, spot, Vector4(0,1,0,0));

        Matrix4 perspectiveMatrix = perspective(70, myRaster.getWidth() / myRaster.getHeight(), 0.01, 88.5);

        Matrix4 viewportMatrix = viewport(0,0, myRaster.getWidth(), myRaster.getWidth());

      teapot.transform(perspectiveMatrix * viewMatrix *  modelMatrixTeapot);
    //    bunny.transform(perspectiveMatrix * viewMatrix *  modelMatrixBunny);

      teapot.homogenize();
  //    bunny.homogenize();

     teapot.transform(viewportMatrix);
  //     bunny.transform(viewportMatrix);

       myRaster.drawModel(teapot);
    //    myRaster.drawModel(bunny);

        myRaster.writeToPPM();

}
