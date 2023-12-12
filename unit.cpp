#include "code/auth.h"
#include "code/auth.cpp"
#include "code/calculator.h"
#include "code/calculator.cpp"
#include "code/communicator.h"
#include "code/communicator.cpp"
#include "code/interface.h"
#include "code/interface.cpp"
#include "code/logger.h"
#include "code/logger.cpp"
#include "code/programmerror.h"
#include "code/programmerror.cpp"
#include "code/userbase.h"
#include "code/userbase.cpp"
#include <UnitTest++/UnitTest++.h>
#include <string>

//Тесты сравнения хешей CompareHashes в модуле аутентификации
SUITE(HAHA){
	TEST(BAD_SALT){
		std::string Client_HASH = "AE89DB7F4CA9B00B2A72CE5CF36BD48B";
		std::string pass = "qwerty";
		Auth au(pass);
		au.setSALT("0000");
		CHECK_THROW(au.CompareHashes(pass), server_error);
	}}
	/*TEST(EMPTY_SALT){
		
	}

	TEST(BAD_PASS){
		
	}
	TEST(EMPTY_PASS){
		
	}

	TEST(NORM){
		
	}
}

//Тесты вычисления среднего арифметического в модуле калькулятора
SUITE(CALC){
	TEST(EMPTY_VEC){
	
	}
	TEST(MAX_OVER_VEC){}
	TEST(MIN_OVER_VEC){}
	
	TEST(NORM_VEC){}
}

//Тесты открытия базы данных
SUITE(CLIENTIC){
	TEST(EMPTY_PATH){
	userbase us;
	}
	TEST(BAD_PATH){}
	
	TEST(NORM_PATH){}
	TEST(ID_CHECK){}
}

//Тесты, связанные с логерами
SUITE(LOGGERY){
	TEST(BAD_PATH_NEW_FILE){}
	TEST(VERY_BAD_PATH){}
	
	TEST(EMPTY_MESSAGE){}
	TEST(){}
	
	TEST(NORM){}
}*/

int main()
{
    return UnitTest::RunAllTests();
}


