#include "logger.h"
#include "interface.h"
#include <chrono>
#include <string>
#include <time.h>
#include <fstream>
using namespace std;

void set_path(std::string path_file) {
        path_to_logfile = path_file;
    }
    
std::string Logger::getCurrentDateTime(std::string s) {
    time_t now = time(0);
    struct tm  tstruct;
    char  buf[80];
    tstruct = *localtime(&now);
    if(s=="now")
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    else if(s=="date")
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    return std::string(buf);
}

int Logger::writelog(std::string s) {
    std::ofstream filelog;
    filelog.open(path_to_logfile, std::ios_base::out | std::ios_base::app);
    if(filelog.is_open()) {
        std::string time = getCurrentDateTime("now");
        filelog << time << ' ' << s << std::endl;
        return 0;
    } else {
        return 1;
    }
}


void Logger::write_error(std::string error_message) {
    std::string log_message = "Error: " + error_message;
    writelog(log_message);
}
