#include "Utils.h"
#include <iostream>

int Utils::readData(const char *fileName, unsigned char *&buf)
{
	const char *MODE = "rb";
	FILE *pFile = 0;
	fopen_s(&pFile, fileName, MODE);

	fseek(pFile, 0, SEEK_END);
	long fSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	buf = (unsigned char *)malloc(fSize);

	int numRead = 0;
	while (numRead != fSize)
	{
		numRead = fread(&buf[numRead], 1, fSize, pFile);
	}

	fclose(pFile);

	return fSize;
}