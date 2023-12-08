#include <iostream>
#include <cstdlib> 
#include <unistd.h> 
#include <string>
#include <fstream>
#include <filesystem>
#include <optional>
#include <unordered_map>
#include "interface.h"
#include "programmerror.h"
#include "communicator.h"
#include "logger.h"

int interface::Opts(int argc, char **argv)
{
	/*********************************
	*
	*   разбор пкс
	*
	*********************************/
    // Создаем unordered_map для хранения аргументов командной строки
    std::unordered_map<char, std::string> args;
    int opt;
   /*if (argc < 2) {
    usage(argv[0]); // Выводим справку
    return 1; // Завершаем программу
    } else {*/
    while ((opt = getopt(argc, argv, "b:l:p:h")) != -1) {
        switch (opt) {
        case 'b':
        case 'l':
        case 'p':
            args[opt] = std::string(optarg);
            break;
        case 'h': 
        case '?': 
        case ':': 
            usage(argv[0]);
        }
    }

    if(args.count('b')) {
        DataBaseName = args['b'];
    }
    if(args.count('l')) {
        LogFileName = args['l'];
    }
    if(args.count('p')) {
        Port = std::stoi(args['p']);
    }
    
    /***************************
    *
    * Инициализация элементов класса
    *
    *****************************/
	ErrorTracker ErrTr;
	Logger logger;
    try{
    	ErrTr.setLogName(LogFileName);
    	logger.set_path(LogFileName);
    	CheckFiles();
    	DB new_db(DataBaseName);
    	WebManager main_manager(Port);
    	main_manager.bindSocket();
    	std::cout<<"The server start"<<std::endl;
        logger.writelog("The server started");
    	main_manager.listenSocket();
    	logger.writelog("The server listen sockets");
    	while (true) {
        	int sock = main_manager.accepting();
        	std::cout<<"Client connected"<<std::endl;
        	logger.writelog("Client connected");
        	main_manager.conversation(Port,  LogFileName, new_db, sock);
    	}
    	
	} catch (const server_error & e) {
	    logger.writelog(e.what());
		ErrTr.write_log(e.what(), e.getState());
        if (e.getState()){
			exit(1);
		}
    }
    return 0;
   // }
}

/*****
*
* подсказка
*
*****/
void interface::usage(const char* progName)
{
    std::cout<<"Использование: "<<progName<<" [-b DataBaseName] [-n LogFileName] [-p Port] \n";
    exit(1);
}


/******
*
*проверка файлов
*
*******/
bool interface::CheckFiles()
{
    std::ifstream databaseFile(DataBaseName);
    if(!databaseFile.good()) {
        throw server_error(std::string("Неверное имя файла базы данных"), true);
        return false;
    }
    databaseFile.close();

    std::ifstream logFile(LogFileName);
    if(!logFile.good()) {
        throw server_error(std::string("Неверное имя файла журнала"), true);
        return false;
    }
    logFile.close();
    return true;
}
