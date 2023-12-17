#include "communicator.h"

using namespace std;

struct sockaddr_in addr;

interface lg; 
string logfile = lg.getLogFileName();
Logger logi(logfile);

communicator::communicator(unsigned int port){
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

    // Привязка сокета к адресу
    int rc = bind(sckt, (struct sockaddr *)&addr, sizeof(addr));
    if(rc < 0) {
        throw server_error(std::string("Socket bind error"), true);
    }
    logi.writelog("Socket bind OK");

    // Начало прослушивания входящих соединений
    int l = listen(sckt, 1);
    if (l < 0) {
    	throw server_error(std::string("Listening error"), true);
    }
}

int communicator::accepting() {
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
int communicator::receiving(int sock, void*buf, int size){
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
void communicator::sending(int sock, void*buf, int sizeb){
    // Отправка данных из буфера buf размера sizeb через сокет sock
    int rc = send(sock, buf, sizeb, 0);
    if (rc < 0){
        // Выброс исключения server_error
        throw server_error(std::string("Sending error"));
    }
    logi.writelog("Sending OK");
}

std::string communicator::GenSALT()
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<long long unsigned> distribution(0,0xFFFFFFFFFFFFFFFF);
    unsigned long long numericsalt = distribution(generator);
    std::stringstream stream;
    stream << std::hex << numericsalt;
    std::string strsalt(stream.str());
    for (long unsigned int i = 0; i <= strsalt.size(); i++) {
        strsalt[i] = toupper(strsalt[i]);
    }
    if (strsalt.size() < 16) {
        std::string strsalttemp =strsalt;
        for (unsigned i = strsalt.size(); i < 16; i++) {
            strsalttemp.insert(strsalttemp.begin(), '0');
        }
        strsalt = strsalttemp;
    }
    SALT = strsalt;
    return SALT;
}

std::string communicator::GenHash(const std::string& password) {
    std::string msg = SALT + password;
    std::string strHash;

    CryptoPP::Weak::MD5 hash;
    CryptoPP::StringSource ss(msg, true,
        new CryptoPP::HashFilter(hash,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(strHash))));
    return strHash;
}

bool communicator::CompareHashes(std::string ClientHash) {
    std::string ServerHash = GenHash(password);

    if (ClientHash != ServerHash) {
        throw server_error(std::string("Invalid Hash"));
    }
	std::cout<<"Kлиент: "<<ClientHash<<"\n"<<"Сервер: "<<ServerHash<<" "<<std::endl;
    return (ClientHash.compare(ServerHash) == 0);
}

void communicator::getpass(std::string pass){
 	password = pass;
}
 
 
 
void communicator::conversation(unsigned int port, std::string LogName, DB new_db, int sock)
{
	try{
    char buf[2048];
    int bytes_read;
    bytes_read = receiving(sock, &buf, 2048);
	std::string USRlogIn = string(buf, bytes_read);
    for (uint i = 0; i < USRlogIn.size();i++){
		if (USRlogIn[i] == '\n'){
			USRlogIn.pop_back();}
	}
   		new_db.IDcheck(USRlogIn);
   		/////////////////////////////////
        //Auth new_auth(new_db.DataBaseP[USRlogIn]);
        getpass(new_db.DataBaseP[USRlogIn]);
        ////////////////////////////////////
        //string str_salt = new_auth.GenSALT();
        std::string str_salt = GenSALT();
        /////////////////////////////////////
        char salt_buf[16];
        strcpy(salt_buf, str_salt.c_str());
        sending(sock, salt_buf, sizeof(salt_buf));
        bytes_read = receiving(sock, &buf, 2048);
        string pass = string(buf, bytes_read);
        
		for (uint i = 0; i < pass.size();i++){
			if (pass[i] == '\n'){
				pass.pop_back();
			}
		}
		
		/////////////////////////////////
        //new_auth.CompareHashes(pass);
        CompareHashes(pass);
        ////////////////////////////////////
        sending(sock, OKmsg, sizeof(OKmsg));
        uint32_t num_vectors;
        uint32_t vector_len;
        bytes_read = receiving(sock, &num_vectors, sizeof num_vectors);
            
        for(unsigned int i =0; i< num_vectors; i++) {
        	bytes_read = receiving(sock, &vector_len, sizeof vector_len);
        	double int_buf[vector_len];
        	bytes_read = receiving(sock, &int_buf, vector_len*sizeof(double));
        	std::vector<double> arr;
        	
        	for(unsigned int i = 0; i < vector_len; i++) {
                    arr.push_back(int_buf[i]);
            }

            Average res;
            double result = res.average(arr);
            sending(sock, &result, sizeof(double));
       }
       std::cout<<"Calculations were successful\n";
       logi.writelog("Calculating OK");
       close(sock);
       std::cout<<"Done\n";
       logi.writelog("Client disconnected");
       
    } catch (const server_error & e) {
		ErrorTracker new_ErrTr;
		new_ErrTr.setLogName(LogName);
		new_ErrTr.write_log(e.what(), e.getState());
		if (e.getState()){
			exit(1);
		}
		communicator ERR_send_manager(port);
        ERR_send_manager.sending(sock, Auth("NO").ERRmsg, sizeof(Auth("NO").ERRmsg));
        close(sock);
    }
}



