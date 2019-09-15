#include"Bitmap.h"
#include<iostream>
using namespace std;

void readBMP(const char* filePath, BitMap &header, char* &data)
{
	FILE* f = fopen(filePath, "rb");
	if (!f)
	{
		printf("Cannot open file for reading!!!");
		exit(-1);
	}

	fread(&header, sizeof(header), 1, f);
	/*
	Tham so 1 : Du lieu luu vao
	Tham so 2 : size cua moi phan tu
	tham so 3 : so luong phan tu can doc
	tham so 4 : file doc
	Khi ghi nhut tren nghia la doc 1 phat het cai f vi dung luong cua f = header(bitmap) t
	*/

	int _padding = header.m_width % 4;
	int _size = header.m_width * header.m_height * (header.m_bpp / 8) + _padding * header.m_height; //(header.m_bpp)/8 ( số kênh màu )

	data = new char[_size];
	fseek(f, header.m_dataOffSet, SEEK_SET);
	fread(data, sizeof(char), _size, f);

	fclose(f);
}


void writeBMP(const char* filePath, BitMap &header, char* &data)
{
	FILE* f = fopen(filePath, "wb");
	if (!f)
	{
		printf("Cannot open file for writing!!!");
		exit(-1);
	}

	fwrite(&header, sizeof(header), 1, f);

	int _padding = header.m_width % 4;
	int _size = header.m_width * header.m_height * (header.m_bpp / 8) + _padding * header.m_height;
	fwrite(data, sizeof(char), _size, f);

	fclose(f);
}

Pix* convertDataToPixelArray(char* &data, BitMap &header)
{
	int _size = header.m_width * header.m_height;
	Pix* _pixels = new Pix[_size];

	int _padding = header.m_width % 4;

	char* _temp = data;

	// 5 dong 3 cot
	// 0 1 2 
	// 
	for (int i = 0; i < header.m_height; i++)
	{
		for (int j = 0; j < header.m_width; j++)
		{
			_pixels[i * header.m_width + j].B = *(_temp++);
			_pixels[i * header.m_width + j].G = *(_temp++);
			_pixels[i * header.m_width + j].R = *(_temp++);
		}

		_temp += _padding;
	}

	return _pixels;
}

char* convertPixelArrayToData(Pix* &pixels, BitMap &header)
{
	int _padding = header.m_width % 4;
	int _size = header.m_width * header.m_height * (header.m_bpp / 8) + _padding * header.m_height;

	char* _data = new char[_size];
	char* _temp = _data;

	for (int i = 0; i < header.m_height; i++)
	{
		for (int j = 0; j < header.m_width; j++)
		{
			*(_temp++) = pixels[i * header.m_width + j].B;
			*(_temp++) = pixels[i * header.m_width + j].G;
			*(_temp++) = pixels[i * header.m_width + j].R;
		}

		for (int k = 0; k < _padding; k++)
		{
			*(_temp++) = 0;
		}
	}

	return _data;
}
