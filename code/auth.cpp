#include <iostream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
#include <fstream>
#include <random>
#include <sstream>
#include <map>
#include "auth.h"
#include "programmerror.h"
#include <exception>
#include <typeinfo>
#include <string>


Auth::Auth(std::string ID, std::string pass) {   ///???
    Id = ID; 
    password = pass;
    }


void Auth::GenSALT()
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<long long unsigned> distribution(0,0xFFFFFFFFFFFFFFFF);
    unsigned long long numericsalt = distribution(generator);
    std::stringstream stream;
    stream << std::hex << numericsalt;
    std::string strsalt(stream.str());
    for (long unsigned int i =0; i<=strsalt.size(); i++) {
        strsalt[i] = toupper(strsalt[i]);
    }
    if (strsalt.size() < 16) {
        std::string strsalttemp =strsalt;
        for (unsigned i = strsalt.size(); i <16; i++) {
            strsalttemp.insert (strsalttemp.begin(), '0');
        }
        strsalt = strsalttemp;
    }

    SALT = strsalt;
}

bool Auth::CompareHashes(std::string ClientHash)
{	try{
		
    	using namespace CryptoPP;
    	Weak::MD5 hash;
    	std::string msg = SALT+password;
    	//std::cout<<msg<<std::endl;
    	StringSource ss(msg, true , new HashFilter(hash, new HexEncoder(new StringSink (strHash))));
    	
    	
    } catch(const CryptoPP::Exception& e ) {
		throw server_error(std::string("Hash calsulation error"));   // catch exception
        return false;
    }	
        
		std::cout<<"Kлиент: "<<ClientHash<<"\n"<<"Сервер: "<<strHash<<" "<<std::endl;
		if (ClientHash.compare(strHash) != 0){
			throw server_error(std::string("Invalid Hash"));
	} 
    return (ClientHash.compare(strHash) == 0);
}



