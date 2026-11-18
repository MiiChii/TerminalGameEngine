#include "Enemy.h"
#include "Engine/GameObject.h"

#include "Engine/Collider.h"

Enemy::Enemy(int hp)
{
	m_iHp = hp;
}

void Enemy::tick(double deltaTime)
{
	if (m_iHp <= 0)
		m_pGameObject->setActive(false);


	Collider* col = m_pGameObject->getComponent<Collider>();
	if (col && col->isCollidingWith(COL_ID_PLAYERDAMAGE)) {
		m_iHp--;
	}

}
