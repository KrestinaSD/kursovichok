/**
* @file calculator.h
* @author Крестина С.Д.
* @version 1.0
* @brief Заголовочный файл для модуля calculator, отвечающий за вычисления
*/

#pragma once
#include <vector>
#include <iostream>
#include <exception>
#include "programmerror.h"

/** 
 * @brief Класс для вычисления среднего арифметического вектора
 * @details Метод для вычисления
 */
class Average
{
private:
	double result; ///< Результат вычислений
public:
	/**
 	* @brief Конструтор класса без параметров
 	*/
	Average(){};
	 /**
 	* @brief Функция вычисления среднего арифметического вектора
 	* @param [in] vector<double>& arr вектор со значениями типа double
 	* @return result
 	*/
	double average(std::vector<double>& arr);
};
