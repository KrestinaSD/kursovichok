#include "calculator.h"
#include "programmerror.h"
#include <sstream>

double Average::average(std::vector<double>& arr) {
	double sum = 0;
		try{
			if (arr.empty()){
    			throw server_error("Vector is empty");
			} 
			
			for (size_t i = 0; i < arr.size(); i++) {
				sum += arr[i];
			}
			
		  	result = sum/arr.size(); 
		  	
		  	
		}catch(const server_error & e){
			std::stringstream ss;
    		ss << "Error: " << e.what() << ", State: " << e.getState();
    		std::cerr << e.what() << std::endl;
		}	     	 		
		return result;
}

