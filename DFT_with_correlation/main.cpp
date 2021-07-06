#include <math.h>
#include <iostream>
#include <iomanip>
#include "Wave.h"
#define PI 3.14159265F
using namespace std;


void IDFT(float* samples, size_t numSamples, float* real, float* imag) {

	size_t freqPoints = numSamples / 2 + 1;

	// INVERSE DFT
	float w;
	for (size_t k = 0; k < freqPoints; k++) {
		for (size_t i = 0; i < numSamples; i++) {
			w = 2.0F * PI * k * i / numSamples;
			real[k] += (samples[i] * cos(w));
			imag[k] -= (samples[i] * sin(w));
		}
	}
}

int main(int argc, char* argv[])
{
	
	if (argc == 2) {

		WavHeader* header = new WavHeader;
		size_t numSamples1;
		
		const char* fileName = argv[1];
		float* samples1 = WavRead(fileName, header, &numSamples1);

		// gelen ses sinyali, 40000 orneklemeye sahip, 5s
		cout << "Bit rate:        " << header->bps << endl;
		cout << "Sample rate:     " << header->sampleRate << endl;
		cout << "No. of channels: " << header->numChannels << endl;
		cout << "Number of samples: " << numSamples1 << endl << endl;


		// 100 ornek uzerinden sonuclar test edilecek
		size_t numSamples2 = 100;

		// farkli frekansta bir sinyal uret exp: 200Hz, 100 sampling
		float f = 200.0F;
		float fs = float(header->sampleRate);		// gelen sinyal ile esit miktarda orneklem frekansi
		float* samples2 = new float[numSamples2];
		float t;
		for (size_t i = 0; i < numSamples2; i++)
		{
			t = float(i / fs);
			samples2[i] = sin(2.0F * PI * f * t);
		}


		// gelen sinyalin ilk 100 ornegini kendisiyle carpalim. (Aranan sinyalin kendisi oldugunu varsaydigimizdan dolayi)
		float* result1 = new float[numSamples2];
		for (size_t i = 0; i < numSamples2; i++)
			result1[i] = samples1[i] * samples1[i];

		// gelen sinyali bir de uretilen sentetik sinyal ile carpalim
		float* result2 = new float[numSamples2];
		for (size_t i = 0; i < numSamples2; i++)
			result2[i] = samples1[i] * samples2[i];


		// carpim sonuclari
		cout << "s1 * s1" << " \t " << "s1 * s2" << endl;
		for (size_t i = 0; i < numSamples2; i++)
			cout << fixed << std::setprecision(6) << result1[i] << " \t " << result2[i] << endl;


		// s1 * s1 sonucunun IDFT sonuclarini hesapla
		size_t freqPoints = numSamples2 / 2 + 1;
		float* real1 = new float[freqPoints]();    // initialize with 0
		float* imag1 = new float[freqPoints]();    // initialize with 0
		IDFT(result1, numSamples2, real1, imag1);


		// s1 * s2 sonucunun IDFT sonuclarini hesapla
		float* real2 = new float[freqPoints]();    // initialize with 0
		float* imag2 = new float[freqPoints]();    // initialize with 0
		IDFT(result2, numSamples2, real2, imag2);


		// file write
		//ofstream file("values.txt");

		std::cout << endl << "IDFT1(s1 * s1) Magnitude" << " \t " << "IDFT2(s1 * s2) Magnitude" << endl;
		for (size_t i = 0; i < freqPoints; i++)
		{
			std::cout << fixed << std::setprecision(6) << sqrt(real1[i] * real1[i] + imag1[i] * imag1[i]) << " \t \t \t " << sqrt(real2[i] * real2[i] + imag2[i] * imag2[i]) << endl;
			//file << fixed << std::setprecision(6) << sqrt(real1[i] * real1[i] + imag1[i] * imag1[i]) << " \t " << sqrt(real2[i] * real2[i] + imag2[i] * imag2[i]) << endl;
		}

		//file.close();


		/*
			Sonuclar incelendiginde bir sinyalin icerisinde, aradigimiz sinyalin olup olmadigini IDFT degerlerinin maksimum degerine gore yorumlayabiliriz.
			IDFT1 (s1 * s1) degerlerinin maksimum sonucu 49.8; 
			IDFT2 (s1 * s2) degerlerinin maksimum sonucu 24.9 olduguna gore burada aradigimiz s1 sinyalinin, s1 ile maksimum ortustugunu goruruz.
			Yani bir nevi benzerlik olcumunu bu yol ile yapmis oluruz.
			Ayrica sonuclari daha iyi gozlemleyebilmek icin grafik goruntulerini de rar dosyasina ekledim.
		*/

		delete header;
		delete[] real1, real2, imag1, imag2;
		delete[] samples1;
		delete[] samples2;
		delete[] result1;
		delete[] result2;
	}
	else
		cout << "You must enter audio name" << endl;
	
	
	return 0;
}