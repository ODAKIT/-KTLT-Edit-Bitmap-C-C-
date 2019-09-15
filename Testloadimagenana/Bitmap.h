#pragma pack(push, 1)
#pragma once

#define BMP_OUT "Output.bmp"

#define BMP_SAVE "SAVE.bmp"

#define BMP_SAVETEMP "_Save.bmp"
struct Pix
{
	unsigned char B;
	unsigned char G;
	unsigned char R;

};
#pragma pack(pop)

#pragma pack(push, 1)
struct BitMap
	{
	short		m_signature;
	long		m_reserved1;
	long		m_reserved2;

	long		m_dataOffSet;

	long		m_size;
	long		m_width;
	long		m_height;
	short		m_planes;
	short		m_bpp;

	long		m_compression;
	long		m_sizeImage;

	long		m_xPixelsPreMeter;
	long		m_yPixelsPreMeter;

	long		m_colorsUsed;
	long		m_colorsImportant;
};
#pragma pack(pop)


void readBMP(const char* filePath, BitMap &header, char* &data);


void writeBMP(const char* filePath, BitMap &header, char* &data);

Pix* convertDataToPixelArray(char* &data, BitMap &header);

char* convertPixelArrayToData(Pix* &pixels, BitMap &header);
