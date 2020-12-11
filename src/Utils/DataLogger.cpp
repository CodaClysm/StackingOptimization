#include "DataLogger.h"
#include <iostream>
#include <filesystem>
ofstream DataLogger::outStream = ofstream();

/*
* Function: start
* Parameters: 
*   Level level: The level the logger should be started at. 
* Description: opens a log file to write to. Level determines how much to be logged
    Info level logs all info logs as well as warn and error. 
    warn level logs all warning and errors
    error level logs all errors
*/
void DataLogger::start()
{
    if(!outStream.is_open())
    {
        string filename = "logs/DataLog-";
        time_t currentTime = time(0);
        filename += ctime(&currentTime);
        filename.replace(filename.length()-1, 1, "");
        filename += ".txt";

        //clean invalid characters
        int pos = filename.find_first_of(":");
        while(pos != string::npos)
        {
            filename[pos] = '_';
            pos = filename.find_first_of(":");
        }
        outStream.open(filename);
    }
}


/*
* Function: error
* Parameters: 
*   string msg: msg to write to log file 
* Description: 
*    writes a message to log file with prefix ERROR
*/
void DataLogger::error(string msg)
{
    if(outStream.is_open())
    {
        string message = "ERROR: ";
        message += msg;
        outStream << message;
        outStream.flush();
    }
}


/*
* Function: warn
* Parameters: 
*   string msg: msg to write to log file 
* Description: 
*    writes a message to log file with prefix WARN
*/
void DataLogger::warn(string msg)
{
    if(outStream.is_open())
    {
        string message = "WARN: ";
        message += msg;
        outStream << message;
        outStream.flush();
    }
}


/*
* Function: info
* Parameters: 
*   string msg: msg to write to log file 
* Description: 
*    writes a message to log file with prefix INFO
*/
void DataLogger::info(string msg)
{
    if(outStream.is_open())
    {
        string message = "INFO: ";
        message += msg;
        outStream << message;
        outStream.flush();
    }
}


/*
* Function: close
* Parameters: 
* Description: 
*   closes the outStream at the end of execution.
*/

void DataLogger::close()
{
    if(outStream.is_open())
    {
        outStream.flush();
        outStream.close();
    }
}

