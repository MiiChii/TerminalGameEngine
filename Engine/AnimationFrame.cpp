#include "AnimationFrame.h"
#include "defines.h"

AnimationFrame::AnimationFrame(std::string sFileName, int iFD)
{
	m_pFile = new ImageFile(sFileName);
	m_iFrameDuration = iFD;
}

AnimationFrame::AnimationFrame(std::string sFileName) : AnimationFrame(sFileName, ANIMATION_FRAME_LENGTH) {}

AnimationFrame::AnimationFrame(ImageFile* pF, int iFD)
{
	m_pFile = pF;
	m_iFrameDuration = iFD;
}

AnimationFrame::AnimationFrame(ImageFile* pF) : AnimationFrame(pF, ANIMATION_FRAME_LENGTH) {}
