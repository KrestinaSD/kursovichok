#include <iostream>
#include <cstdlib> 
#include <unistd.h> 
#include <string>
#include "interface.h"
#include <fstream>
#include <map>
#include <exception>
#include "ErrorTracker.h"

using namespace std;

Opts::Opts(int argc, char **argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "b:l:p:h")) != -1) {
        switch (opt) {
        case 'b':
            DataBaseName = string(optarg);
            break;
        case 'l':
            LogFileName = string(optarg);
            break;
        case 'p':
            Port = strtol(optarg,nullptr,10);
            break;
        case 'h': 
        case '?': 
        case ':': 
            usage(argv[0]);
        }
    }
}

void Opts::usage(const char* progName)
{
    std::cout<<"Usage: "<<progName<<" [-b DataBaseName] [-n LogFileName] [-p Port] \n";
    exit(1);
}

bool Opts::CheckFiles()
{
        std::ifstream file1(DataBaseName);
        if (!file1.good()) {
            throw server_error(std::string("Wrong database-file Name"), true);
			return false;
        }
        std::ifstream file2(LogFileName);
        if (!file2.good()) {
            throw server_error(std::string("Wrong log-file Name"), true);
			return false;
		}

    	return true;
}
