/**
* @file interface.h
* @author Крестина С.Д.
* @version 1.0
* @brief Заголовочный файл для модуля interface, отвечающий за разбор ПКС, и включение других модулей
*/
#pragma once
#include <string>
#include <optional>
/** 
 * @brief Класс для разбора командной строки и включения других модулей
 * @details Методы: разбор ПКС
 * проверка файлов
 * получение пути до файла с логами
 */
class interface
{
private:
    std::string DataBaseName = "bas"; ///< Путь к файлу с базой данных
    std::string LogFileName = "log"; ///< Путь к файлу для записи логов
    int Port = 33333; ///< Порт, на котором работает сервер
    void usage(const char* progName); ///< Вывод подсказки и останов
public:
	/**
 	* @brief Функция разбора ПКС и включение модулей
 	* @param [in] int argc,
 	* @param [in] char **argv
 	* @details В этом методе происходит разбор ПКС и включение модулей
 	* @return 1 or 0
 	*/
    int Opts(int argc, char **argv);
    /**
 	* @brief Функция получения пути до журнала работы
 	* @details В этом методе возвращается путь до файла с журналом работы
 	* @return LogFileName
 	*/
    std::string getLogFileName() /// Возвращает путь к файлу для записи логов
    {
        return LogFileName;
    }
};

