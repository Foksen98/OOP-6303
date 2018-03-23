#include <iostream>
#include <string>
#include "shape.h"

class Ellipse : public Shape
{
friend ostream &operator<<(ostream &output, Ellipse &object);
public:
    Ellipse (double newCoordinateX, double newCoordinateY, double newRadius, double newRadiusEllipse);
    void rotate (double newAngle);
    void scale (double ratio);
    string getType ();
    double getRadiusEllipse();

private:
    double radiusEllipse;
    double array[4][2];
    static string type;
    void updateNodes();
};
