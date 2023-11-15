#pragma once
#include <string>
#include <map>

using namespace std;

class Opts
{
private:
    string DataBaseName = "base.txt"; ///< Путь к файлу с базой данных
    string LogFileName = "log.txt"; ///< Путь к файлу для записи логов
    int Port = 33333; ///< Порт, на котором работает сервер
    void usage(const char* progName); ///<вывод подсказки и останов
public:
    Opts(int argc, char **argv);
	bool CheckFiles();
    string getDataBaseName() ///<Возвращает путь к файлу с базой данных 
    {
        return DataBaseName;
    }
    string getLogFileName() ///<Возвращает путь к файлу для записи логов
    {
        return LogFileName;
    }
    int getPort() ///<Порт, на котором работает сервер
    {
        return Port;
    }
};
