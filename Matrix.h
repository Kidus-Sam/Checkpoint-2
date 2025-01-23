#ifndef Matrix_H
#define Matrix_H
#include "Vector.h"

struct Matrix4
{
public:
float ix;
float iy;
float iz;
float iw;
float jx;
float jy;
float jz;
float jw;
float kx;
float ky;
float kz;
float kw;
float ox;
float oy;
float oz;
float ow;

Matrix4();
Matrix4(float ix,float jx,float kx,float ox,float iy,float jy,float ky,float oy,float iz,float jz,float kz,float oz,float iw,float jw,float kw,float ow);
Vector4 operator*(const Vector4& vector);
Matrix4 operator*(const Matrix4& matrix);
void print();
     
};

Matrix4 translate3D(float tX, float tY, float tZ);
Matrix4 scale3D(float sX, float sY, float sZ);
Matrix4 rotateX3D(float degrees);
Matrix4 rotateY3D(float degrees);
Matrix4 rotateZ3D(float degrees);
Matrix4 rotate3D(float degreesX, float degreesY, float degreesZ);
Matrix4 rotate3D(float degrees, Vector4 vec);
Matrix4 lookAt(Vector4 eye, Vector4 spot, Vector4 up);
Matrix4 orthographic(float minX,float maxX, float minY, float maxY, float minZ, float maxZ);
Matrix4 perspective(float fovY,float aspect, float nearZ, float farZ);
Matrix4 viewport(float x, float y, float width, float height);



#endif