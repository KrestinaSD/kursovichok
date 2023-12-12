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
public:
	/**
 	* @brief Конструтор класса без параметров
 	* @details В конструкторе идет проверка на существование файла с базой клиентов
 	*/
	DB() {
        if (!CheckFiles()) {
            throw server_error(std::string("Неверное имя файла базы данных"), true);
        }
    }
	std::map <std::string,std::string> DataBaseP; ///< Словарь с парами идентификатор:пароль
	/**
 	* @brief Конструтор класса
 	* @param [in] DBName - путь до файла с данными клиентов
 	* @details В этом конструкторе происходит открытие файла, получение данных, заполнение словаря, закрытие словаря
 	*/
    DB(std::string DBName);
	/**
 	* @brief Функция проверки наличия ID  в файле базы клиентов
 	* @details В этом методе происходит проверка на наличие ID в файле базы клиентов
 	* @return True or False
 	*/
    bool IDcheck(std::string login);
    /**
 	* @brief Функция проверки файлов
 	* @details В этом методе происходит проверка на "правильность" пути до файла с базой клиентов
 	* @return True or False
 	*/
    bool CheckFiles();
};
