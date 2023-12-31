/**
* @file programmerror.h
* @author Крестина С.Д.
* @version 1.0
* @brief Заголовочный файл для модуля server_error, отвечающий за ошибки
*/
#pragma once

#include <exception>
#include <ctime>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iostream>

/** @brief Класс вызова исключений 
**  @details Класс server_error
 */

class server_error: public std::invalid_argument {
	private:
	bool State = false; ///<Статус критичности ошибки
	public:
	/**
 	* @brief Конструктор ошибок с строкой в качестве параметра
 	* @param [in] what_arg, тип ошибки,
 	* @param [in]  const std::string, critical, критическая ошибка - true, штатная - false, bool
	*/
	explicit server_error (const std::string& what_arg, bool critical = false):
		std::invalid_argument(what_arg) {State = critical;}
	/**
 	* @brief Конструктор ошибок с си-строкой в качестве параметра
 	* @param [in] what_arg, тип ошибки, 
 	* @param [in] const char*, critical, критическая ошибка - true, штатная - false, bool
	*/
	explicit server_error (const char* what_arg,  bool critical = false):
		std::invalid_argument(what_arg) {State = critical;}
	std::string getState() const {return State ? "Критическая" : "Штатная";} ///<Возвращает статус критичности ошибки
};
