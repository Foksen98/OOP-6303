#include <iostream>
#include <string>
#include "shape.h"

class Hexagon : public Shape
{
friend ostream &operator<<(ostream &output, Hexagon &object);
public:
    Hexagon (double newCoordinateX, double newCoordinateY, double newRadius);
    void rotate (double newAngle);
    void scale (double ratio);
    string getType ();

private:
    double array[6][2];
    static string type;

    void updateNodes();
};
