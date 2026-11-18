#pragma once
#include <vector>
#include "ImageFile.h"

class SpriteSheet
{
public:
	SpriteSheet(ImageFile* pImgFile, int iSpriteWidth, int iSpriteHeight);
	SpriteSheet(std::string sFilePath, int iSpriteWidth, int iSpriteHeight, std::string sHMapPath = "");

	ImageFile* m_pImageSource;
	std::vector<ImageFile*> m_vImages;

	int m_iSpriteWidth;
	int m_iSpriteHeight;

	int m_iColumns;
	int m_iRows;
};

