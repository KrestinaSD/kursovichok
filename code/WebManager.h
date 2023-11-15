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


class WebManager
{
private:
    unsigned int Port; //Порт, на котором работает сервер
    const char* Adress = "127.0.0.1"; //Сетевой адрес сервера
    struct sockaddr_in addr; //Структура sockaddr_in
    int listener; //Основной сокет 
public:
    WebManager(unsigned int port);

    void start_listening();

    int new_bind();

    int accepting();

    int receiving(int sock, void*buf, int size);

    void sending(int sock, void*buf, int sizeb);
};
