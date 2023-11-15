#pragma once

#include <exception>
#include <ctime>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iostream>



class ErrorTracker
{
private:
    std::string LogFileName; ///< Путь к файлу с логом ошибок
public:
	ErrorTracker(){}; ///< Конструктор без параметров
    void setLogName(std::string LogName); ///<Функция, устанавливающая путь к файлу с логом ошибок



    void write_log(std::string what, bool Critical);
	~ErrorTracker(){}; ///< Деструктор
};



class server_error: public std::invalid_argument {
private:
bool State = false; ///<Статус критичности ошибки
public:


explicit server_error (const std::string& what_arg, bool critical = false):
std::invalid_argument(what_arg) {State = critical;}



explicit server_error (const char* what_arg,  bool critical = false):
std::invalid_argument(what_arg) {State = critical;}
bool getState() const {return State;} ///<Возвращает статус критичности ошибки
};
