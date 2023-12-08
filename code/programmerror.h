/**
* @file programmerror.h
* @author Крестина С.Д.
* @version 1.0
* @brief Заголовочный файл для модуля ErrorTracker, отвечающий за ошибки и их запись в лог
*/
#pragma once

#include <exception>
#include <ctime>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iostream>


/** 
 * @brief Класс для получения ошибок и запись их в лог
 * @details Методы: разбор ПКС
 * проверка файлов
 * получение пути до файла с логами
 */
 
class ErrorTracker
{
private:
    std::string LogFileName; ///< Путь к файлу с журналом работы
public:
	/**
 	* @brief Конструтор класса без параметров
 	*/
	ErrorTracker(){}; 
	/**
 	* @brief Функция получения пути до журнала работы
 	* @param [in] string LogName - путь до файла логов
 	* @details В этом методе устанавливается путь до файла с журналом работы
 	* @return LogFileName
 	*/
    void setLogName(std::string LogName); ///<Функция, устанавливающая путь к файлу с логом ошибок
    /**
 	* @brief Функция получения времени
 	* @details В этом методе происходит получение времени и вывод его в нужном формате
 	* @return string(buf)
 	*/
	static std::string getDateTime();
	/**
 	* @brief Функция записи лога
 	* @param [in] string what - причина,
 	* @param [in] bool Critical - критичность
 	* @details В этом методе происходит открытие файла, запись, закрытие файла. Ничего не возвращает.
 	*/
    void write_log(std::string what, bool Critical);
    /**
 	* @brief Деструктор класса
 	*/
	~ErrorTracker(){}; 
};

/** @brief Класс вызова исключений 
**  @class server_error
 */

class server_error: public std::invalid_argument {
private:
bool State = false; ///<Статус критичности ошибки
public:
/**
 @brief Конструктор ошибок с строкой в качестве параметра
 @param [in] what_arg, тип ошибки, const std::string.
 @param [in] critical, критическа ошибка - true, штатная - false, bool
*/
explicit server_error (const std::string& what_arg, bool critical = false):
	std::invalid_argument(what_arg) {State = critical;}
/**
 @brief Конструктор ошибок с си-строкой в качестве параметра
 @param [in] what_arg, тип ошибки, const char*.
 @param [in] critical, критическаZ ошибка - true, штатная - false, bool
*/
explicit server_error (const char* what_arg,  bool critical = false):
	std::invalid_argument(what_arg) {State = critical;}
bool getState() const {return State;} ///<Возвращает статус критичности ошибки
};
