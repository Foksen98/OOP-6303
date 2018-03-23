#include <cmath>
#include <iomanip>
#include "square.h"

#define AMOUNT_SQUARE_NODES 4

Square::Square (double newCoordinateX, double newCoordinateY, double newRadius)
{
    coordinateX = newCoordinateX;
    coordinateY = newCoordinateY;
    radius = newRadius;
    angle = 45;
    color = "default white";
    updateNodes();
}

void Square::rotate (double newAngle)
{
    angle = newAngle;
    updateNodes();
}

void Square::scale (double ratio)
{
    radius *= ratio;
    updateNodes();
}

string Square::getType ()
{
    return type;
}

string Square::type = "square";

void Square::updateNodes()
{
    for (int i = 0; i < AMOUNT_SQUARE_NODES; ++i)
    {
        array[i][0] = getCoordinateX() + getRadius() * cos(1.57 * (getAngle() / 90 + i));
        array[i][1] = getCoordinateY() + getRadius() * sin(1.57 * (getAngle() / 90 + i));
    }
}

ostream& operator<<(ostream& output, Square &object)
{
    output << "Type: " << object.getType() << endl;
    output << "CoordinateX: " << setprecision(2) << object.getCoordinateX() << endl;
    output << "CoordinateY: " << object.getCoordinateY() << endl;
    output << "Radius: " << object.getRadius() << endl;
    output << "Angle: " << object.getAngle() << endl;
    output << "Color: " << object.getColor() << endl;
    output << "Coordinates: " << endl;
    for (int i = 0; i < AMOUNT_SQUARE_NODES; ++i)
        output << object.array[i][0] << " " << object.array[i][1] << endl;

    return output;
}
