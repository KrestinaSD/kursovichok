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
#include "programmerror.h"
#include "logger.h"
#include "auth.h"
#include "calculator.h"
#include "userbase.h"

class WebManager
{
private:
    unsigned int Port; //Порт, на котором работает сервер
    const char* Adress = "127.0.0.1"; //Сетевой адрес сервера
    struct sockaddr_in addr; //Структура sockaddr_in
    int sckt; //Основной сокет 
public:
	WebManager(unsigned int port); // Конструктор класса в нем создание сокета
	void bindSocket();// бинды 
	void listenSocket(); // ожидание
	int accepting(); // принятие соединения
    int receiving(int sock, void*buf, int size);//принимает данные из сокета
    void sending(int sock, void*buf, int sizeb);//отправляет данные через сокет
    void conversation(unsigned int port, std::string LogName, DB new_db, int sock); // "разговор" с клиентом
};
