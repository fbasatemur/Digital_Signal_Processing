#include <iostream>
#include <fstream>
#include <vector>

#define LITTLE_ENDIAN2B(x,index) ((x[index + 1] << 8) | x[index])
#define LITTLE_ENDIAN4B(x,index) (x[index + 3] << 24) | (x[index + 2] << 16) | (x[index + 1] << 8) | x[index];
#define MIN(a,b) (a<b) ? a : b
#define MAX(a,b) (a>b) ? a : b

using namespace std;

typedef struct {
									// Size   - Beg -> End
	string         chunkID;			// 4 Byte - 0
	unsigned int chunkSize;         // 4 Byte - 4
	string         format;			// 4 Byte - 8

	string         fmtChunkID;		// 4 Byte - 12 
	unsigned int   fmtChunkSize;    // 4 Byte - 16
	unsigned short audioFormat;     // 2 Byte - 20
	unsigned short numChannels;     // 2 Byte - 22
	unsigned int   sampleRate;      // 4 Byte - 24
	unsigned int   byteRate;        // 4 Byte - 28
	unsigned short blockAlign;      // 2 Byte - 32
	unsigned short bps;             // 2 Byte - 34

	string         dataChunkID;		// 4 Byte - 36
	unsigned int   dataChunkSize;   // 4 Byte - 40 -> 44

}WavHeader;

float* DecodeWave(vector<unsigned char>& fileData, WavHeader* header, size_t* numSamples) {

	// CHUNK DESCRIPTOR
	header->chunkID = string(fileData.begin(), fileData.begin() + 4);
	header->chunkSize = LITTLE_ENDIAN4B(fileData, 4);
	header->format = string(fileData.begin() + 8, fileData.begin() + 12);

	// FORMAT CHUNK
	int fmtChunkI = 12;
	header->fmtChunkID = string(fileData.begin() + fmtChunkI, fileData.begin() + fmtChunkI + 4);
	header->fmtChunkSize = LITTLE_ENDIAN4B(fileData, fmtChunkI + 4);
	header->audioFormat = LITTLE_ENDIAN2B(fileData, fmtChunkI + 8);
	header->numChannels = LITTLE_ENDIAN2B(fileData, fmtChunkI + 10);
	header->sampleRate = (unsigned int)LITTLE_ENDIAN4B(fileData, fmtChunkI + 12);
	header->byteRate = LITTLE_ENDIAN4B(fileData, fmtChunkI + 16);	// numBytesPerSecond
	header->blockAlign = LITTLE_ENDIAN2B(fileData, fmtChunkI + 20);
	header->bps = LITTLE_ENDIAN2B(fileData, fmtChunkI + 22);

	if (header->chunkID != "RIFF" || header->format != "WAVE")
		cout << "Not a wav file " << endl;

	if (header->audioFormat != 1)
		cout << "Only PCM encoding supported " << endl;

	if (header->numChannels != 1)
		cout << "Only 1 channel encoding supported " << endl;

	if (header->bps != 16)
		cout << "Only 16 bits encoding supported " << endl;

	// DATA CHUNK
	int dataChunkI = 36;
	header->dataChunkID = string(fileData.begin() + dataChunkI, fileData.begin() + dataChunkI + 4);
	header->dataChunkSize = LITTLE_ENDIAN4B(fileData, dataChunkI + 4);

	*numSamples = header->dataChunkSize / (header->numChannels * header->bps / 8);
	int samplesStartIndex = dataChunkI + 8;

	int sampleIndex;
	float* samples = new float[*numSamples];
	short sampleAsInt;
	float sample;
	for (int i = 0; i < *numSamples; i++)
	{
		sampleIndex = samplesStartIndex + (header->blockAlign * i);

		sampleAsInt = LITTLE_ENDIAN2B(fileData, sampleIndex);
		sample = static_cast<float> (sampleAsInt) / static_cast<float> (32768.);
		samples[i] = sample;
	}

	return samples;
}

float* WavRead(const char* fileName, WavHeader* header, size_t* numSamples)
{
	ifstream file(fileName, std::ios::binary);
	if (!file.is_open()) cout << "Error opening file" << endl;

	vector<unsigned char> fileData;
	file.unsetf(std::ios::skipws);

	file.seekg(0, std::ios::end);
	size_t length = file.tellg();
	file.seekg(0, std::ios::beg);

	fileData.resize(length);
	file.read(reinterpret_cast<char*> (fileData.data()), length);
	file.close();

	// file format WAVE
	return DecodeWave(fileData, header, numSamples);
}

void AddStringToFile(vector<unsigned char>& fileData, std::string s) {
	for (size_t i = 0; i < s.length(); i++)
		fileData.push_back((unsigned char)s[i]);
}

void AddInt4BToFile(vector<unsigned char>& fileData, int i)
{
	unsigned char bytes[4];

	bytes[3] = (i >> 24) & 0xFF;
	bytes[2] = (i >> 16) & 0xFF;
	bytes[1] = (i >> 8) & 0xFF;
	bytes[0] = i & 0xFF;

	for (int i = 0; i < 4; i++)
		fileData.push_back(bytes[i]);
}

void AddInt2BToFile(vector<unsigned char>& fileData, short i)
{
	unsigned char bytes[2];

	bytes[1] = (i >> 8) & 0xFF;
	bytes[0] = i & 0xFF;

	fileData.push_back(bytes[0]);
	fileData.push_back(bytes[1]);
}

void WavSave(const char* fileName, WavHeader* header, size_t numSamples, float* samples)
{
	vector<unsigned char> fileData;

	int dataChunkSize = numSamples * (header->numChannels * header->bps / 8);
	int formatChunkSize = 16;
	int fileSizeInBytes = 4 + formatChunkSize + 8 + 8 + dataChunkSize;

	// HEADER CHUNK
	AddStringToFile(fileData, "RIFF");
	AddInt4BToFile(fileData, fileSizeInBytes);
	AddStringToFile(fileData, "WAVE");

	// FORMAT CHUNK
	AddStringToFile(fileData, "fmt ");
	AddInt4BToFile(fileData, formatChunkSize); // format chunk size (16 for PCM)
	AddInt2BToFile(fileData, header->audioFormat); // audio format
	AddInt2BToFile(fileData, header->numChannels); // num channels
	AddInt4BToFile(fileData, header->sampleRate); // sample rate

	int numBytesPerSecond = (int)((header->numChannels * header->sampleRate * header->bps) / 8);
	AddInt4BToFile(fileData, numBytesPerSecond);

	short numBytesPerBlock = header->numChannels * (header->bps / 8);
	AddInt2BToFile(fileData, numBytesPerBlock);
	AddInt2BToFile(fileData, (short)header->bps);

	// DATA CHUNK
	AddStringToFile(fileData, "data");
	AddInt4BToFile(fileData, dataChunkSize);

	short sampleAsInt;
	for (size_t i = 0; i < numSamples; i++)
	{
		samples[i] = MIN(samples[i], 1.0);
		samples[i] = MAX(samples[i], -1.0);
		sampleAsInt = static_cast<short> (samples[i] * 32767.);
		AddInt2BToFile(fileData, sampleAsInt);
	}

	ofstream outputFile(fileName, ios::binary);

	if (outputFile.is_open())
	{
		char value;
		for (size_t i = 0; i < fileData.size(); i++)
		{
			value = (char)fileData[i];
			outputFile.write(&value, sizeof(char));
		}

		outputFile.close();
	}
}