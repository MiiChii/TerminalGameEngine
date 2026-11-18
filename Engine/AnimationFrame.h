#pragma once
#include <string>
#include "ImageFile.h"

class AnimationFrame
{
public:
	AnimationFrame(std::string sFileName, int iFD);
	AnimationFrame(std::string sFileName);
	AnimationFrame(ImageFile* pF, int iFD);
	AnimationFrame(ImageFile* pF);

	ImageFile* m_pFile;
	int m_iFrameDuration;
	int m_iId;
};

