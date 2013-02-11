#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
public:
    Vector2(double x = 0.0, double y = 0.0);
    Vector2 operator +(Vector2 &v2);

    Vector2 operator -();

    Vector2 operator -(Vector2 &v2);

    double operator *(Vector2 &v2);

    double getX();
    void setX(double x);
    double getY();
    void setY(double y);

    double norm();

    static double angleBetween(Vector2 &v1, Vector2 &v2);

    static Vector2 unitX();
    static Vector2 unitY();
private:
    double x;
    double y;

};


#endif // VECTOR2_H
