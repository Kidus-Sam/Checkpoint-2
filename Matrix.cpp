#include "Matrix.h"
#include <cmath>
#include <iostream>
#include "math.h"
using namespace std;




Matrix4::Matrix4()
{
ix = 0;
iy = 0;
iz = 0;
iw = 0;
jx = 0;
jy = 0;
jz = 0;
jw = 0;
kx = 0;
ky = 0;
kz = 0;
kw = 0;
ox = 0;
oy = 0;
oz = 0;
ow = 0;
}

Matrix4::Matrix4(float pix,float pjx,float pkx,float pox,float piy,float pjy,float pky,float poy,float piz,float pjz,float pkz,float poz,float piw,float pjw,float pkw,float pow)
{
ix = pix;
iy = piy;
iz = piz;
iw = piw;
jx = pjx;
jy = pjy;
jz = pjz;
jw = pjw;
kx = pkx;
ky = pky;
kz = pkz;
kw = pkw;
ox = pox;
oy = poy;
oz = poz;
ow = pow;
}

Vector4 Matrix4::operator*(const Vector4& vector)
{
  Vector4 newVector;
  Vector4 iVector = Vector4(ix,iy,iz,iw);
  Vector4 jVector = Vector4(jx,jy,jz,jw);
  Vector4 kVector = Vector4(kx,ky,kz,kw);
  Vector4 oVector = Vector4(ox,oy,oz,ow);
  iVector = iVector*vector.x;
  jVector = jVector*vector.y;
  kVector = kVector*vector.z;
  oVector = oVector*vector.w;
  newVector= iVector + jVector + kVector + oVector;
  return newVector;
}

Matrix4 Matrix4::operator*(const Matrix4& matrix)
{
    Matrix4 newMatrix;
    Vector4 iVector = Vector4(matrix.ix,matrix.iy,matrix.iz,matrix.iw);
    Vector4 jVector = Vector4(matrix.jx,matrix.jy,matrix.jz,matrix.jw);
    Vector4 kVector = Vector4(matrix.kx,matrix.ky,matrix.kz,matrix.kw);
    Vector4 oVector = Vector4(matrix.ox,matrix.oy,matrix.oz,matrix.ow);
    iVector = *this*iVector;
    jVector = *this*jVector;
    kVector = *this*kVector;
    oVector = *this*oVector;
    newMatrix = Matrix4(iVector.x,jVector.x,kVector.x,oVector.x,iVector.y,jVector.y,kVector.y,oVector.y,iVector.z,jVector.z,kVector.z,oVector.z,iVector.w,jVector.w,kVector.w,oVector.w);
    return newMatrix;
}

void Matrix4::print()
{
   cout << ix << ", " << jx << ", " <<  kx << ", " << ox << endl;
   cout << iy << ", " << jy << ", " <<  ky << ", " << oy << endl;
   cout << iz << ", " << jz << ", " <<  kz << ", " << oz << endl;
   cout << iw << ", " << jw << ", " <<  kw << ", " << ow << endl;
}

Matrix4 translate3D(float tX, float tY, float tZ)
{
    return Matrix4(
      1,0,0,tX,
      0,1,0,tY,
      0,0,1,tZ,
      0,0,0,1);
    
}

Matrix4 scale3D(float sX, float sY, float sZ)
{
    return Matrix4(
      sX,0,0,0,
      0,sY,0,0,
      0,0,sZ,0,
      0,0,0,1);
}

Matrix4 rotateX3D(float degrees)
{
  float radians = degrees * M_PI / 180.0;
  return Matrix4(
    1,0,0,0,
    0,cos(radians),sin(radians),0,
    0,-sin(radians),cos(radians),0,
    0,0,0,1);
}

Matrix4 rotateY3D(float degrees)
{
  float radians = degrees * M_PI / 180.0;
  return Matrix4(
    cos(radians),0,-sin(radians),0,
    0,1,0,0,
    sin(radians),0,cos(radians),0,
    0,0,0,1);
}

Matrix4 rotateZ3D(float degrees)
{
  float radians = degrees * M_PI / 180.0;
  return Matrix4(
    cos(radians),sin(radians),0,0,
  -sin(radians),cos(radians),0,0,
  0,0,1,0,
  0,0,0,1);
}

Matrix4 rotate3D(float degreesX, float degreesY, float degreesZ)
{
  return rotateX3D(degreesX) * rotateY3D(degreesY) * rotateZ3D(degreesZ);
}

Matrix4 rotate3D(float degrees, Vector4 vec)
{
    return rotateY3D(-atanf(vec.x / vec.z)) * rotateX3D(-acosf(vec.y / vec.magnitude())) * rotateY3D(degrees) * rotateX3D(acosf(vec.y / vec.magnitude())) * rotateY3D(atanf(vec.x / vec.z));
}

Matrix4 lookAt(Vector4 eye, Vector4 spot, Vector4 up)
{
    Vector4 look = (spot-eye).normalize();
   Vector4 right = (look.cross(up)).normalize();
   up = (right.cross(look)).normalize();

  //  Vector4 look = Vector4(0,0,-1,1);
  // Vector4 right = Vector4(1,0,0,1);
  // up = Vector4(0,1,0,1);


    return Matrix4(
      right.x,right.y,right.z,0,
      up.x,up.y,up.z,0,
      -look.x,-look.y,-look.z,0,
      0,0,0,1) * Matrix4(
        1,0,0,-eye.x,
        0,1,0,-eye.y,
        0,0,1,-eye.z,
        0,0,0,1);
}

Matrix4 orthographic(float minX,float maxX, float minY, float maxY, float minZ, float maxZ)
{
  Matrix4 translate = translate3D(-(minX+maxX)/2, -(minY+maxY)/2, -(minZ+maxZ)/2);
  Matrix4 scale = scale3D(2/(maxX - minX), 2/(maxY - minY), 2/(maxZ - minZ));
  return scale * translate;
}

Matrix4 perspective(float fovY,float aspect, float nearZ, float farZ)
{
  fovY = fovY * M_PI / 180.0; // IF problems maybe remove this
  float nx = 1/ (tan(fovY/2)*aspect);
  float ny = 1/(tan(fovY/2));
  float nz = (farZ + nearZ) / (nearZ - farZ);
  float nz2 = 2*(nearZ * farZ) / (nearZ - farZ);
  return Matrix4(
    nx,0,0,0,
    0,ny,0,0,
    0,0,nz,nz2,
    0,0,-1,0);
}

Matrix4 viewport(float x, float y, float width, float height) 
{

  return translate3D(x,y,0) * scale3D(width,height,1) * scale3D(0.5,0.5,0.5) * translate3D(1,1,-1);
 // return translate3D(1,1,-1) * scale3D(0.5,0.5,0.5) * scale3D(width,height,1) * translate3D(x,y,0);
}





 