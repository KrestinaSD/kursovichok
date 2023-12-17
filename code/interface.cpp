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
    // Создаем unordered_map для хранения аргументов командной строки
    std::unordered_map<char, std::string> args;
    int opt;
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
    
	Logger logger;
    try{
    	communicator main_manager;
    	logger.set_path(LogFileName);
    	DB new_db(DataBaseName);
    	main_manager.conversation(Port, new_db.get_data());
    	
	} catch (const server_error & e) {
		std::stringstream ss;
    	ss << "Error: " << e.what() << ", State: " << e.getState();
    	logger.writelog(ss.str());
          if (e.getState() == "Критическая"){
			exit(1);
		}
    }
    return 0;
}

void interface::usage(const char* progName)
{
    std::cout<<"Использование: "<<progName<<" [-b DataBaseName] [-n LogFileName] [-p Port] \n";
    exit(1);
}



