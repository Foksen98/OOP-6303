#include <iostream>
#include <string>
#include "shape.h"

class Square : public Shape
{
friend ostream &operator<<(ostream &output, Square &object);
public:
    Square (double newCoordinateX, double newCoordinateY, double newRadius);
    void rotate (double newAngle);
    void scale (double ratio);
    string getType ();

private:
    double array[4][2];
    static string type;
    void updateNodes();
};
