#include "Animation.h"
#include "defines.h"

Animation::Animation(std::vector<std::string> sStates, std::vector<AnimationFrame*> vF)
{
    for (std::string s : sStates) {
        m_vAnimationStates.push_back(AnimatorState(s));
    }

    m_vFrames = vF;
    m_pFrameCurrent = m_vFrames.front();
    m_iFrameChangeTime = 0;

    m_bPlaying = false;

    int i = 0;
    for (AnimationFrame* f : m_vFrames) {
        f->m_iId = i;
        i++;
    }
}

Animation::Animation(std::vector<std::string> sStates, std::vector<ImageFile*> vF) {
    for (std::string s : sStates) {
        m_vAnimationStates.push_back(AnimatorState(s));
    }

    for (ImageFile* f : vF) {
        m_vFrames.push_back(new AnimationFrame(f));
    }

    m_pFrameCurrent = m_vFrames.front();
    m_iFrameChangeTime = 0;

    m_bPlaying = false;

    int i = 0;
    for (AnimationFrame* f : m_vFrames) {
        f->m_iId = i;
        i++;
    }
}

Animation::Animation(std::vector<std::string> sStates, SpriteSheet* pSheet)
{
    for (std::string s : sStates) {
        m_vAnimationStates.push_back(AnimatorState(s));
    }

    std::vector<AnimationFrame*> vF;
    for (int i = 0; i < pSheet->m_vImages.size(); i++) {
        vF.push_back(new AnimationFrame(pSheet->m_vImages[i]));
    }
    
    m_vFrames = vF;
    m_pFrameCurrent = m_vFrames.front();
    m_iFrameChangeTime = 0;

    m_bPlaying = false;

    int i = 0;
    for (AnimationFrame* f : m_vFrames) {
        f->m_iId = i;
        i++;
    }
}



bool Animation::play()
{
    bool bOut = clock() > m_iFrameChangeTime + m_pFrameCurrent->m_iFrameDuration;

    if (bOut) {
        m_iFrameChangeTime = clock();
        playNextFrame();
    }

    return bOut;
}

void Animation::playNextFrame()
{
    if (m_pFrameCurrent == m_vFrames.back()) {
        m_pFrameCurrent = m_vFrames.front();
    }
    else {
        m_pFrameCurrent = m_vFrames[m_pFrameCurrent->m_iId + 1];
    }
}
