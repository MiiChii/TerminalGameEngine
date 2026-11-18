#pragma once
#include <string>
#include "Component.h"
#include "Vector.h"
#include "Pixel.h"
#include "HeightMap.h"

class ImageFile
{
public:
	ImageFile(Pixel** ppPixel, int iWidth, int iHeight);
	ImageFile(std::string sFilePath, std::string sHMapPath = "");

	// Metadaten
	unsigned int m_iWidth;
	unsigned int m_iHeight;

	Pixel** m_ppPixel;
	HeightMap* m_pHeightMap;

	void openImage(std::string sFilePath);
	void initHeightMap(std::string sFilePath);
	void initHeightMap(HeightMap* pHeightMap);
	void generateHeightMap(bool bAutoGenerate = false);

private:
	void openPng(std::string sFilePath);
	void openBmp(std::string sFilePath);
};
