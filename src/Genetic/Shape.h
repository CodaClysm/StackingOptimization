#pragma once
#include <vector>
using namespace std;
class Shape
{
private:
    int x;
    int y;
    int z;
    int volume;
public:
    Shape(int x, int y, int z);
    int getX();
    int getY();
    int getZ();
    int getVolume();
    vector<Shape> getUniqueOrientations();
};

