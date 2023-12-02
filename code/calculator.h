#pragma once
#include <vector>
#include <iostream>
#include <exception>
#include "programmerror.h"

class Average
{
private:
	double result; ///< Результат вычислений
public:
	Average(){}; ///<Конструктор без параметров
	double average(std::vector<double>& arr);
};
