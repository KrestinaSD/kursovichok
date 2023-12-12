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
 	* @brief Генерация хэша из пароля и соли.*
 	* @details Данный метод использует библиотеку Crypto++ для генерации хэша MD5 из пароля и соли.
 	* Затем хэш преобразуется в шестнадцатеричную строку.
 	* @param [in] password Пароль для хэширования.
 	* @return Сгенерированный хэш в шестнадцатеричной строке.
 	*/
    std::string GenHash(const std::string& password);
     /**
	* @brief Сравнение хэшей клиента и сервера.
 	* @details Данный метод сравнивает хэш, полученный от клиента, с хэшем, сгенерированным на сервере.
 	* Если хэши не совпадают, то генерируется исключение server_error с сообщением "Invalid Hash".
 	* Затем выводится на экран хэш клиента и сервера.*
 	* @param [in] ClientHash Хэш, полученный от клиента.
 	* @return true, если хэши совпадают, иначе false.
 	* @throw server_error, если хэши не совпадают.
 	*/
    bool CompareHashes(std::string ClientHash);
    /**
 	* @brief Метод для установки соли
  	* @details Этот метод позволяет установить значение соли. Создан для модульных тестов.
 	* @param salt Новое значение соли
 	*/
	void setSALT(const std::string& salt) {
 	   SALT = salt;
	}
};
