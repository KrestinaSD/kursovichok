/**
* @file auth.h
* @author Крестина С.Д.
* @version 1.0
* @brief Заголовочный файл для модуля auth, отвечающий за аутентификацию
*/
#pragma once
#include <map>
#include <string>
#include <iostream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
#include <fstream>
#include <random>
#include <sstream>
#include <map>
#include <exception>
#include <typeinfo>
#include <string>
#include "programmerror.h"

/** 
 * @brief Класс для аутентификации клиента на сервере
 * @details Методы для генерации SALT и генерирует HASH
 */
 
class Auth
{
private:
    std::string SALT; ///< Соль для вычисления хэша
    std::string password; ///< Пароль клиента
    std::string strHash; ///< Хэш 
public:
    char ERRmsg[3] = {'E', 'R','R'}; ///< Сообщение, отсылаемое клиенту при ошибке его обработки
    char OKmsg[2] = {'O', 'K'}; ///< Сообщение, отсылаемое клиенту при успешной авторизации
    /**
 	* @brief Конструтор класса
 	* @param [in] wskey Пароль
 	*/
    Auth(std::string pass);
    /**
 	* @brief Функция генерации SALT
 	* @return Случайное число SALT
 	*/
    std::string GenSALT();
     /**
 	* @brief Функция создания хеша на стороне сервера и сравнения хешей. Алгоритм md5.
 	* @param [in] ClientHash Строка с клиентским хэшем для сравнения с хэшем на сервере
 	* @return True or False
 	*/
    bool CompareHashes(std::string ClientHash);
};
