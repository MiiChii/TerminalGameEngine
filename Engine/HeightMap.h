#pragma once
#include <string>

class ImageFile;

class HeightMap
{
public:
	HeightMap(std::string sFilePath);
	HeightMap(ImageFile* img, bool bSetNoHeight = false);

	int m_iHeight;
	int m_iWidth;
	int** m_ppiHeightPixels;
};

