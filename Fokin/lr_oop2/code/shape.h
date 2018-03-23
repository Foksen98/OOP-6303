#ifndef SHAPE_H
#define SHAPE_H

#include <string>

using namespace std;

class Shape
{
public:
    // поворот на заданный угол (в градусах)
    virtual void rotate (double newAngle) = 0;
    // масштабирование
    virtual void scale (double ratio) = 0;
    // перемещение в новые координаты
    void move (double newCoordinateX, double newCoordinateY);
    // установить цвет
    void setColor (string colorString);
    // получить цвет
    string getColor ();

    double getCoordinateX ();
    double getCoordinateY ();
    double getRadius ();
    double getAngle ();

protected:
    double coordinateX;
    double coordinateY;
    double radius;
    double angle;
    string color;

    // обновление координат вершин
    virtual void updateNodes () = 0;
};

#endif // SHAPE_H
