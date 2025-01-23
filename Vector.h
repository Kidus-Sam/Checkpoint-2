#ifndef Vector2_H
#define Vector2_H


struct Vector4
{
    public:
        float x;
        float y;
        float z;
        float w;
        Vector4();
        Vector4(float px, float py,float pz,float pw);
        Vector4 operator*(const float& scalar);
        Vector4 operator+(const Vector4& vector);
        Vector4 operator-(const Vector4& vector);
        float magnitude();
        float dot(Vector4 vector);
        Vector4 normalize();  
        Vector4 cross(Vector4 vector);
    private:
};



struct Vector2
{
    public:
        float x;
        float y;
        Vector2();
        Vector2(float px, float py);
        Vector2 operator*(const float& scalar);
        Vector2 operator+(const Vector2& vector);
        Vector2 operator-(const Vector2& vector);
        float magnitude();
        float dot(Vector2 vector);
        Vector2 normalize();
        Vector2 perpendicular();
    private:
};

float determinant(Vector2 a, Vector2 b);


#endif