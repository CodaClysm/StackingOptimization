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

string Shape::toString()
{
    string s = "";
    s += "x:" + to_string(x) + " y:" + to_string(y) + " z:" + to_string(z);
    return s;
}


/*
* Function: getUniqueOrientations
* Parameters: 
* Description: rotates the shape to get all unique orientations. Since all shapes
*   are rectangles, there are 1-4 possible unique orientations for each shape. 
*/
vector<Shape> Shape::getUniqueOrientations()
{
    vector<Shape> returnVector;
    Shape s(x,y,z);
    returnVector.push_back(s);
    if(x != z)
    {
        Shape s(z,y,x);
        returnVector.push_back(s);
    }
    if(x != y)
    {
        Shape s(y,x,z);
        returnVector.push_back(s);
    }
    if(y != z)
    {
        Shape s(x,z,y);
        returnVector.push_back(s);
    }
    return returnVector;
}