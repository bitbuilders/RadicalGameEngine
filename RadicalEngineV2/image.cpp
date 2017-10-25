#include "stdafx.h"
#include "image.h"
#include <string>
#include <fstream>

const unsigned char * Image::LoadBMP(const std::string & filename, int & width, int & height, int & bpp)
{
	FILE* file;
	errno_t err = fopen_s(&file, filename.c_str(), "rb");

	if (err != 0)
	{
		printf("FILE FAILED TO OPEN. BMP INVALID!");
		return nullptr;
	}

	if (file)
	{
		//FILE* file = fopen(filename.c_str(), "rb");
		unsigned char header[54];
		fread_s(header, sizeof(header), sizeof(unsigned char), 54, file);
		//fread(header, sizeof(unsigned char), 54, file);

		width = *(int*)&(header[18]);
		height = *(int*)&(header[22]);
		bpp = *(int*)&(header[28]);

		const int bytesPerPixel = 4;
		int size = bytesPerPixel * width * height;
		unsigned char* data = new unsigned char[size];
		fread_s(data, sizeof(unsigned char) * size, sizeof(unsigned char), size, file);
		//fread(data, sizeof(unsigned char), size, file);
		fclose(file);

		//for (int i = 0; i < size; i += 3)
		//{
		//	unsigned char tmp = data[i];
		//	data[i] = data[i + 2];
		//	data[i + 2] = tmp;
		//}

		return data;
	}
	else
	{
		return nullptr;
	}
}
