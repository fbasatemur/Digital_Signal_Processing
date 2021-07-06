#include <stdio.h>
#include <math.h> 
#include <stdlib.h> 
#define PI 3.141592

float Gauss(float x) 
{ 
    return  exp(- pow(x,2) / 2.0) / sqrt(2.0 * PI); 
} 
  
// Simpson's 1/3 Rule
float Simpson(float lowLimit, float upLimit, int n) 
{ 
    float h = (upLimit - lowLimit) / n; 
	
    float res = 0; 
	res += Gauss(lowLimit);
	
    for (int i = 1; i < n; i++) { 
        if (i % 2 == 0) 
			res += 2 * Gauss(lowLimit + i * h);
        else
            res += 4 * Gauss(lowLimit + i * h);  
    } 
	res += Gauss(upLimit);
	
    return res * (h / 3); 
}

int main(int argc, char* argv[]) {

	if (argc == 4) {

		float lowerLimit = atof(argv[1]); 	// Lower limit 
		float upperLimit = atof(argv[2]); 	// Upper limit 
		int n = atoi(argv[3]); 				// Number of interval 
		printf("%f \n", Simpson(lowerLimit, upperLimit, n)); 

	}
	else
		printf("You must enter 4 params \n");

	return 0;
}

