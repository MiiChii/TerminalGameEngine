#pragma once
#include "ImageFile.h"
#include "Component.h"

class ImageRenderer : public Component
{
public:
	ImageRenderer(ImageFile* pFile);
	ImageRenderer(ImageFile* pFile, int iL);

	void tick(double deltaTime);
	void setActive(bool bState);
	void printToScreen();

	void setImage(ImageFile* pImg);


	// Counter aller Bilder f�r iId
	static unsigned int sm_iImageCounter;
	int m_iId;
	int m_iLayer;



private:
	ImageFile* m_pImgFile;
	Vector m_vecOldPosition;
};

