#pragma once
#include <string>
#include <chrono>
#include <string>
#include <time.h>
#include <fstream>
class Logger
{
private:
    std::string path_to_logfile;
public:
    int writelog(std::string s);
    void set_path(std::string path_file);
    void write_error(std::string message) ;
    Logger(){};
    Logger(std::string s){path_to_logfile = s;};
    static std::string getDateTime();
};



