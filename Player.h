#pragma once
#include "Engine/engine.h"
#include "PlayerMovement.h"
#include "PlayerAttack.h"
#include "PlayerStats.h"

class Player : public GameObject
{
public:
	Player();
	Player(Vector vectorPos);

	SpriteSheet* m_sheetWalkDown;
	SpriteSheet* m_sheetWalkUp;
	SpriteSheet* m_sheetWalkRight;
	SpriteSheet* m_sheetWalkLeft;

	SpriteSheet* m_sheetSlashDown;
	SpriteSheet* m_sheetSlashUp;
	SpriteSheet* m_sheetSlashRight;
	SpriteSheet* m_sheetSlashLeft;

	Animation* m_animWalkDown;
	Animation* m_animWalkUp;
	Animation* m_animWalkRight;
	Animation* m_animWalkLeft;

	Animation* m_animIdleDown;
	Animation* m_animIdleUp;
	Animation* m_animIdleRight;
	Animation* m_animIdleLeft;

	Animation* m_animSlashDown;
	Animation* m_animSlashUp;
	Animation* m_animSlashRight;
	Animation* m_animSlashLeft;

	ImageRenderer* m_imageRenderer;
	Animator* m_animator;
	PlayerStats* m_stats;
	PlayerMovement* m_movement;
	PlayerAttack* m_attack;

	Vector m_lookDirection;
};

