#include "Collider.h"

#include "GameObject.h"

//std::vector<Collider*> Collider::vColliders;

Collider::Collider(std::string collisionMapFileName, int iFlagCount, int* piColFlags) : m_imgCollisionMap(collisionMapFileName)
{
	iFlagCount--;
	//vColliders.push_back(this);
	
	for (int i = 0; i < COL_ID_COUNTER; i++) {
		m_abCollisionFlags[i] = false;

		if (iFlagCount >= 0 && i == piColFlags[iFlagCount]) {
			m_abColliderFlags[i] = true;
			iFlagCount--;
		}
	}
}

void Collider::tick(double deltaTime)
{
	updateCollider();

	/*for (Collider* col : vColliders) {
		if (col == this)
			continue;

		if (isCollidingWith(col)) {
			for (int i = 0; i < COL_ID_COUNTER; i++) {
				abCollisionFlags[i] |= col->abColliderFlags[i];
			}
		}
	}*/
}

GameObject* Collider::isCollidingWith(int iFlag)
{
	for (GameObject* gO : GameObject::sm_vGameObjects) {
		Collider* col = gO->getComponent<Collider>();
		if (col == this)
			continue;
		if (!col)
			continue;
		if (!col->m_abColliderFlags[iFlag])
			continue;
		if (!col->m_bActive || !col->m_pGameObject->m_bActive)
			continue;

		for (int x = 0; x < X_RES; x++) {
			for (int y = 0; y < Y_RES; y++) {
				if (m_aabCollisionPixel[x][y] && col->m_aabCollisionPixel[x][y]) {
					return gO;
				}
			}
		}
	}
	return nullptr;
}


void Collider::updateCollider()
{
	Vector vectorP = m_pGameObject->m_vecPosition;

	vectorP.m_dX -= m_imgCollisionMap.m_iWidth / 2;
	vectorP.m_dY -= m_imgCollisionMap.m_iHeight / 2;

	for (int x = 0; x < X_RES; x++) {
		for (int y = 0; y < Y_RES; y++) {
			m_aabCollisionPixel[x][y] = false;
		}
	}
	for (int iY = 0; iY < m_imgCollisionMap.m_iHeight; iY++) {
		for (int iX = 0; iX < m_imgCollisionMap.m_iWidth; iX++) {
			int x = vectorP.m_dX + iX;
			int y = vectorP.m_dY + iY;

			if (x < 0 || x >= X_RES || y < 0 || y >= Y_RES)
				continue;

			
			m_aabCollisionPixel[x][y] = m_imgCollisionMap.m_ppPixel[iX][iY].m_cA > 100;
		}
	}
}

	


