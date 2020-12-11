#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

class DataLogger
{
private:
    static ofstream outStream;
public:
    static void start();
    static void log(string msg);
    static void close();

};
