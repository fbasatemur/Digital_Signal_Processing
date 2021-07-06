#include <iostream>
#include <fstream>
#include "Wave.h"
#define PI 3.1415926

using namespace std;


// The Input Side Algorithm
//float* Conv(float* input, int inputN, float* filter, int filterN, int& resultN)
//{
//	resultN = inputN + filterN - 1;
//	float* result = new float[resultN]();
//
//	for (int i = 0; i < inputN; i++)
//		for (int j = 0; j < filterN; j++)
//			result[i + j] += input[i] * filter[j];
//		
//	return result;
//}

// The Output Side Algorithm
float* Conv(float* input, int inputN, float* filter, int filterN, int& resultN)
{
	resultN = inputN + filterN - 1;
	float* result = new float[resultN]();
	int startk, endk;

	for (int i = 0; i < resultN; i++)
	{
		startk = i >= inputN ? i - inputN + 1 : 0;
		endk = i < filterN ? i : filterN - 1;

		for (int k = startk; k <= endk; k++)
			result[i] += input[i - k] * filter[k];
	}
	return result;
}


int main(int argc, char* argv[]) {
	
	if (argc == 4) {
		
		WavHeader* header = new WavHeader;
		size_t numSamples;

		float* samples = WavRead(argv[1], header, &numSamples);

		// gelen ses sinyali, 40000 orneklemeye sahip, fs=8KHz 5s
		cout << "Bit rate:        " << header->bps << endl;
		cout << "Sample rate:     " << header->sampleRate << endl;
		cout << "No. of channels: " << header->numChannels << endl;
		cout << "Number of samples: " << numSamples << endl << endl;


		// 400Hz kesim frekansi icin katsayilari al
		int filterN = atoi(argv[2]);
		float* filter = new float[filterN];
		
		ifstream file(argv[3]);
		string coeff;
		for (size_t i = 0; i < filterN; i++) {
			file >> coeff;
			filter[i] = stof(coeff);
		}
		file.close();
		
		// 1KHz ve 400Hz den olusan inputa, 400Hz lik kesim frekansli LowPass uygulayalim
		int resultN;
		float* result = Conv(samples, numSamples, filter, filterN, resultN);
		
		cout << "  -input-  " << "\t" << "  -output-  " << endl; 
		for(int i = 0; i< 20; i++)
			cout<< "[" << i << "]: " << samples[i] << "\t -> " << result[i] << endl; 
		
		WavSave("result.wav", header, resultN, result);
	}
	else
		printf("You must enter 4 params \n");

	return 0;
}