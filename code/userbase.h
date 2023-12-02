#pragma once

#include <map>
#include <string>
#include <fstream>
#include <exception>
#include <typeinfo>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "programmerror.h"


class DB
{
private:
    char sep = ':'; ///<Разделитель идентификатора и пароля в базе данных
public:
	std::map <std::string,std::string> DataBaseP; ///<Словарь с парами идентификатор:пароль

    DB(std::string DBName);

    bool IDcheck(std::string login);
};
