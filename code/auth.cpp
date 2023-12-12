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
            strsalttemp.insert(strsalttemp.begin(), '0');
        }
        strsalt = strsalttemp;
    }

    SALT = strsalt;
    return SALT;
}

std::string Auth::GenHash(const std::string& password) {
    std::string msg = SALT + password;
    std::string strHash;

    CryptoPP::Weak::MD5 hash;
    CryptoPP::StringSource ss(msg, true,
        new CryptoPP::HashFilter(hash,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(strHash))));
    return strHash;
}


bool Auth::CompareHashes(std::string ClientHash) {
    std::string ServerHash = GenHash(password);

    if (ClientHash != ServerHash) {
        throw server_error(std::string("Invalid Hash"));
    }
	std::cout<<"Kлиент: "<<ClientHash<<"\n"<<"Сервер: "<<ServerHash<<" "<<std::endl;
    return (ClientHash.compare(ServerHash) == 0);
}




