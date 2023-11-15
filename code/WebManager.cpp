#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include "WebManager.h"
#include "ErrorTracker.h"


using namespace std;

WebManager::WebManager(unsigned int port){
    listener = socket(AF_INET, SOCK_STREAM, 0);
	if (listener<0){
		throw server_error(std::string("Socket creation error"), true);
	}
	
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(Adress);
}

int WebManager::new_bind(){
	int rc = bind(listener, (struct sockaddr *)&addr, sizeof(addr));
	if (rc<0){
		throw server_error(std::string("Socket bind error"), true);}
	return rc;
}

void WebManager::start_listening(){
int rc = listen(listener, 1);
	if (rc<0){
		throw server_error(std::string("Listening error"), true);}
}

int WebManager::accepting(){
    sockaddr_in * client_addr = new sockaddr_in;
    socklen_t len = sizeof (sockaddr_in);
	int rc = accept(listener,  (sockaddr*)(client_addr), &len);
	if (rc<0){
		throw server_error(std::string("Accepting error"), false);}
    return rc;
}

int WebManager::receiving(int sock, void*buf, int size){
	int rc = recv(sock, buf, size, 0);
	if (rc<0){
		throw server_error(std::string("Receiving error"), false);}
    return rc;
}

void WebManager::sending(int sock, void*buf, int sizeb){
	int rc = send(sock, buf, sizeb, 0);
	if (rc<0){
		throw server_error(std::string("Sending error"));}
}


