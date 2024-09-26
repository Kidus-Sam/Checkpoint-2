#include "Vector2.h"
#include <cmath>
using namespace std;


Vector2::Vector2(){
    x=0;
    y=0;
};

Vector2::Vector2(float px, float py){
    x=px;
    y=py;
};


float Vector2::magnitude(){
    return sqrt(x*x + y*y);
};

float Vector2::dot(Vector2 vector){
    return (x*vector.x+y*vector.y);
}

Vector2 Vector2::normalize(){
    float divisible= 1/magnitude();
    Vector2 newvect=(*this) * divisible;
    return newvect;
}

Vector2 Vector2::perpendicular(){
    return Vector2(-y,x);
}


Vector2 Vector2::operator*(const float& scalar){
    Vector2 newVector;
    newVector.x=x*scalar;
    newVector.y=y*scalar;
    return newVector;
}
Vector2 Vector2::operator+(const Vector2& vector){
    Vector2 newVect;
    newVect.x=x+vector.x;
    newVect.y= y+vector.y;
    return newVect;
}
Vector2 Vector2::operator-(const Vector2& vector){
    Vector2 newVect;
    newVect.x=x-vector.x;
    newVect.y=y-vector.y;
    return newVect;
}

float determinant(Vector2 a, Vector2 b){
    return (b.x*a.y - a.x*b.y);
}