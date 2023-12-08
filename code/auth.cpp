#include "auth.h"


Auth::Auth(std::string pass) {  
    password = pass;
    }


std::string Auth::GenSALT()
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
            strsalttemp.insert (strsalttemp.begin(), '0');
        }
        strsalt = strsalttemp;
    }

    SALT = strsalt;
    return SALT;
}

bool Auth::CompareHashes(std::string ClientHash)
{	try{
    	using namespace CryptoPP;
    	Weak::MD5 hash;
    	std::string msg = SALT+password;
    	StringSource ss(msg, true , 
    	                new HashFilter(hash, 
    	                               new HexEncoder(new StringSink (strHash))));
    	
    } catch(const CryptoPP::Exception& e ) {
		throw server_error(std::string("Hash calculation error")); 
        return false;
    }	
        
		if (ClientHash.compare(strHash) != 0){
			throw server_error(std::string("Invalid Hash"));
	} 
	std::cout<<"Kлиент: "<<ClientHash<<"\n"<<"Сервер: "<<strHash<<" "<<std::endl;
    return (ClientHash.compare(strHash) == 0);
}



