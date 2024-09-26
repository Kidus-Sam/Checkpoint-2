#ifndef Vector2_H
#define Vector2_H



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