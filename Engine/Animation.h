#pragma once
#include "AnimationFrame.h"
#include <string>
#include <vector>
#include <time.h>
#include "SpriteSheet.h"

class AnimatorState {
public:
	AnimatorState(std::string s) 
	{ 
		m_sName = s;
		m_bActive = false; 
		
		if (s[0] == '!') {
			m_sName = &m_sName[1];
			m_bActive = true;
		}
	}

	std::string m_sName;
	bool m_bActive;
};


class Animation
{
public:
	Animation(std::vector<std::string> sStates, std::vector<AnimationFrame*> vF);
	Animation(std::vector<std::string> sStates, std::vector<ImageFile*> vF);
	Animation(std::vector<std::string> sStates, SpriteSheet* pSheet);
	std::vector<AnimationFrame*> m_vFrames;
	std::vector<AnimatorState> m_vAnimationStates;

	AnimationFrame* m_pFrameCurrent;

	bool play();
	void playNextFrame();

private:
	int m_iFrameChangeTime;
	bool m_bPlaying;
};




