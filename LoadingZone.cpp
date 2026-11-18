#include "LoadingZone.h"
#include "Engine/engine.h"
#include "PlayerMovement.h"

LoadingZone::LoadingZone(int iId, Vector vS)
{
	m_vecSpawn = vS;
	m_iSceneId = iId;
}

void LoadingZone::tick(double deltaTime)
{
	if (m_pGameObject->getComponent<Collider>()->isCollidingWith(COL_ID_PLAYER)) {
		for (GameObject* gO : GameObject::sm_vGameObjects) {
			if (!(gO->getComponent<PlayerMovement>())) {
				continue;
			}
			gO->m_vecPosition = m_vecSpawn;
		}
		Scene::sm_vScenes[m_iSceneId].loadScene();
	}
}
