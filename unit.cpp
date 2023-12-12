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
#include <limits>
const double inf = std::numeric_limits<double>::infinity();

//Тесты сравнения хешей CompareHashes в модуле аутентификации
SUITE(HAHA){
	TEST(SIZE_SALT){
		Auth auth("password");
		std::string salt = auth.GenSALT();
    	CHECK(salt.size() == 16);
	}
	TEST(BAD_SALT){
    	Auth auth("password");
    	std::string salt = auth.GenSALT();
    	std::string hash = auth.GenHash("password");
    	// Устанавливаем неправильный SALT
    	auth.setSALT("0000");
    	CHECK_THROW(auth.CompareHashes(hash), server_error);
	}
	TEST(EMPTY_SALT){
		Auth auth("password");
    	std::string salt = auth.GenSALT();
    	std::string hash = auth.GenHash("password");
    	// Устанавливаем пустой SALT
    	auth.setSALT("");
    	CHECK_THROW(auth.CompareHashes(hash), server_error);
	}

	TEST(BAD_PASS){
		 Auth auth("password");
    	std::string salt = auth.GenSALT(); 
    	// делаем хэширование с "плохим паролем"
    	std::string badHash = auth.GenHash("badpassword");
    	CHECK_THROW(auth.CompareHashes(badHash), server_error);
	}
	
	TEST(EMPTY_PASS){
		Auth auth("password");
    	std::string salt = auth.GenSALT();
    	std::string badHash = auth.GenHash("");
    	CHECK_THROW(auth.CompareHashes(badHash), server_error);
	}

	TEST(NORM){
		Auth auth("password");
   		std::string salt = auth.GenSALT();
    	std::string goodHash = auth.GenHash("password");
    	CHECK(auth.CompareHashes(goodHash));
	}
}

//Тесты вычисления среднего арифметического в модуле калькулятора
SUITE(CALC){
	TEST(EMPTY_VEC){
		Average avg;
    	std::vector<double> arr;
    	CHECK_THROW(avg.average(arr), server_error);
	}
	
	TEST(MAX_OVER_VEC){
		Average avg;
    	std::vector<double> arr = {1.79769e+308, 1.79769e+308, 1.79769e+308}; 
    	CHECK_EQUAL(inf, avg.average(arr));

	}
	TEST(MIN_OVER_VEC){
		Average avg;
    	std::vector<double> arr = {-1.79769e+308, -1.79769e+308,-1.79769e+308}; 
    	CHECK_EQUAL(-inf, avg.average(arr));
	}
	
	TEST(NORM_VEC){
		Average avg;
    	std::vector<double> arr = {1, 2, 3}; 
    	CHECK_EQUAL(2, avg.average(arr));
	}
}

//Тесты открытия базы данных
SUITE(CLIENTIC){
	TEST(EMPTY_PATH){
		 CHECK_THROW(DB(""), server_error);
	}
	
	TEST(BAD_PATH){
		CHECK_THROW(DB("no/base/file.txt"), server_error);
	}
	
	TEST(BAD_ID_CHECK){
		DB db("test_base.txt");
    	CHECK_THROW(db.IDcheck("non_existing_id"), server_error);
    
	}
	TEST(ID_CHECK){
		DB db("test_base.txt");
		CHECK(db.IDcheck("vasya"));
	}
}

//Тесты, связанные с логерами
SUITE(LOGGERY){
	TEST(EMPTY_PATH_FILE){
		Logger logger;
        CHECK_THROW(logger.set_path(""), std::invalid_argument);
	}
	TEST(VERY_BAD_PATH){
		Logger logger;
		CHECK_THROW(logger.set_path("Путь/к/лог/файлу.txt"), std::invalid_argument);
	}
	
	TEST(EMPTY_MESSAGE){
		Logger logger;
        logger.set_path("test_log.txt");
        CHECK_THROW(logger.writelog(""), std::invalid_argument);
	}
	TEST(VREMYA){
		Logger logger;
        std::string dateTime = logger.getDateTime();
        CHECK(dateTime.length() > 0);
	}
	
	TEST(NORM){
		Logger logger;
		logger.set_path("test_log.txt");
        CHECK_EQUAL(0, logger.writelog("Test message"));
	}
}

int main()
{
    return UnitTest::RunAllTests();
}


