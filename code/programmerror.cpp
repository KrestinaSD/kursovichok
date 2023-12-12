#include "programmerror.h"
#include "logger.h"
#include <exception>
#include <ctime>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <iostream>

void ErrorTracker::setLogName(std::string LogName){
	std::ofstream log(LogName, std::ios_base::app);
	if(!log.good()){
			throw std::invalid_argument("Wrong log File Name");}
	log.close();
	LogFileName = LogName;
}

std::string ErrorTracker::getDateTime() {
    time_t now = time(0);
    struct tm  tstruct;
    char  buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%d.%m.%Y %X", &tstruct);
    return std::string(buf);
} 

void ErrorTracker::write_log(std::string what, bool Critical)
{
	std::string data = getDateTime();
    
    std::ofstream log(LogFileName, std::ios_base::app);
    if(!log.good()){
		throw std::invalid_argument("Wrong log File Name");
	}
    std::string err_msg = std::string(data);
	err_msg.pop_back();
    if (Critical){
    err_msg += " "+what + " Критическая\n";}
    else {err_msg += " "+what + " Штатная\n";}
    log.write(err_msg.c_str(),err_msg.size());
    log.close();
}
