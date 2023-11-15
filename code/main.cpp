#include "interface.h"
#include "Auth.h"
#include "calculator.h"
#include "DataBase.h"
#include <iostream>
#include "WebManager.h"
#include "communicator.h"
#include <vector>
#include <string>
#include <map>
#include "ErrorTracker.h"
#include "logger.h"

ErrorTracker ErrTr;
Logger logger;

int main(int argc, char **argv)
{

	try{
    	Opts op(argc, argv);
    	ErrTr.setLogName(op.getLogFileName());
    	//logger.set_path(op.getLogFileName());
    	op.CheckFiles();
    	DB new_db(op.getDataBaseName());
    	WebManager main_manager(op.getPort());
    	main_manager.new_bind();
    	std::cout<<"The server start"<<std::endl;
    	//logger.writelog("The server start");
    	main_manager.start_listening();
    	while (true) {
        	int sock = main_manager.accepting();
        	std::cout<<"Client connected"<<std::endl;
        	conversation(op.getPort(), op.getLogFileName(), new_db, sock);
    	}
    	
	} catch (const server_error & e) {
		ErrTr.write_log(e.what(), e.getState());
        if (e.getState()){
			exit(1);
		}
    }
    return 0;
}



