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
#include "programmerror.h"
#include "logger.h"
#include "auth.h"
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
    unsigned int Port; ///< Порт, на котором работает сервер
    const char* Adress = "127.0.0.1"; ///< Сетевой адрес сервера
    struct sockaddr_in addr; ///< Структура sockaddr_in
    int sckt; ///< Основной сокет 
    std::string password; ///< Пароль клиента
    std::string SALT; ///< Соль для вычисления хэша
    std::string strHash; ///< Хэш
    
public:
	char ERRmsg[3] = {'E', 'R','R'}; ///< Сообщение, отсылаемое клиенту при ошибке его обработки
    char OKmsg[2] = {'O', 'K'}; ///< Сообщение, отсылаемое клиенту при успешной авторизации
	/**
 	* @brief Конструтор класса
 	* @param [in] port Порт, на котором работает сервер
 	* @details В этом конструкторе происходит создание сокета, 
 	* установка бинда по созданному сокету,
 	* установка сервера в режим ожидания соединений.
 	*/
	communicator(unsigned int port);  
	/**
 	* @brief Функция принятия соединения
 	* @details В этом методе происходит принятие соединения от клиента. 
 	* @return scktr
 	*/
	int accepting();
	/**
 	* @brief Функция получения данных от клиента
 	* @details В этом методе происходит получение данных от клиента. 
 	* @return rc
 	*/
    int receiving(int sock, void*buf, int size);
    /**
 	* @brief Функция отправки сообщения клиенту
 	* @details В этом методе просиходит отправка сообщений клиенту. Ничего не возвращает.
 	*/
    void sending(int sock, void*buf, int sizeb);
    /**
 	* @brief Функция "разговора" с клиентом.
 	* @details В этом методе происходит все взаимодействие с клиентом. Ничего не возвращает.
 	*/
    void conversation(unsigned int port, std::string LogName, DB new_db, int sock); 
    
    std::string GenSALT();
    std::string GenHash(const std::string& password);
    bool CompareHashes(std::string ClientHash);
    void getpass(std::string pass);
    
};
