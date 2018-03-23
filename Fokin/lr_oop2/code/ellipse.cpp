#include <cmath>
#include <iomanip>
#include "ellipse.h"

#define AMOUNT_ELLIPSE_NODES 4

Ellipse::Ellipse (double newCoordinateX, double newCoordinateY, double newRadius, double newRadiusEllipse)
{
    coordinateX = newCoordinateX;
    coordinateY = newCoordinateY;
    radius = newRadius;
    radiusEllipse = newRadiusEllipse;
    angle = 0;
    color = "default white";
    updateNodes();
}

void Ellipse::rotate (double newAngle)
{
    angle = newAngle;
    updateNodes();
}

void Ellipse::scale (double ratio)
{
    radius *= ratio;
    radiusEllipse *= ratio;
    updateNodes();
}

double Ellipse::getRadiusEllipse ()
{
    return radiusEllipse;
}

string Ellipse::getType ()
{
    return type;
}

string Ellipse::type = "ellips";

void Ellipse::updateNodes()
{
    for (int i = 0; i < AMOUNT_ELLIPSE_NODES; i += 2)
    {
        array[i][0] = getCoordinateX() + getRadius() * cos(1.57 * (getAngle() / 90 + i));
        array[i][1] = getCoordinateY() + getRadius() * sin(1.57 * (getAngle() / 90 + i));
    }
    for (int i = 1; i < AMOUNT_ELLIPSE_NODES; i += 2)
    {
        array[i][0] = getCoordinateX() + getRadiusEllipse() * cos(1.57 * (getAngle() / 90 + i));
        array[i][1] = getCoordinateY() + getRadiusEllipse() * sin(1.57 * (getAngle() / 90 + i));
    }
}

ostream& operator<<(ostream& output, Ellipse &object)
{
    output << "Type: " << object.getType() << endl;
    output << "CoordinateX: " << setprecision(2) << object.getCoordinateX() << endl;
    output << "CoordinateY: " << object.getCoordinateY() << endl;
    output << "Radius1: " << object.getRadius() << endl;
    output << "Radius2: " << object.getRadiusEllipse() << endl;
    output << "Angle: " << object.getAngle() << endl;
    output << "Color: " << object.getColor() << endl;
    output << "Coordinates: " << endl;
    for (int i = 0; i < AMOUNT_ELLIPSE_NODES; ++i)
        output << object.array[i][0] << " " << object.array[i][1] << endl;

    return output;
}
