#include "Vector.h"
#include <cmath>
using namespace std;

Vector2::Vector2()
{
    x = 0;
    y = 0;
};

Vector2::Vector2(float px, float py)
{
    x = px;
    y = py;
};

float Vector2::magnitude()
{
    return sqrt(x * x + y * y);
};

float Vector2::dot(Vector2 vector)
{
    return (x * vector.x + y * vector.y);
}

Vector2 Vector2::normalize()
{
    float divisible = 1 / magnitude();
    Vector2 newvect = (*this) * divisible;
    return newvect;
}

Vector2 Vector2::perpendicular()
{
    return Vector2(-y, x);
}

Vector2 Vector2::operator*(const float &scalar)
{
    Vector2 newVector;
    newVector.x = x * scalar;
    newVector.y = y * scalar;
    return newVector;
}
Vector2 Vector2::operator+(const Vector2 &vector)
{
    Vector2 newVect;
    newVect.x = x + vector.x;
    newVect.y = y + vector.y;
    return newVect;
}
Vector2 Vector2::operator-(const Vector2 &vector)
{
    Vector2 newVect;
    newVect.x = x - vector.x;
    newVect.y = y - vector.y;
    return newVect;
}

float determinant(Vector2 a, Vector2 b)
{
    return (b.x * a.y - a.x * b.y);
}

Vector4::Vector4()
{
    x = 0;
    y = 0;
    z = 0;
    w = 0;
};

Vector4::Vector4(float px, float py, float pz, float pw)
{
    x = px;
    y = py;
    z = pz;
    w = pw;
};

float Vector4::magnitude()
{
    return sqrt(x * x + y * y + z * z);
};

float Vector4::dot(Vector4 vector)
{
    return (x * vector.x + y * vector.y + z * vector.z + w * vector.w);
}

Vector4 Vector4::normalize()
{
    float divisible = 1 / magnitude();
    Vector4 newvect = (*this) * divisible;
    return newvect;
}

Vector4 Vector4::operator*(const float &scalar)
{
    Vector4 newVector;
    newVector.x = x * scalar;
    newVector.y = y * scalar;
    newVector.z = z * scalar;
    newVector.w = w * scalar;
    return newVector;
}
Vector4 Vector4::operator+(const Vector4 &vector)
{
    Vector4 newVect;
    newVect.x = x + vector.x;
    newVect.y = y + vector.y;
    newVect.z = z + vector.z;
    newVect.w = w + vector.w;
    return newVect;
}
Vector4 Vector4::operator-(const Vector4 &vector)
{
    Vector4 newVect;
    newVect.x = x - vector.x;
    newVect.y = y - vector.y;
    newVect.z = z - vector.z;
    newVect.w = w - vector.w;
    return newVect;
}

Vector4 Vector4::cross(Vector4 vector)
{
    Vector4 newVector = Vector4();
    newVector.x = (this->y * vector.z) - (this->z * vector.y);
    newVector.y = (this->z * vector.x) - (this->x * vector.z);
    newVector.z = (this->x * vector.y) - (this->y * vector.x);
    newVector.w = 0;
    return newVector;
}
