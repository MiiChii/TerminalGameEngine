#pragma once
#include "Component.h"
#include "Animation.h"
#include <string>
#include <vector>

class Animator : public Component
{
public:
	Animator(ImageFile* pIdle, std::vector<Animation*> vA, std::vector<std::string> sStates);

	std::vector<Animation*> m_vAnimation;
	std::vector<AnimatorState> m_vCurrentStates;
	ImageFile* m_pIdleImage;

	void tick(double deltaTime);
	void setBool(std::string s, bool b);

private:
	bool isActive(const Animation& a);
};

