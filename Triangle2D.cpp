#include "Triangle2D.h"
#include "Vector2.h"
#include "Color.h"
#include <iostream>
using namespace std;

Triangle2D::Triangle2D(){
    v1= Vector2(0,0);
    v2= Vector2(0,0);
    v3= Vector2(0,0);
    c1=Black;
    c2=Black;
    c3=Black;
}

Triangle2D::Triangle2D(Vector2 v1p, Vector2 v2p, Vector2 v3p, Color c1p, Color c2p, Color c3p){
    v1=v1p;
    v2=v2p;
    v3=v3p;
    c1=c1p;
    c2=c2p;
    c3=c3p;
}

void Triangle2D::calculateBarycentricCoordinates(Vector2 P, float& lambda1,float& lambda2, float& lambda3){
    float Areafull=determinant(v2-v3, v1-v3);
    lambda1=determinant(v2-v3, P-v3)/Areafull;
    lambda2=determinant(P-v3, v1-v3)/Areafull;
    lambda3=1-lambda1-lambda2;
}
