#include "PlayerAttack.h"
// #include <windows.h>
#include "PlayerMovement.h"

PlayerAttack::PlayerAttack()
{


	m_gameObjectSword = new GameObject();
	m_gameObjectSword->m_bGlobal = true;
	m_gameObjectSword->addComponent(new Collider("Assets//SwordCol.bmp", 1, new int{ COL_ID_PLAYERDAMAGE }));
	m_gameObjectSword->getComponent<Collider>()->setActive(false);

	m_bAttacking = false;
	m_iAttackTime = 0;

	m_iAttackAnticipation = 500;
	m_iAttackDuration = 200;
	m_iAttackCooldown = 300;
}

void PlayerAttack::tick(double deltaTime)
{
	// if (!m_bAttacking && GetAsyncKeyState(' ')) {
	// 	m_pGameObject->getComponent<Animator>()->setBool("Slashing", true);
	// 	m_pGameObject->getComponent<PlayerMovement>()->m_bCanMove = false;
	//
	// 	m_bAttacking = true;
	// 	m_iAttackTime = clock();
	//
	// 	m_gameObjectSword->m_vecPosition = m_pGameObject->m_vecPosition;
	//
	// }

	if (!m_bAttacking)
		return;


	if (clock() > m_iAttackTime + m_iAttackAnticipation + m_iAttackDuration + m_iAttackCooldown) {
		m_bAttacking = false;
		m_pGameObject->getComponent<Animator>()->setBool("Slashing", false);
		m_pGameObject->getComponent<PlayerMovement>()->m_bCanMove = true;
	}
	if (clock() > m_iAttackTime + m_iAttackAnticipation + m_iAttackDuration) {
		// m_gameObjectSword->getComponent<Collider>()->setActive(false);
	}
	else if (clock() > m_iAttackTime + m_iAttackAnticipation) {
		// m_gameObjectSword->getComponent<Collider>()->setActive(true);
	}


}

void PlayerAttack::attack()
{		

}
