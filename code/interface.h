#pragma once
#include <string>
#include <optional>

class interface
{
private:
    std::string DataBaseName = "base.txt"; ///< Путь к файлу с базой данных
    std::string LogFileName = "log.txt"; /// Путь к файлу для записи логов
    int Port = 33333; /// Порт, на котором работает сервер
    void usage(const char* progName); /// Вывод подсказки и останов
public:
    int Opts(int argc, char **argv);
    bool CheckFiles();
    std::string getDataBaseName() ///Возвращает путь к файлу с базой данных 
    {
        return DataBaseName;
    }
    std::string getLogFileName() /// Возвращает путь к файлу для записи логов
    {
        return LogFileName;
    }
    int getPort() ///Порт, на котором работает сервер
    {
        return Port;
    }
};

