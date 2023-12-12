/**
* @file logger.h
* @author Крестина С.Д.
* @version 1.0
* @brief Заголовочный файл для модуля logger, отвечающий за запись логов
*/

#pragma once
#include <string>
#include <chrono>
#include <string>
#include <time.h>
#include <fstream>
#include "interface.h"
#include "programmerror.h"

/** 
 * @brief Класс для формирования и записи логов
 * @details Методы: запись лога,
 * получение пути до файла журнала работы
 * получение даты и времени
 */
class Logger
{
private:
    std::string path_to_logfile; ///< путь до файла с журналом работы
public:
	/**
 	* @brief Функция записи лога
 	* @details В этом методе происходит открытие файла, запись, закрытие файла
 	* @return 1 or 0
 	*/
    int writelog(std::string s);
    /**
 	* @brief Функция получение пути до файла журнала работы
 	* @details В этом методе происходит получение пути до файла журнала работы. Ничего не возращает. 	
 	*/
    void set_path(std::string path_file);
    /**
 	* @brief Конструтор класса без параметров
 	*/
    Logger(){};
    /**
 	* @brief Конструтор класса
 	* @param [in] s - путь до файла с логами
 	*/
    Logger(std::string s){path_to_logfile = s;};
    /**
 	* @brief Функция получения времени
 	* @details В этом методе происходит получение времени и вывод его в нужном формате
 	* @return string(buf)
 	*/
    static std::string getDateTime();
    
};



