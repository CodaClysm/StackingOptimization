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
    static void error(string msg);
    static void warn(string msg);
    static void info(string msg);
    static void close();

};
