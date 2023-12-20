/**
* @file userbase.h
* @author Крестина С.Д.
* @version 1.0
* @brief Заголовочный файл для модуля userbase, отвечающий за получение данных из базы клиентов
*/
#pragma once

#include <map>
#include <string>
#include <fstream>
#include <exception>
#include <typeinfo>
#include <iostream>
#include "programmerror.h"
/** 
 * @brief Класс для получения данных из файла базы клиентов
 * @details Методы: проверка ID
 */

class DB
{
private:
    char sep = ':'; ///<Разделитель идентификатора и пароля в базе данных
    std::string path_to_userbase; ///< Путь до файла с журналом работы
    std::map <std::string,std::string> DataBaseP; ///< Словарь с парами идентификатор:пароль
public:
	
	/**
 	* @brief Конструтор класса
 	* @param [in] DBName - путь до файла с данными клиентов
 	* @details В этом конструкторе происходит открытие файла, получение данных, заполнение словаря, закрытие словаря
 	*/
    DB(std::string DBName);
	/**
     * @brief Метод для получения данных из словаря
     * @return DataBaseP Словарь с парами идентификатор:пароль
     */
     std::map<std::string,std::string> get_data()
    {
        return DataBaseP;
    }
};
