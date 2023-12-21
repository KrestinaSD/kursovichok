#include "calculator.h"

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
		  	//if ((result >= std::numeric_limits<double>::max()) or (result <= std::numeric_limits<double>::min())){
					//throw server_error("Result is very big/small.");
				//}
		  	
		}catch(const server_error & e){
			std::cerr << e.what() << '\n';
		}	     	 		
		return result;
}

