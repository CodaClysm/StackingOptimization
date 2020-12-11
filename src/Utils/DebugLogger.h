#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

enum Level {
    ERROR = 1,
    WARN = 2,
    INFO = 3
};

class DebugLogger
{
private:
    static Level level;
    static ofstream outStream;
public:
    static void start(Level level);
    static void error(string msg);
    static void warn(string msg);
    static void info(string msg);
    static void close();

};
