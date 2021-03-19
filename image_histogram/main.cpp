#include <iostream>
#include <stdio.h>
#include <cmath>
#define HEADERINFOSIZE 54
#pragma warning(disable:4996)

using namespace std;
typedef unsigned char BYTE;


BYTE* ReadGrayBMP(char* filename, int& width, int& height)
{
	FILE* file = fopen(filename, "rb");

	if (file == NULL)
		throw "File is not find !";

	BYTE info[HEADERINFOSIZE];
	fread(info, sizeof(BYTE), HEADERINFOSIZE, file);

	// get image height and width from header
	width = *(int*)&info[18];
	height = *(int*)&info[22];

	BYTE* ret = new BYTE[width * height];

	int paddingWidth = width + width % 4;	// each row contains a buffer field
	BYTE* data = new BYTE[paddingWidth];

	/*
		8 bits bitmap image
			  ---0----  ---1---		  --W-2---   ---W-1--
		H-1	- RRRGGGBB, RRRGGGBB, ... RRRGGGBB,  RRRGGGBB
		H-2	- RRRGGGBB, RRRGGGBB, ... RRRGGGBB,  RRRGGGBB
		.
		.
		1	- RRRGGGBB, RRRGGGBB, ... RRRGGGBB,  RRRGGGBB
		0	- RRRGGGBB, RRRGGGBB, ... RRRGGGBB,  RRRGGGBB
	*/

	for (int row = height - 1; row >= 0; row--)
	{
		fread(data, sizeof(BYTE), paddingWidth, file);

		for (int col = 0; col < width; col++)
			ret[row * width + col] = data[col];
	}

	fclose(file);
	return ret;
}

int* Histogram(BYTE* grayImage, int width, int height) {

	int* hist = new int[256]();

	for (int i = 0; i < width * height; i++)
		hist[grayImage[i]]++;

	return hist;
}

void Draw(int* hist) {

	for (int i = 0; i < 256; i++) {
		cout << i << " |";
		for (int j = 0; j < hist[i] / 100; j++)
			cout << "*";
		cout << " " << hist[i] << endl;
	}
}

double Mean(int* hist, int size) {

	double sum = 0.0;
	for (int i = 0; i < 256; i++)
		sum += (double)(i * hist[i]);

	return sum / (double)size;
}

double Variance(int* hist, double mean, int size) {

	double sum = 0.0;
	for (int i = 0; i < 256; i++)
		sum += (pow((i - mean), 2) * (double)hist[i]);


	return sum / (size - 1);
}

int main(int argc, char* argv[]) {

	if (argc == 2) {

		int width, height;
		BYTE* grayImage = ReadGrayBMP(argv[1], width, height);
		int* hist = Histogram(grayImage, width, height);
		Draw(hist);

		double mean = Mean(hist, width * height);
		double var = Variance(hist, mean, width * height);

		cout << endl;
		cout << argv[1] << " " << "Width: " << width << " Height: " << height << endl;
		cout << "Mean: " << mean << " Variance: "<< var << endl;

		delete[] grayImage;
		delete[] hist;
	}
	else
		cout << "You must enter image name" << endl;


	return 0;
}

