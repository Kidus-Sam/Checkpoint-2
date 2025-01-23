#include "Triangle.h"
#include "Vector.h"
#include "Color.h"
#include <iostream>
using namespace std;

Triangle2D::Triangle2D()
{
    v1 = Vector2(0, 0);
    v2 = Vector2(0, 0);
    v3 = Vector2(0, 0);
    c1 = Black;
    c2 = Black;
    c3 = Black;
}

Triangle2D::Triangle2D(Vector2 v1p, Vector2 v2p, Vector2 v3p, Color c1p, Color c2p, Color c3p)
{
    v1 = v1p;
    v2 = v2p;
    v3 = v3p;
    c1 = c1p;
    c2 = c2p;
    c3 = c3p;
}

Triangle2D::Triangle2D(Triangle3D t)
{
    v1 = Vector2(t.v1.x, t.v1.y);
    v2 = Vector2(t.v2.x, t.v2.y);
    v3 = Vector2(t.v3.x, t.v3.y);
    c1 = t.c1;
    c2 = t.c2;
    c3 = t.c3;
}

void Triangle2D::calculateBarycentricCoordinates(Vector2 P, float &lambda1, float &lambda2, float &lambda3)
{
    float Areafull = determinant(v2 - v3, v1 - v3);
    lambda1 = determinant(v2 - v3, P - v3) / Areafull;
    lambda2 = determinant(P - v3, v1 - v3) / Areafull;
    lambda3 = 1 - lambda1 - lambda2;
}

Triangle3D::Triangle3D()
{
    v1 = Vector4(0, 0, 0, 1);
    v2 = Vector4(0, 0, 0, 1);
    v3 = Vector4(0, 0, 0, 1);
    c1 = White;
    c2 = White;
    c3 = White;
    shouldDraw = true;
}

Triangle3D::Triangle3D(Vector4 pV1, Vector4 pV2, Vector4 pV3, Color pC1, Color pC2, Color pC3)
{
    v1 = pV1;
    v2 = pV2;
    v3 = pV3;
    c1 = pC1;
    c2 = pC2;
    c3 = pC3;
    shouldDraw = true;
}

void Triangle3D::transform(Matrix4 matrix)
{
  //  cout << "Before v1 = " << v1.x << ", " << v1.y << ", " << v1.z << ", " << v1.w << endl;
    v1 = matrix * v1;
    v2 = matrix * v2;
    v3 = matrix * v3;
//    cout << "After v1 = " << v1.x << ", " << v1.y << ", " << v1.z << ", " << v1.w << endl;
}
