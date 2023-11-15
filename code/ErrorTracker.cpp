#include "ErrorTracker.h"
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
		throw std::invalid_argument("Wrong log File Name");
		return;}
log.close();
LogFileName = LogName;}

void ErrorTracker::write_log(std::string what, bool Critical)
{
    time_t now = time(0);
    char* dt = ctime(&now);
    tm *gmtm = localtime(&now);
    dt = asctime(gmtm);
    std::ofstream log(LogFileName, std::ios_base::app);
    if(!log.good()){
		throw std::invalid_argument("Wrong log File Name");
		return;}
    std::string err_msg = std::string(dt);
	err_msg.pop_back();
    if (Critical){
    err_msg += " "+what + " Критическая\n";}
    else {err_msg += " "+what + " Штатная\n";}
    log.write(err_msg.c_str(),err_msg.size());
    log.close();
}
