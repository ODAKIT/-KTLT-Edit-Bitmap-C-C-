#include"ProcessImage.h"
#include<algorithm>
#include<iostream>
#include<iostream>
#include<string>
#include <cmath>
#include<vector>
using namespace std;

//===============Chuc nang anh trang den===============
void grayscale(Pix* &pixels, int size)
{
	for (int i = 0; i < size; i++)
	{
		int _val = (pixels[i].R + pixels[i].G + pixels[i].B) / 3;
		pixels[i].R = pixels[i].G = pixels[i].B = _val;
	}
}

void grayscaleArea(Pix* &pixels , int mousex , int mousey , BitMap header)
{

	int width = header.m_width;
	for (int i = mousey; i <= mousey +200; i++)
	{
		for (int j = mousex; j <= mousex + 200; j++)
		{
			int _val = (pixels[i * width + j].R + pixels[i * width + j].G + pixels[i * width + j].B) / 3;
			pixels[i * width + j].R = pixels[i * width + j].G = pixels[i * width + j].B = _val;
		}
	}
}

//===============Chuc nang Dao anh doc===============

void DaoAnhDoc(Pix* &pixels, int size)
{
	for (int i = 0; i < size / 2; i++)
	{
		unsigned char temp1 = pixels[i].B;
		pixels[i].B = pixels[size - 1 - i].B;
		pixels[size - 1 - i].B = temp1;
		temp1 = pixels[i].G;
		pixels[i].G = pixels[size - 1 - i].G;
		pixels[size - 1 - i].G = temp1;
		temp1 = pixels[i].R;
		pixels[i].R = pixels[size - 1 - i].R;
		pixels[size - 1 - i].R = temp1;
	}
}

void DaoAnhDocArea(Pix* &pixels, int mousex, int mousey, BitMap header)
{

	int width = header.m_width;
	int count = mousey + 200;
	for (int i = mousey; i <= (mousey + 100); i++)
	{
		for (int j = mousex; j <= mousex + 200; j++)
		{
			unsigned char temp1 = pixels[i*width+j].B;
			pixels[i*width+j].B = pixels[count*width + j].B;
			pixels[count*width + j].B = temp1;
			temp1 = pixels[i*width + j].G;
			pixels[i*width + j].G = pixels[count*width + j].G;
			pixels[count*width + j].G = temp1;
			temp1 = pixels[i*width + j].R;
			pixels[i*width + j].R = pixels[count*width + j].R;
			pixels[count*width + j].R = temp1;
		}
		count--;
	}
}

//===============Chuc nang Blur(Lam mo` anh)===============

void BlurImage(Pix *&_pixels, BitMap _header)
{

	for (int i = 0; i < _header.m_height; i++)
	{
		for (int j = 0; j < _header.m_width; j++)
		{
			float Red = 0, Blue = 0, Green = 0;
			//Dong dau tien.
			if (i == 0)
			{
				if (j == 0)
				{
					Red += _pixels[i*_header.m_width + j].R + _pixels[(i + 1)*_header.m_width + j].R + _pixels[(i + 1)*_header.m_width + j + 1].R + _pixels[i *_header.m_width + j + 1].R;
					Blue += _pixels[(i + 1)*_header.m_width + j].B + _pixels[i*_header.m_width + j].B + _pixels[i *_header.m_width + j + 1].B + _pixels[(i + 1)*_header.m_width + j + 1].B;
					Green += _pixels[(i + 1)*_header.m_width + j].G + _pixels[(i + 1)*_header.m_width + j + 1].G + _pixels[i *_header.m_width + j + 1].G + _pixels[i*_header.m_width + j].G;
					Red = (float)Red / 4;
					Green = (float)Green / 4;
					Blue = (float)Blue / 4;
				}
				else if (j == _header.m_width - 1)
				{
					Red += _pixels[i*_header.m_width + j].R + _pixels[(i + 1)*_header.m_width + j].R + _pixels[(i + 1)*_header.m_width + j - 1].R + _pixels[i *_header.m_width + j - 1].R;
					Green += _pixels[(i + 1)*_header.m_width + j].G + _pixels[i*_header.m_width + j].G + _pixels[(i + 1)*_header.m_width + j - 1].G + _pixels[i *_header.m_width + j - 1].G;
					Blue += _pixels[(i + 1)*_header.m_width + j - 1].B + _pixels[i *_header.m_width + j - 1].B + _pixels[(i + 1)*_header.m_width + j].B + _pixels[i*_header.m_width + j].B;
					Red = (float)Red / 4;
					Green = (float)Green / 4;
					Blue = (float)Blue / 4;
				}
				else
				{
					Red += _pixels[i*_header.m_width + j].R + +_pixels[i *_header.m_width + j + 1].R + _pixels[i *_header.m_width + j - 1].R + _pixels[(i + 1)*_header.m_width + j + 1].R + _pixels[(i + 1)*_header.m_width + j].R + _pixels[(i + 1)*_header.m_width + j - 1].R;
					Green += _pixels[(i + 1)*_header.m_width + j].G + _pixels[(i + 1)*_header.m_width + j + 1].G + _pixels[i *_header.m_width + j + 1].G + _pixels[(i + 1)*_header.m_width + j - 1].G + _pixels[i *_header.m_width + j - 1].G + _pixels[i*_header.m_width + j].G;
					Blue += +_pixels[(i + 1)*_header.m_width + j - 1].B + _pixels[i *_header.m_width + j - 1].B + _pixels[(i + 1)*_header.m_width + j + 1].B + _pixels[i *_header.m_width + j + 1].B + _pixels[(i + 1)*_header.m_width + j].B + +_pixels[i*_header.m_width + j].B;
					Red = (float)Red / 6;
					Green = (float)Green / 6;
					Blue = (float)Blue / 6;
				}
			}

			// Hang cuoi cung
			else if (i == _header.m_height - 1)
			{
				if (j == 0)
				{
					Red = _pixels[i*_header.m_width + j].R + _pixels[(i - 1)*_header.m_width + j].R + _pixels[(i - 1)*_header.m_width + j - 1].R + _pixels[i *_header.m_width + j + 1].R;
					Green = _pixels[i*_header.m_width + j].G + _pixels[(i - 1)*_header.m_width + j].G + _pixels[(i - 1)*_header.m_width + j - 1].G + _pixels[i *_header.m_width + j + 1].G;
					Blue = _pixels[i*_header.m_width + j].B + _pixels[(i - 1)*_header.m_width + j].B + _pixels[(i - 1)*_header.m_width + j - 1].B + _pixels[i *_header.m_width + j + 1].B;
					Red = (float)Red / 4;
					Green = (float)Green / 4;
					Blue = (float)Blue / 4;
				}
				else if (j == _header.m_width - 1)
				{
					Red = _pixels[i*_header.m_width + j].R + _pixels[(i - 1)*_header.m_width + j].R + _pixels[(i - 1)*_header.m_width + j - 1].R + _pixels[i *_header.m_width + j - 1].R;
					Green = _pixels[i*_header.m_width + j].G + _pixels[(i - 1)*_header.m_width + j].G + _pixels[(i - 1)*_header.m_width + j - 1].G + _pixels[i *_header.m_width + j - 1].G;
					Blue = _pixels[i*_header.m_width + j].B + _pixels[(i - 1)*_header.m_width + j].B + _pixels[(i - 1)*_header.m_width + j - 1].B + _pixels[i *_header.m_width + j - 1].B;
					Red = (float)Red / 4;
					Green = (float)Green / 4;
					Blue = (float)Blue / 4;

				}
				else
				{
					Red = _pixels[i*_header.m_width + j].R + _pixels[(i - 1)*_header.m_width + j].R + _pixels[(i - 1)*_header.m_width + j - 1].R + _pixels[i *_header.m_width + j - 1].R + _pixels[i *_header.m_width + j + 1].R + _pixels[(i - 1)*_header.m_width + j - 1].R;
					Green = _pixels[i*_header.m_width + j].G + _pixels[(i - 1)*_header.m_width + j].G + _pixels[(i - 1)*_header.m_width + j - 1].G + _pixels[i *_header.m_width + j - 1].G + _pixels[(i - 1)*_header.m_width + j - 1].G + _pixels[i *_header.m_width + j + 1].G;
					Blue = _pixels[i*_header.m_width + j].B + _pixels[(i - 1)*_header.m_width + j].B + _pixels[(i - 1)*_header.m_width + j - 1].B + _pixels[i *_header.m_width + j - 1].B + _pixels[(i - 1)*_header.m_width + j - 1].B + _pixels[i *_header.m_width + j + 1].B;
					Red = (float)Red / 6;
					Green = (float)Green / 6;
					Blue = (float)Blue / 6;
				}
			}
			// Cac hang chinh giua
			else
			{
				if (j == 0)
				{
					Red += _pixels[i*_header.m_width + j].R + _pixels[(i - 1)*_header.m_width + j].R + _pixels[(i - 1)*_header.m_width + j + 1].R + _pixels[i *_header.m_width + j + 1].R + _pixels[(i + 1)*_header.m_width + j + 1].R + _pixels[(i + 1) *_header.m_width + j].R;
					Green += _pixels[i*_header.m_width + j].G + _pixels[(i - 1)*_header.m_width + j].G + _pixels[(i - 1)*_header.m_width + j - 1].G + _pixels[i *_header.m_width + j + 1].G + _pixels[(i + 1)*_header.m_width + j + 1].G + _pixels[(i + 1) *_header.m_width + j].G;
					Blue += _pixels[i*_header.m_width + j].B + _pixels[(i - 1)*_header.m_width + j].B + _pixels[(i - 1)*_header.m_width + j - 1].B + _pixels[i *_header.m_width + j + 1].B + _pixels[(i + 1)*_header.m_width + j + 1].B + _pixels[(i + 1) *_header.m_width + j].B;
					Red = (float)Red / 6;
					Green = (float)Green / 6;
					Blue = (float)Blue / 6;
				}
				else if (j == _header.m_width - 1)
				{
					Red += _pixels[i*_header.m_width + j].R + _pixels[(i - 1)*_header.m_width + j].R + _pixels[(i - 1)*_header.m_width + j - 1].R + _pixels[i *_header.m_width + j - 1].R + _pixels[(i + 1)*_header.m_width + j - 1].R + _pixels[(i + 1) *_header.m_width + j].R;
					Green += _pixels[i*_header.m_width + j].G + _pixels[(i - 1)*_header.m_width + j].G + _pixels[(i - 1)*_header.m_width + j - 1].G + _pixels[i *_header.m_width + j - 1].G + _pixels[(i + 1)*_header.m_width + j - 1].G + _pixels[(i + 1) *_header.m_width + j].G;
					Blue += _pixels[i*_header.m_width + j].B + _pixels[(i - 1)*_header.m_width + j].B + _pixels[(i - 1)*_header.m_width + j - 1].B + _pixels[i *_header.m_width + j - 1].B + _pixels[(i + 1)*_header.m_width + j - 1].B + _pixels[(i + 1) *_header.m_width + j].B;
					Red = (float)Red / 6;
					Green = (float)Green / 6;
					Blue = (float)Blue / 6;
				}


				else
				{
					Red += _pixels[i*_header.m_width + j].R + _pixels[(i - 1)*_header.m_width + j].R + _pixels[(i - 1)*_header.m_width + j - 1].R + _pixels[i *_header.m_width + j - 1].R + _pixels[(i + 1)*_header.m_width + j - 1].R + _pixels[(i + 1) *_header.m_width + j].R + _pixels[(i + 1) *_header.m_width + j + 1].R + _pixels[i *_header.m_width + j + 1].R + _pixels[(i + 1) *_header.m_width + j + 1].R;
					Green += _pixels[i*_header.m_width + j].G + _pixels[(i - 1)*_header.m_width + j].G + _pixels[(i - 1)*_header.m_width + j - 1].G + _pixels[i *_header.m_width + j - 1].G + _pixels[(i + 1)*_header.m_width + j - 1].G + _pixels[(i + 1) *_header.m_width + j].G + _pixels[(i + 1) *_header.m_width + j + 1].R + _pixels[i *_header.m_width + j + 1].G + _pixels[(i + 1) *_header.m_width + j + 1].G;
					Blue += _pixels[i*_header.m_width + j].B + _pixels[(i - 1)*_header.m_width + j].B + _pixels[(i - 1)*_header.m_width + j - 1].B + _pixels[i *_header.m_width + j - 1].B + _pixels[(i + 1)*_header.m_width + j - 1].B + _pixels[(i + 1) *_header.m_width + j].B + _pixels[(i + 1) *_header.m_width + j + 1].B + _pixels[i *_header.m_width + j + 1].B + _pixels[(i + 1) *_header.m_width + j + 1].B;
					Red = (float)Red / 9;
					Green = (float)Green / 9;
					Blue = (float)Blue / 9;
				}
			}
			_pixels[i*_header.m_width + j].R = Red;
			_pixels[i*_header.m_width + j].G = Green;
			_pixels[i*_header.m_width + j].B = Blue;
		}
	}
}

//===============Dieu chinh anh theo bo loc tuy y===============

void ProcessImageWithFilter(Pix *&_pixels, double filter[][3], BitMap _header)
{
	int filterWidth = 3;
	int filterHeight = 3;
	int w = _header.m_width;
	int h = _header.m_height;
	Pix *result = new Pix[w*h];
	//double filter[3][3] = { {-1, -1, -1}, { -1,9,-1 }, { -1,-1,-1 } };

	double factor = 1.0;
	double bias = 0.0;

	//Color[, ] result = new Color[img.Width, img.Height];
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			double red = 0.0, green = 0.0, blue = 0.0;


			for (int filterX = 0; filterX < filterWidth; filterX++)
			{
				for (int filterY = 0; filterY < filterHeight; filterY++)
				{
					int imageX = (y - filterWidth / 2 + filterX + h) % h;
					int imageY = (x - filterHeight / 2 + filterY + w) % w;

					//Color imageColor = img.GetPixel(imageX, imageY);
					Pix imageColor = _pixels[imageX*_header.m_width + imageY];
					red += imageColor.R * filter[filterX][filterY];
					green += imageColor.G * filter[filterX][filterY];
					blue += imageColor.B * filter[filterX][filterY];

				}

				int r = min(max((int)(factor * red + bias), 0), 255);
				int g = min(max((int)(factor * green + bias), 0), 255);
				int b = min(max((int)(factor * blue + bias), 0), 255);

				result[y*w + x].R = r;
				result[y*w + x].G = g;
				result[y*w + x].B = b;


			}
		}
	}

	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			if (result[i*w + j].R == 0 && result[i*w + j].G == 0 && result[i*w + j].B == 0)
			{
				continue;
			}
			else
			{
				_pixels[i*w + j] = result[i*w + j];
			}
		}
	}


}


//===============Chuc nang tang do sang cua anh===============

void Birghtness(Pix *&_pixels, BitMap _header)
{
	for (int i = 0; i < _header.m_width*_header.m_height; i++)
	{

		if (_pixels[i].R + 50 > 255)
		{
			_pixels[i].R = 255;
		}
		else
			_pixels[i].R += 50;

		if (_pixels[i].B + 50 > 255)
		{
			_pixels[i].B = 255;
		}
		else
			_pixels[i].B += 50;

		if (_pixels[i].G + 50 > 255)
		{
			_pixels[i].G = 255;
		}
		else
			_pixels[i].G += 50;

	}
}

void Birghtness2(Pix *&_pixels, BitMap _header)
{
	for (int i = 0; i < _header.m_width*_header.m_height; i++)
	{

		if (_pixels[i].R + 100 > 255)
		{
			_pixels[i].R = 255;
		}
		else
			_pixels[i].R += 100;

		if (_pixels[i].B + 100 > 255)
		{
			_pixels[i].B = 255;
		}
		else
			_pixels[i].B += 100;

		if (_pixels[i].G + 100 > 255)
		{
			_pixels[i].G = 255;
		}
		else
			_pixels[i].G += 100;

	}
}




//============Chuc nang chinh anh theo mau RBG=================
                   // 1.Chinh anh theo Red
void editRedColorLevel1(Pix *&_pixels, BitMap _header)
{
	for (int i = 0; i < _header.m_width*_header.m_height; i++)
	{

		if (_pixels[i].R + 50 > 255)
		{
			_pixels[i].R = 255;
		}
		else
			_pixels[i].R += 50;
	}
}

void editRedColorLevel2(Pix *&_pixels, BitMap _header)
{
	for (int i = 0; i < _header.m_width*_header.m_height; i++)
	{

		if (_pixels[i].R + 100 > 255)
		{
			_pixels[i].R = 255;
		}
		else
			_pixels[i].R += 100;
	}
}

void editRedColorLevel3(Pix *&_pixels, BitMap _header)
{
	for (int i = 0; i < _header.m_width*_header.m_height; i++)
	{

		if (_pixels[i].R + 130 > 255)
		{
			_pixels[i].R = 255;
		}
		else
			_pixels[i].R += 130;
	}
}

                    //2.Chinh Theo Blue

void editBlueColorLevel1(Pix *&_pixels, BitMap _header)
{
	for (int i = 0; i < _header.m_width*_header.m_height; i++)
	{

		if (_pixels[i].B + 50 > 255)
		{
			_pixels[i].B = 255;
		}
		else
			_pixels[i].B += 50;
	}
}

void editBlueColorLevel2(Pix *&_pixels, BitMap _header)
{
	for (int i = 0; i < _header.m_width*_header.m_height; i++)
	{

		if (_pixels[i].B + 100 > 255)
		{
			_pixels[i].B = 255;
		}
		else
			_pixels[i].B += 100;
	}
}

void editBlueColorLevel3(Pix *&_pixels, BitMap _header)
{
	for (int i = 0; i < _header.m_width*_header.m_height; i++)
	{

		if (_pixels[i].B + 130 > 255)
		{
			_pixels[i].B = 255;
		}
		else
			_pixels[i].B += 130;
	}
}



                     //3.Theo Green

void editGreenColorLevel1(Pix *&_pixels, BitMap _header)
{
	for (int i = 0; i < _header.m_width*_header.m_height; i++)
	{

		if (_pixels[i].G + 50 > 255)
		{
			_pixels[i].G = 255;
		}
		else
			_pixels[i].G += 50;
	}
}

void editGreenColorLevel2(Pix *&_pixels, BitMap _header)
{
	for (int i = 0; i < _header.m_width*_header.m_height; i++)
	{

		if (_pixels[i].G + 100 > 255)
		{
			_pixels[i].G = 255;
		}
		else
			_pixels[i].G += 100;
	}
}

void editGreenColorLevel3(Pix *&_pixels, BitMap _header)
{
	for (int i = 0; i < _header.m_width*_header.m_height; i++)
	{

		if (_pixels[i].G + 130 > 255)
		{
			_pixels[i].G = 255;
		}
		else
			_pixels[i].G += 130;
	}
}



#pragma pack(pop)


//chuyển đổi giá trị màu RGB
void Swap(Pix*& pixels, int size)
{
	for (int i = 0; i < size; i++)
	{
		//1. R G B
		//2. G B R
		//3. B R G

		pixels[i].B = pixels[i].R;
		pixels[i].G = pixels[i].G;
		pixels[i].R = pixels[i].B;
	}
}



//hàm lấy nhị phân của một kí tự
string getBin(char s) {

	if (s == ' ')
		return "0100000";

	char out[9];

	int k = (int)s;
	_itoa(k, out, 2);

	return out;
}


//hàm chuyển một string thành mã nhị phân
string getStrBin(string str) {
	string out = "";
	for (int i = 0; i < str.length(); i++) {
		string temp = getBin(str[i]);
		out += temp;
	}
	return out;
}


//hàm chèn text vào 1 ảnh
void changeBit(Pix * &pixels, int size, string bin)
{
	int z = 0;

	for (int i = 0; i < size; i++)
	{
		if (z >= bin.length()) {
			return;
		}

		else {
			if (z < bin.length()) {
				if ((bin[z] - 48) % 2) {
					if (pixels[i].B % 2 == 0) {
						pixels[i].B -= 1;
					}
				}
				else {
					if (pixels[i].B % 2) {
						pixels[i].B -= 1;
					}
				}
				z++;
			}

			if (z < bin.length()) {
				if ((bin[z] - 48) % 2) {
					if (pixels[i].G % 2 == 0) {
						pixels[i].G -= 1;
					}
				}
				else {
					if (pixels[i].G % 2) {
						pixels[i].G -= 1;
					}
				}
				z++;
			}

			if (z < bin.length()) {
				if ((bin[z] - 48) % 2) {
					if (pixels[i].R % 2 == 0) {
						pixels[i].R -= 1;
					}
				}
				else {
					if (pixels[i].R % 2) {
						pixels[i].R -= 1;
					}
				}
				z++;
			}
		}
	}
}




//hàm giải mã
string decryptionMBP(Pix * &pixels, int size, int length)
{
	string k = "";
	int z = 0;

	for (int i = 0; i < size; i++)
	{
		if (z < length) {
			if (pixels[i].B % 2) {
				k += "1";
			}
			else
				k += "0";
			z++;
		}

		if (z < length) {
			if (pixels[i].G % 2) {
				k += "1";
			}
			else
				k += "0";
			z++;
		}

		if (z < length) {
			if (pixels[i].R % 2) {
				k += "1";
			}
			else
				k += "0";
			z++;
		}
	}
	return k;
}



//======================Tăng độ tương phản=================
void constrast(Pix * &pixels, int size, int nContrast)
{
	if (nContrast < -100 || nContrast > 100)
		return;
	else {
		double zkc = (100.0 + nContrast) / 100.0;
		for (int i = 0; i < size; i++)
		{
			double temp1;
			double temp2;
			double temp3;

			temp1 = pixels[i].B / 255.0;
			temp2 = pixels[i].G / 255.0;
			temp3 = pixels[i].R / 255.0;

			temp1 -= 0.5;
			temp2 -= 0.5;
			temp3 -= 0.5;

			temp1 *= zkc;
			temp2 *= zkc;
			temp3 *= zkc;


			temp1 += 0.5;
			temp2 += 0.5;
			temp3 += 0.5;

			temp1 *= 255;
			temp2 *= 255;
			temp3 *= 255;

			if (temp1 < 0)
				temp1 = 0;
			if (temp2 < 0)
				temp2 = 0;
			if (temp3 < 0)
				temp3 = 0;

			if (temp1 > 255)
				temp1 = 255;
			if (temp2 > 255)
				temp2 = 255;
			if (temp3 > 255)
				temp3 = 255;


			pixels[i].B = temp1;
			pixels[i].G = temp2;
			pixels[i].R = temp3;

		}
	}
}

struct ConvMatrix {
	int topLeft, topMid, topRight, midLeft, pixel, midRight, botLeft, botMid, botRight;
	int factor, offset;
};



//hàm Julia set


//hàm getPix
void get_pixel(const unsigned int x, const unsigned int y,
	unsigned char& red,
	unsigned char& green,
	unsigned char& blue,
	Pix *_pixels,
	BitMap _header)
{
	const unsigned int y_offset = y * _header.m_width;
	const unsigned int x_offset = x * 24;

	blue = _pixels[y_offset + x_offset].B;
	green = _pixels[y_offset + x_offset].G;
	red = _pixels[y_offset + x_offset].R;
}


//hàm ám vàng ảnh
void sepiaConvert(Pix*& _pixels, BitMap _header) {
	for (int i = 0; i < _header.m_height; i++) {
		for (int j = 0; j < _header.m_width; j++) {
			Pix temp = _pixels[i * _header.m_width + j];

			temp.R = (int)(0.393 * _pixels[i * _header.m_width + j].R + 0.769 * _pixels[i * _header.m_width + j].G + 0.189 * _pixels[i * _header.m_width + j].B);
			temp.G = (int)(0.349 * _pixels[i * _header.m_width + j].R + 0.686 * _pixels[i * _header.m_width + j].G + 0.168 * _pixels[i * _header.m_width + j].B);
			temp.B = (int)(0.272 * _pixels[i * _header.m_width + j].R + 0.534 * _pixels[i * _header.m_width + j].G + 0.131 * _pixels[i * _header.m_width + j].B);

			if (temp.B > 255)
				temp.B = 255;
			if (temp.G > 255)
				temp.G = 255;
			if (temp.R > 255)
				temp.R = 255;

			_pixels[i * _header.m_width + j] = temp;

		}
	}
}



//hàm twirl
void twirl(Pix*& _pixels, BitMap _header) {
	Pix* out = new Pix[_header.m_height * _header.m_width];

	for (int y = 0; y < _header.m_height; y++) {
		for (int x = 0; x < _header.m_width; x++) {
			int yDif = y - _header.m_height / 2;
			int xDif = x - _header.m_width / 2;
			int rotation = 100 * (3.141592654 / 180);

			double radian = sqrt(yDif * yDif + xDif * xDif);
			double cal = atan2(yDif, xDif) + rotation * (((_header.m_height / 2) - radian) / (_header.m_height / 2));

			int rotationY = (_header.m_height / 2) + radian * sin(cal);
			int rotationX = (_header.m_width / 2) + radian * cos(cal);

			if (rotationY > _header.m_height - 1)
				rotationY = _header.m_height - 1;
			else {
				if (rotationY < 0)
					rotationY = 0;
			}

			if (rotationX > _header.m_width - 1)
				rotationX = _header.m_width - 1;
			else {
				if (rotationX < 0)
					rotationX = 0;
			}

			out[y * _header.m_width + x] = _pixels[rotationY * _header.m_width + rotationX];
		}
	}
	_pixels = out;
}

//hàm neo noir
void neonoir(Pix*& _pixels, BitMap _header) {
	Pix* out = new Pix[_header.m_height * _header.m_width];
	out = _pixels;

	for (int y = 0; y < _header.m_height; y++) {
		for (int x = 0; x < _header.m_width; x++) {
			double sum = out[y * _header.m_width + x].B + out[y * _header.m_width + x].G + out[y * _header.m_width + x].R + 0.0001;
			int r = out[y * _header.m_width + x].R;
			int g = out[y * _header.m_width + x].G;
			int b = out[y * _header.m_width + x].B;

			if ((r / sum > 0.7 && r > 20) || (r > 140 && g < 100 && b < 100) || (r > 200 && g < 150 && b < 150)) {
				out[y * _header.m_width + x].R = out[y * _header.m_width + x].R;
				out[y * _header.m_width + x].G = 0;
				out[y * _header.m_width + x].B = 0;
			}
			else {
				if (sum > 400) {
					out[y * _header.m_width + x].R = out[y * _header.m_width + x].G = out[y * _header.m_width + x].B = 255;
				}
				else {
					out[y * _header.m_width + x].R = out[y * _header.m_width + x].G = out[y * _header.m_width + x].B = 0;
				}
			}
		}
	}

	for (int y = 1; y < _header.m_height - 1; y++) {
		for (int x = 1; x < _header.m_width - 1; x++) {
			double sum = 0;
			for (int ky = -1; ky <= 1; ky++) {
				for (int kx = -1; kx <= 1; kx++) {
					sum += out[(y + ky) * _header.m_width + (x + kx)].R + out[(y + ky) * _header.m_width + (x + kx)].G + out[(y + ky) * _header.m_width + (x + kx)].B;
				}
			}
			if (out[y * _header.m_width + x].R > out[y * _header.m_width + x].G + out[y * _header.m_width + x].B) {
				sum = 0;
			}
			else {
				//chuyển xám giữa 3 và 6 pixels xung quanh tâm
				if (sum > 3 * 3 * 255 && sum < 6 * 3 * 255)
					out[y * _header.m_width + x].R = out[y * _header.m_width + x].G = out[y * _header.m_width + x].B = 127;
			}
		}
	}

	_pixels = out;
}


void readBMPtext(const char* filePath, BitMap & header, char*& data, int& length)
{
	FILE* f = fopen(filePath, "rb");
	if (!f)
	{
		printf("Cannot open file for reading!!!");
		exit(-1);
	}

	fread(&header, sizeof(header), 1, f);

	//if (header.m_signature[0] != 'B' || header.m_signature[1] != 'M')
	//	return;

	//if (header.m_bpp != 24 || header.m_height < 0)
	//	return;

	length = header.m_reserved2;

	int _padding = header.m_width % 4;
	int _size = header.m_width * header.m_height * (header.m_bpp / 8) + _padding * header.m_height; //(header.m_bpp)/8 ( số kênh màu )

	data = new char[_size];
	fread(data, sizeof(char), _size, f);

	fclose(f);
}


void writeBMPtext(const char* filePath, BitMap & header, char*& data, string bin)
{
	FILE* f = fopen(filePath, "wb");
	if (!f)
	{
		printf("Cannot open file for writing!!!");
		exit(-1);
	}

	header.m_reserved2 = bin.length();

	fwrite(&header, sizeof(header), 1, f);

	int _padding = header.m_width % 4;
	int _size = header.m_width * header.m_height * (header.m_bpp / 8) + _padding * header.m_height;

	fwrite(data, sizeof(char), _size, f);

	fclose(f);
}








//Hàm tham khảo do các bạn làm nhưng thực dụng không cao

// Fillter
// 1. Red
// 2. Green
// 3. Blue
void fillterColor(Pix*& pixels, int size, int k)
{
	for (int i = 0; i < size; i++)
	{
		switch (k) {
		case 3:
			pixels[i].B = pixels[i].B;
			pixels[i].G = 255 - pixels[i].G;
			pixels[i].R = 255 - pixels[i].R;
			break;
		case 2:
			pixels[i].B = 255 - pixels[i].B;
			pixels[i].G = pixels[i].G;
			pixels[i].R = 255 - pixels[i].R;
			break;
		case 1:
			pixels[i].B = 255 - pixels[i].B;
			pixels[i].G = 255 - pixels[i].G;
			pixels[i].R = pixels[i].R;
			break;
		default:
			cout << "Something went wrong ! Please try again ! " << endl;
			system("pause");
		}
	}
}



void juliaSet(Pix*& pixels, BitMap _header, unsigned int max_iterations) {

	max_iterations = 150;

	const double cr = -0.70000;
	const double ci = 0.27015;

	double prevr, previ;

	for (unsigned int y = 0; y < _header.m_height - 3; ++y)
	{
		for (unsigned int x = 0; x < _header.m_width - 3; ++x)
		{
			double nextr = 1.5 * (2.0 * x / _header.m_width - 1.0);
			double nexti = (2.0 * y / _header.m_height - 1.0);

			for (unsigned int i = 0; i < max_iterations; ++i)
			{
				prevr = nextr;
				previ = nexti;

				nextr = prevr * prevr - previ * previ + cr;
				nexti = 2 * prevr * previ + ci;

				if (((nextr * nextr) + (nexti * nexti)) > 4)
				{
					Pix p = hsv_colormap[static_cast<int>((1000.0 * i) / max_iterations)];

					pixels[y * _header.m_width + x] = p;

					break;
				}
			}
		}
	}
}




//hàm chèn text vào ảnh - mọi chuyện đều ổn cho tới khi tích hợp với giao diện thì lỗi , nên đưa vào tham khảo
void insertTextToPic(Pix *&_pixels, BitMap _header, const char* filePath, string msg)
{

	string bin = getStrBin(msg);
	changeBit(_pixels, _header.m_width * _header.m_height, bin);
}


//dịch về message
void messageBMP(string bin) {
	int k = bin.length();
	int i = 0;
	while (i < k) {
		int temp = 0;

		temp += (bin[i] - '0') * pow(2, 6);
		temp += (bin[i + 1] - '0') * pow(2, 5);
		temp += (bin[i + 2] - '0') * pow(2, 4);
		temp += (bin[i + 3] - '0') * pow(2, 3);
		temp += (bin[i + 4] - '0') * pow(2, 2);
		temp += (bin[i + 5] - '0') * pow(2, 1);
		temp += (bin[i + 6] - '0');

		i += 7;

		cout << (char)temp;
	}
	cout << endl;
}





//hàm giải mã và show msg khi nhập đúng key
void showMsgInPic(const char* filePath, string key)
{
	int length = 0;
	BitMap _header;
	char* _data = NULL;

	readBMPtext(filePath, _header, _data, length);
	Pix* _pixels = convertDataToPixelArray(_data, _header);

	if (key == "12345678") {
		string strBin = decryptionMBP(_pixels, _header.m_width * _header.m_height, length);
		messageBMP(strBin);
	}
	else {
		cout << "Key is not correct ! ";
		system("pause");
	}
}


//hàm mirror
void mirror(Pix*& _pixels, BitMap _header) {
	Pix* out = new Pix[_header.m_height*_header.m_width];

	for (int y = 0; y < _header.m_height; y++) {
		for (int x = 0; x < _header.m_width; x++) {
			out[(y * _header.m_width + x)] = _pixels[(y * _header.m_width + (_header.m_width - x))];
		}
	}
	_pixels = out;
}


void setAll(ConvMatrix &c, int nVal) {
	c.botLeft = c.botMid = c.botRight = c.midLeft = c.midRight = c.pixel = c.topLeft = c.topMid = c.topRight = nVal;

}

//gap càng nhỏ lưới càng mịn
void Conv3x3(ConvMatrix &c, Pix*& pixels, BitMap _header, int gap) {
	if (c.factor == 0)
		return;
	else {
		int stride1 = _header.m_width;
		int stride2 = stride1 * 2;
		int offSet = 0;
		int nWidth = _header.m_width - 2;
		int nHeigh = _header.m_height - 2;

		int nPixel1, nPixel2, nPixel3;
		for (int i = 0; i < nHeigh; i += gap) {
			for (int j = 0; j < nWidth; j += gap) {
				nPixel1 = ((pixels[i * nWidth].R * c.topLeft + pixels[i * nWidth + 1].R * c.topMid + pixels[i * nWidth + 2].R * c.topRight) + (pixels[i * nWidth + stride1].R * c.midLeft + pixels[i * nWidth + 1 + stride1].R * c.pixel + pixels[i * nWidth + 2 + stride1].R * c.midRight) + (pixels[i * nWidth + stride2].R * c.botLeft + pixels[i * nWidth + 1 + stride2].R * c.botMid + pixels[i * nWidth + 2 + stride2].R * c.botRight)) / c.factor;
				if (nPixel1 < 0)
					nPixel1 = 0;
				if (nPixel1 > 255)
					nPixel1 = 255;

				nPixel2 = ((pixels[i * nWidth].G * c.topLeft + pixels[i * nWidth + 1].G * c.topMid + pixels[i * nWidth + 2].G * c.topRight) + (pixels[i * nWidth + stride1].G * c.midLeft + pixels[i * nWidth + 1 + stride1].G * c.pixel + pixels[i * nWidth + 2 + stride1].G * c.midRight) + (pixels[i * nWidth + stride2].G * c.botLeft + pixels[i * nWidth + 1 + stride2].G * c.botMid + pixels[i * nWidth + 2 + stride2].G * c.botRight)) / c.factor;
				if (nPixel2 < 0)
					nPixel2 = 0;
				if (nPixel2 > 255)
					nPixel2 = 255;

				nPixel3 = ((pixels[i * nWidth].B * c.topLeft + pixels[i * nWidth + 1].B * c.topMid + pixels[i * nWidth + 2].B * c.topRight) + (pixels[i * nWidth + stride1].B * c.midLeft + pixels[i * nWidth + 1 + stride1].B * c.pixel + pixels[i * nWidth + 2 + stride1].B * c.midRight) + (pixels[i * nWidth + stride2].B * c.botLeft + pixels[i * nWidth + 1 + stride2].B * c.botMid + pixels[i * nWidth + 2 + stride2].B * c.botRight)) / c.factor;
				if (nPixel3 < 0)
					nPixel3 = 0;
				if (nPixel3 > 255)
					nPixel3 = 255;

				pixels[i * nWidth + j].B = nPixel3;
				pixels[i * nWidth + j].G = nPixel2;
				pixels[i * nWidth + j].R = nPixel1;

			}
		}
	}
}

void gridBlur(Pix*& pixels, BitMap _header, int nWeight) {
	ConvMatrix c = { 1 };
	c.pixel = nWeight;
	c.factor = nWeight + 8;
	Conv3x3(c, pixels, _header, nWeight);
}

//hàm Mandelprot set
void Mandelprot(Pix*& pixels, BitMap _header) {
	double    cr, ci;
	double nextr, nexti;
	double prevr, previ;

	const unsigned int max_iterations = 1000;

	for (unsigned int y = 0; y < _header.m_height; ++y)
	{
		for (unsigned int x = 0; x < _header.m_width; ++x)
		{
			cr = 1.5 * (2.0 * x / _header.m_width - 1.0) - 0.5;
			ci = (2.0 * y / _header.m_height - 1.0);

			nextr = nexti = 0;
			prevr = previ = 0;

			for (unsigned int i = 0; i < max_iterations; ++i)
			{
				prevr = nextr;
				previ = nexti;

				nextr = prevr * prevr - previ * previ + cr;
				nexti = 2 * prevr * previ + ci;

				if (((nextr * nextr) + (nexti * nexti)) > 4)
				{
					using namespace std;

					const double z = sqrt(nextr * nextr + nexti * nexti);

					const unsigned int index = static_cast<unsigned int>
						(1000.0 * log2(1.75 + i - log2(log2(z))) / log2(max_iterations));

					pixels[y * _header.m_width + x].B = pixels[y * _header.m_width + x].G = pixels[y * _header.m_width + x].R = index;

					break;
				}
			}
		}
	}
}
