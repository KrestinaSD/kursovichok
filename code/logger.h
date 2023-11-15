#pragma once
#include <string>
class Logger
{
private:
    std::string path_to_logfile;
   
public:
    int writelog(std::string s);
    void set_path(std::string path_file);
    void write_error(std::string error_message) ;
    Logger(){};
    Logger(std::string s){path_to_logfile = s;};
    static std::string getCurrentDateTime(std::string s);
};



