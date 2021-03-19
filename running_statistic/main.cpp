#include <iostream>
#include <cmath>
#define PI 3.141592653589793

using namespace std;

double GenerateSinSignal(int t) {

	// A * sin(wt + Q)
	// w = 2 * PI * f

	double f = 1.0 / 7.0; 	// T = 7
	double w = 2.0 * PI * f;
	return sin(w * (double)t);
}

double GenerateNoisySignal() {
	double noise = (rand() % 11 - 5.0) / 10.0;		// -0.5 .. +0.5
	return 1.0 + noise;
}

void Pause(float seconds)
{
	clock_t endtime = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endtime)
	{}
}

double RunningMean(double sum, int n){
	return sum / n;
}

double RunningSD(double sumSquares, double sum, int n){
	return sqrt((sumSquares - (pow(sum, 2) / n)) / (n-1));
}

int main(int argc, char* argv[]) {

	if (argc == 3) {

		int signalType = atoi(argv[1]);
		int n = atoi(argv[2]);
		
		if (n > 1 && signalType >= 0 && signalType < 2) {

			double sum = 0.0;
			double sumSquares = 0.0;
			double signal;
			srand(time(0));
			
			if(signalType == 0)
				signal = GenerateSinSignal(0);		// current time : t0
			else 
				signal = GenerateNoisySignal();
			
			sum += signal;
			sumSquares += pow(signal, 2);
			cout << "t: " << 0 << " Signal: "<< signal << endl;

			for (int t = 1; t < n; t++)				// t1 and after
			{
				if(signalType == 0)
					signal = GenerateSinSignal(t);
				else 
					signal = GenerateNoisySignal();
				
				sum += signal;
				sumSquares += pow(signal, 2);
				cout << "t: " << t << " Signal: "<< signal << " Mean: "<< RunningMean(sum, t+1) << " SD: " << RunningSD(sumSquares, sum, (t+1)) << endl;
				
				Pause(0.5);
			}
		}
		else
			cout << "You must enter first argument \"0 or 1\", second argument > 1" << endl;

	}
	else
		cout << "You must enter 2 digit argument " << endl;


	return 0;
}