#include "PlayerStats.h"

PlayerStats::PlayerStats()
{
	// m_iIFrames = 1500;
	//
	// m_imgHeart = new ImageFile("Assets//Heart.bmp");
	// m_imgHeartEmpty = new ImageFile("Assets//HeartEmpty.bmp");
	//
	// m_iHpMax = 0;
	// for (int i = 0; i < 5; i++) {
	// 	addLife();
	// }
}

int iHitTimer = 0;
void PlayerStats::tick(double deltaTime)
{
	// int iTimeSinceHit = clock() - iHitTimer;
	// if (iTimeSinceHit < m_iIFrames) {
	// 	if (iTimeSinceHit % 160 > 80) {
	// 		m_pGameObject->getComponent<ImageRenderer>()->setActive(false);
	// 	}
	// 	else {
	// 		m_pGameObject->getComponent<ImageRenderer>()->setActive(true);
	// 	}
	// 	return;
	// }
	//
	// m_pGameObject->getComponent<ImageRenderer>()->m_bActive = true;
	//
	// GameObject* enemy = m_pGameObject->getComponent<Collider>()->isCollidingWith(COL_ID_ENEMYDAMAGE);
	// if (enemy) {
	// 	if (m_gameObjectLifes.empty())
	// 		return;
	//
	// 	Vector vectorKnockBack = m_pGameObject->m_vecPosition - enemy->m_vecPosition;
	// 	m_pGameObject->m_vecPosition += vectorKnockBack.normal() * 10;
	//
	// 	m_gameObjectLifes[--m_iHp]->getComponent<ImageRenderer>()->setImage(m_imgHeartEmpty);
	//
	// 	iHitTimer = clock();
	// }
}

void PlayerStats::addLife()
{
	for (GameObject* h : m_gameObjectLifes) {
        m_gameObjectLifes[--m_iHp]->getComponent<ImageRenderer>()->setImage(m_imgHeart);
	}

	m_iHpMax++;
	m_iHp = m_iHpMax;

	m_gameObjectLifes.push_back(new GameObject(Vector(30 + 10 * m_gameObjectLifes.size(), 7)));
	m_gameObjectLifes.back()->m_bGlobal = true;
	m_gameObjectLifes.back()->addComponent(new ImageRenderer(m_imgHeart, LAYER_UI));
}


