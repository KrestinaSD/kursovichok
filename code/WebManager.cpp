#include "WebManager.h"
#include "programmerror.h"
#include "logger.h"


using namespace std;

struct sockaddr_in addr;
int Port;
Logger logi;


WebManager::WebManager(unsigned int port){
// Создание сокета
    sckt = socket(AF_INET, SOCK_STREAM, 0);
    if(sckt < 0) {
        throw server_error(std::string("Socket creation error"), true);
    }
    logi.writelog("Socket creation OK");
     // Задание параметров адреса сервера
    addr.sin_family = AF_INET; // Семейство адресов
    addr.sin_port = htons(port); // Порт, на котором будет работать сервер
    addr.sin_addr.s_addr = inet_addr(Adress); // адрес
}


void WebManager::bindSocket() {
    // Привязка сокета к адресу
    int rc = bind(sckt, (struct sockaddr *)&addr, sizeof(addr));
    if(rc < 0) {
        throw server_error(std::string("Socket bind error"), true);
    }
    logi.writelog("Socket bind OK");
}

void WebManager::listenSocket() {
    // Начало прослушивания входящих соединений
    int l = listen(sckt, 1);
    if (l < 0) {
    	throw server_error(std::string("Listening error"), true);
    }
    logi.writelog("Listening  OK");
}

int WebManager::accepting() {
    // Принятие входящего соединения
    sockaddr_in * client_addr = new sockaddr_in;
    socklen_t len = sizeof (sockaddr_in);
    // Принятие входящего соединения на сокете sock
    int scktr = accept(sckt, (sockaddr*)(client_addr), &len);
    if (scktr < 0){
        // Выброс исключения server_error
        throw server_error(std::string("Accepting error"), false);
    }
    logi.writelog("Accepting OK");
    return scktr;
}

// Функция receiving, которая принимает данные из сокета
int WebManager::receiving(int sock, void*buf, int size){
    // Прием данных из сокета sock в буфер buf размера size
    int rc = recv(sock, buf, size, 0);
    if (rc < 0){
        // Выброс исключения server_error
        throw server_error(std::string("Receiving error"), false);
    }
    logi.writelog("Receiving OK");
    // Возвращение количества принятых байт
    return rc;
}

// Функция sending, которая отправляет данные через сокет
void WebManager::sending(int sock, void*buf, int sizeb){
    // Отправка данных из буфера buf размера sizeb через сокет sock
    int rc = send(sock, buf, sizeb, 0);
    if (rc < 0){
        // Выброс исключения server_error
        throw server_error(std::string("Sending error"));
    }
    logi.writelog("Sending OK");
}


