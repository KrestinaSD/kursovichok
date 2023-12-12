
#include "userbase.h"

DB::DB(std::string DBName)
    {
    	std::string path_to_userbase = DBName;
        std::ifstream file(path_to_userbase);
		if(!file.good()){
			throw server_error(std::string("Wrong DB File Name"), true);
		} 
        std::string Pair;
        while(getline(file, Pair)) {
            DataBaseP[Pair.substr(0,Pair.find(sep))] = Pair.substr(Pair.find(sep)+1);
        }
        file.close();
    }

bool DB::IDcheck(std::string login)
    {
			if (DataBaseP.count(login) != 1){
				throw server_error(std::string("Invalid ID"), false);}
			
        return DataBaseP.count(login) == 1;
    }

bool DB::CheckFiles(){
    std::ifstream databaseFile(path_to_userbase);
    if(!databaseFile.good()) {
        return false;
    }
    databaseFile.close();
    return true;
}
