#include <cmath>
#include <iomanip>
#include "hexagon.h"

#define AMOUNT_HEXAGON_NODES 6

Hexagon::Hexagon (double newCoordinateX, double newCoordinateY, double newRadius)
{
    coordinateX = newCoordinateX;
    coordinateY = newCoordinateY;
    radius = newRadius;
    angle = 0;
    color = "default white";
    updateNodes();
}

void Hexagon::rotate (double newAngle)
{
    angle = newAngle;
    updateNodes();
}

void Hexagon::scale (double ratio)
{
    radius *= ratio;
    updateNodes();
}

string Hexagon::getType ()
{
    return type;
}

string Hexagon::type = "hexagon";

void Hexagon::updateNodes()
{
    for (int i = 0; i < AMOUNT_HEXAGON_NODES; ++i)
    {
        array[i][0] = getCoordinateX() + getRadius() * cos(1.57 * (getAngle() / 90 + i / 1.5));
        array[i][1] = getCoordinateY() + getRadius() * sin(1.57 * (getAngle() / 90 + i / 1.5));
    }
}

ostream& operator<<(ostream& output, Hexagon &object)
{
    output << "Type: " << object.getType() << endl;
    output << "CoordinateX: " << setprecision(2) << object.getCoordinateX() << endl;
    output << "CoordinateY: " << object.getCoordinateY() << endl;
    output << "Radius: " << object.getRadius() << endl;
    output << "Angle: " << object.getAngle() << endl;
    output << "Color: " << object.getColor() << endl;
    output << "Coordinates: " << endl;
    for (int i = 0; i < AMOUNT_HEXAGON_NODES; ++i)
        output << object.array[i][0] << " " << object.array[i][1] << endl;

    return output;
}
