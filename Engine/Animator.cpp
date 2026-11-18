#include "Animator.h"

#include "GameObject.h"
#include "ImageRenderer.h"

Animator::Animator(ImageFile* pIdle, std::vector<Animation*> vA, std::vector<std::string> sStates)
{
	for (std::string s : sStates) {
		m_vCurrentStates.push_back(AnimatorState(s));
	}

	m_pIdleImage = pIdle;
	m_vAnimation = vA;
}

void Animator::tick(double deltaTime)
{
	for (Animation* a : m_vAnimation) {
		if (isActive(*a)) {
			if (a->play()) {
				m_pGameObject->getComponent<ImageRenderer>()->setImage(a->m_pFrameCurrent->m_pFile);
			}
			return;
		}
	}

	m_pGameObject->getComponent<ImageRenderer>()->setImage(m_pIdleImage);
}

void Animator::setBool(std::string s, bool b)
{
	for (AnimatorState& a : m_vCurrentStates) {
		if (a.m_sName == s)
			a.m_bActive = b;
	}
}

bool Animator::isActive(const Animation& a)
{
	for (AnimatorState animator : m_vCurrentStates) {
		for (AnimatorState animation : a.m_vAnimationStates) {
			if (animation.m_sName == animator.m_sName)
				if (animator.m_bActive == animation.m_bActive)
					return false;
		}
	}
	return true;
}
