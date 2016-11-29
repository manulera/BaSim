#include <cmath>

class Vector2{
public:
    float XX,YY;
    Vector2(){}
    Vector2(const float x, const float y): XX(x), YY(y){}
    ~Vector2() {}
   //Vector2(Vector2 &a): XX(a.XX), YY(a.YY){}
    float const normSqr()
    {
        return XX*XX + YY*YY;
    }
    float const norm()
    {
        return sqrtf(XX*XX+YY*YY);
    }
    float distSqr(Vector2 const &a)
    {
        return (a.XX-XX)*(a.XX-XX) + (a.YY-YY)*(a.YY-YY);
    }
    float dist(Vector2 const &a)
    {
        return sqrt((a.XX-XX)*(a.XX-XX) + (a.YY-YY)*(a.YY-YY));
    }
    void normalize(const float n = 1.0) // I guess this is a default value =1, but can be changed if the argument given is different
    {
        float s = n / norm();
        XX *= s;
        YY *= s;
    }
    float const getAngle()
    {
        return atan2(YY,XX);
    }
    void const fromAngle(float ang)
    {
        XX = cos(ang);
        YY = sin(ang);
    }
    friend const Vector2 operator +(Vector2 const &a, Vector2 const &b)
    {
        return Vector2( a.XX+b.XX ,a.YY+b.YY );
    }
    friend const Vector2 operator -(Vector2 const &a, Vector2 const &b)
    {
        return Vector2(a.XX-b.XX ,a.YY-b.YY);
    }
    friend const Vector2 operator -(Vector2 const &a)
    {
        return Vector2(a.XX,a.YY);
    }
    friend float vecProd(Vector2 const &a, Vector2 const &b)
    {
        return a.XX * b.YY - a.YY * b.XX;
    }
    // Scalar product
    friend const float operator *(Vector2 const &a, Vector2 const &b)
    {
        return a.XX*b.XX + a.YY*b.YY;
    }
    friend const Vector2 operator *(Vector2 const &a, float const b)
    {
        return Vector2(a.XX*b , a.YY*b);
    }
    friend const Vector2 operator /(Vector2 const &a, float const b)
    {
        return Vector2(a.XX/b , a.YY/b);
    }
    void operator +=(Vector2 const &a)
    {
        XX += a.XX;
        YY += a.YY;
    }
    void operator -=(Vector2 const &a)
    {
        XX -= a.XX;
        YY -= a.YY;
    }
    void operator *=(const float a)
    {
        XX *= a;
        YY *= a;
    }
    void operator /=(const float a)
    {
        XX /= a;
        YY /= a;
    }
    friend bool operator ==(Vector2 const &a, Vector2 const &b)
    {
        return (a.XX==b.XX && a.YY==b.YY);
    }
    friend bool operator !=(Vector2 const &a, Vector2 const &b)
    {
        return (a.XX!=b.XX || a.YY!=b.YY);
    }
    void shuffle(const float mult = 1.0) //By default from 0 to 1, but one can indicate the value
    {
        XX = srand()*mult;
        YY = srand()*mult;
    }
};