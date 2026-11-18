#pragma once
#include "Engine/engine.h"
#include "Player.h"
#include "Enemy.h"
#include "LoadingZone.h"

class Game
{
public:
	Game();

	void initAssets();
	void initScenes();

	void tick(double deltaTime);
	bool finiCondition();
	void fini();


	// Assets
#pragma region imageFiles
	ImageFile* m_pImgOverworld;
	ImageFile* m_pImgCow;
	ImageFile* m_pImgCave;
#pragma endregion

#pragma region spriteSheets
	SpriteSheet* m_pSheetSwordDown;
	SpriteSheet* m_pSheetSwordUp;
	SpriteSheet* m_pSheetSwordRight;
	SpriteSheet* m_pSheetSwordLeft;
#pragma endregion

#pragma region animations
	Animation* m_pAnimSwordDown;
	Animation* m_pAnimSwordUp;
	Animation* m_pAnimSwordRight;
	Animation* m_pAnimSwordLeft;
#pragma endregion

	// Objects
	GameObject* m_pPlayer;
};

