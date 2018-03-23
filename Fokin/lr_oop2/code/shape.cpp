#include "shape.h"

void Shape::move (double newCoordinateX, double newCoordinateY)
{
    coordinateX = newCoordinateX;
    coordinateY = newCoordinateY;
    updateNodes();
}

void Shape::setColor (string colorString)
{
    color = colorString;
}

string Shape::getColor ()
{
    return color;
}

double Shape::getCoordinateX ()
{
    return coordinateX;
}

double Shape::getCoordinateY ()
{
    return coordinateY;
}

double Shape::getRadius ()
{
    return radius;
}

double Shape::getAngle ()
{
    return angle;
}
