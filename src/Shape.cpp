#include "Shape.h"

Shape::Shape(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    volume = x * y * z;
}

int Shape::getX()
{
    return x;
}

int Shape::getY()
{
    return y;
}

int Shape::getZ()
{
    return z;
}

int Shape::getVolume()
{
    return volume;
}