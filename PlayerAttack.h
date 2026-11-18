#pragma once
#include "Engine/engine.h"
class PlayerAttack : public Component
{
public:
	PlayerAttack();

	void tick(double deltaTime);
	void attack();
	
	GameObject* m_gameObjectSword;
	bool m_bAttacking;
	int m_iAttackTime;

	int m_iAttackAnticipation;
	int m_iAttackDuration;
	int m_iAttackCooldown;
};

