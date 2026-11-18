#pragma once
#include "Component.h"
#include "ImageFile.h"

#include <vector>
#include <string>
#include "defines.h"

// Collider sind aus Deadline-Druck durch sehr ineffizientes Mapping der Bilddateien auf die Collider gel�st

class Collider : public Component
{
public:
	Collider(std::string collisionMapFilePath, int iFlagCount, int* piColFlags);

	bool m_abColliderFlags[COL_ID_COUNTER];
	bool m_abCollisionFlags[COL_ID_COUNTER];
	bool m_aabCollisionPixel[X_RES][Y_RES];

	ImageFile m_imgCollisionMap;

	void tick(double deltaTime);
	virtual GameObject* isCollidingWith(int iFlag);
	virtual void updateCollider();
};

