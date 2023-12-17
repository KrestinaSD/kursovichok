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
	  
	communicator(){};
	
    /**
 	* @brief Функция "разговора" с клиентом.
 	* @details В этом методе происходит все взаимодействие с клиентом. Ничего не возвращает.
 	*/
    void conversation(unsigned int port,  std::map <std::string,std::string> DataBaseP); 
    
    std::string GenSALT();
    std::string GenHash(const std::string& password);
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
