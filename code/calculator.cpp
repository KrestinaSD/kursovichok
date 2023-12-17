#include "calculator.h"

double Average::average(std::vector<double>& arr) {
	double sum = 0;
		try{
			
			if (arr.empty()){
				throw server_error("Count Error");
			}
			
			for (std::vector<double>::iterator it = arr.begin(); it != arr.end(); ++it){
				std::cout << '\t' << *it;
			}
			
			std::cout << '\n';
			
			
			for (size_t i = 0; i < arr.size(); i++) {
				sum += arr[i];
			}
		
		}catch(const server_error & e){
			std::cerr << "Caught exception: " << e.what() << '\n';
		}
		     	 
    	
		result = sum/arr.size();
		
		return result;
}

