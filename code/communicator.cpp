#include "communicator.h"
#include <limits>
#include <string.h>
using namespace std;

struct sockaddr_in addr;

interface lg; 
string logfile = lg.getLogFileName();
Logger logi(logfile);

//communicator::communicator(unsigned int port){
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
        throw server_error("Invalid Hash");
    }
	std::cout<<"Kлиент: "<<ClientHash<<"\n"<<"Сервер: "<<ServerHash<<" "<<std::endl;
    return (ClientHash.compare(ServerHash) == 0);
}

///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void communicator::conversation(unsigned int port, std::map <std::string,std::string> DataBaseP)
{
	try{
	// Создание сокета
    int sckt = socket(AF_INET, SOCK_STREAM, 0);
    if(sckt < 0) {
        throw server_error("Socket creation error", true);
    }
    logi.writelog("Socket creation OK");
     // Задание параметров адреса сервера
    addr.sin_family = AF_INET; // Семейство адресов
    addr.sin_port = htons(port); // Порт, на котором будет работать сервер
    addr.sin_addr.s_addr = inet_addr(Adress); // адрес

    // Привязка сокета к адресу
    int rc = bind(sckt, (struct sockaddr *)&addr, sizeof(addr));
    if(rc < 0) {
        throw server_error("Socket bind error", true);
    }
    logi.writelog("Socket bind OK");

    // Начало прослушивания входящих соединений
    int l = listen(sckt, 100);
    if (l < 0) {
    	throw server_error("Listening error", true);
    }
    std::cout << "The server started" << std::endl;
    logi.writelog("The server started");
    while (true) {
    	// Принятие входящего соединения
    	sockaddr_in * client_addr = new sockaddr_in;
    	socklen_t len = sizeof (sockaddr_in);
    	// Принятие входящего соединения на сокете sock
    	int work_sock = accept(sckt, (sockaddr*)(client_addr), &len);
    	if (work_sock < 0){
        	throw server_error("Accepting error");
    	}
    	logi.writelog("Accepting OK");
    	char buf[1024];
    	rc = recv(work_sock, buf, sizeof(buf), 0);
    	if (rc < 0){
    		close(work_sock);
    		throw server_error("Receiving error");
    	}
    	std::string USRlogIn = string(buf, rc);
    	for (uint i = 0; i < USRlogIn.size();i++){
			if (USRlogIn[i] == '\n'){
				USRlogIn.pop_back();}
		}
		if(DataBaseP.find(USRlogIn) == DataBaseP.end()) {
                    close(work_sock);
                    throw server_error("Invalid ID");
        }
    	getpass(DataBaseP[USRlogIn]);
    	std::string str_salt = GenSALT();
    	char salt_buf[16];
        strcpy(salt_buf, str_salt.c_str());
        rc = send(work_sock, salt_buf, sizeof(salt_buf), 0);
        if (rc < 0){
    		close(work_sock);
    		throw server_error("Sending error");
    	}
    	rc = recv(work_sock, buf, sizeof(buf), 0);
    	if (rc < 0){
    		close(work_sock);
    		throw server_error("Receiving error");
    	}
        string pass = string(buf, rc);
    	for (uint i = 0; i < pass.size();i++){
			if (pass[i] == '\n'){
				pass.pop_back();
			}
		}
		CompareHashes(pass);
		rc = send(work_sock, "OK", 2, 0);
		if (rc < 0){
    		close(work_sock);
    		throw server_error("Sending error");
    	}
		
        uint32_t num_vectors;
        uint32_t vector_len;
        rc = recv(work_sock, &num_vectors, sizeof num_vectors, 0);
        if (rc < 0){
    		close(work_sock);
    		throw server_error("Receiving error");
    	}  
    	
        for(unsigned int i =0; i< num_vectors; i++) {
        	rc = recv(work_sock, &vector_len, sizeof vector_len, 0);
        	if (rc < 0){
    			close(work_sock);
    			throw server_error("Receiving error");
    		}
    		
        	std::vector<double> int_buf(vector_len);
    		rc = recv(work_sock, int_buf.data(), vector_len*sizeof(double), 0);
        	if (rc < 0){
    			close(work_sock);
    			throw server_error("Receiving error");
    		}
    		
    		/*///////////////////////////
    		if (memcmp(int_buf.data(), "\0", 8) != 0){
        		close(work_sock);
        		throw server_error("Received number is too large");
    		}
    		////////////////////////////*/
    		
        	std::vector<double> arr;
        	
        	for(unsigned int i = 0; i < vector_len; i++) {
        	if ((int_buf[i] >= std::numeric_limits<double>::max()) or (int_buf[i] < std::numeric_limits<double>::min())){
        		arr.push_back(0);
        	}else{
                    arr.push_back(int_buf[i]);
            }}

            Average res;
            double result = res.average(arr);
            rc = send(work_sock,  &result, sizeof(double), 0);
            if (rc < 0){
    			close(work_sock);
    			throw server_error("Sending error");
    		} 
       }
       std::cout<<"Calculations were successful\n";
       logi.writelog("Calculating OK");
       close(work_sock);
       std::cout<<"Done\n";
       logi.writelog("Client disconnected");
       
    }
   } catch (const server_error & e) {
		std::stringstream ss;
    	ss << "Error: " << e.what() << ", State: " << e.getState();
    	logi.writelog(ss.str());
          if (e.getState() == "Критическая"){
			exit(1);
		}
        close(sckt);
    } 
}



