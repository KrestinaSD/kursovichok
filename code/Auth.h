#pragma once
#include <map>
#include <string>
#include "ErrorTracker.h"


class Auth
{
private:
    
    std::string SALT; ///< Соль для вычисления хэша
    std::string Id; ///< Идентификатор клиента
    std::string password; ///< Пароль клиента
    std::string strHash; ///< Хэш в виде шестнадцатиричных цифр

public:



    Auth(std::string ID, std::string pass);


    void GenSALT();
    char ERRmsg[3] = {'E', 'R','R'}; ///< Сообщение, отсылаемое клиенту при ошибке его обрабоки
    char OKmsg[2] = {'O', 'K'}; ///< Сообщение, отсылаемое клиенту при успешной авторизации

    bool CompareHashes(std::string ClientHash);
    std::string getSALT() ///< Возвращает соль
    {
        return SALT;
    }
    std::string getId() ///< Возвращает идентефикатор
    {
        return Id;
    }
    std::string getpass() ///< Возвращает пароль
    {
        return password;
    }
    std::string getstrHash() ///< Возвращает хэш
    {
        return strHash;
    }
};
