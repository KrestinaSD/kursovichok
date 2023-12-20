/**
* @file communicator.h
* @author Крестина С.Д.
* @version 1.0
* @brief Заголовочный файл для модуля communacator, отвечающий за связь с клиентом
*/

#pragma once
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <map>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
#include <fstream>
#include <random>
#include <sstream>
#include <exception>
#include <typeinfo>
#include "programmerror.h"
#include "logger.h"
#include "calculator.h"
#include "userbase.h"
#include "interface.h"

/** 
 * @brief Класс для связи с клиентом 
 * @details Методы: установка бинда,
 * установка сервера в режим ожидания соединения
 * принятие соединения
 * получение данных от клиента
 * отправка данных клиенту
 * "разговор" с клиентом
 */
class communicator
{
private:
    const char* Adress = "127.0.0.1"; ///< Сетевой адрес сервера
    struct sockaddr_in addr; ///< Структура sockaddr_in
    int sckt; ///< Основной сокет 
    std::string password; ///< Пароль клиента
    std::string SALT; ///< Соль для вычисления хэша
    std::string strHash; ///< Хэш
    
public:
	/**
 	* @brief Конструтор класса без параметров
 	*/
	communicator(){};
	
    /**
 	* @brief Функция "разговора" с клиентом.
 	* @param [in] unsigned int port, map <string,string> DataBaseP
 	* @details В этом методе происходит все взаимодействие с клиентом. Ничего не возвращает.
 	*/
    void conversation(unsigned int port,  std::map <std::string,std::string> DataBaseP); 
    /**
 	* @brief Функция генерации соли
 	* @details В этом методе происходит генерация соли. 
 	* @return SALT
 	*/
    std::string GenSALT();
     /**
 	* @brief Генерация хэша из пароля и соли.
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
    #if _UNITTEST_ != 1
    void getpass(std::string pass){
 	password = pass;
	}
    #endif
    #if _UNITTEST_ != 1
	void setSALT(const std::string& salt) {
 	   SALT = salt;
	}
	#endif
    
};
