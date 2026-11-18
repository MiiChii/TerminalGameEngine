#include "Scene.h"

int Scene::sm_iCounter = 0;
std::vector<Scene> Scene::sm_vScenes;
bool Scene::sm_bReload = false;

Scene::Scene(std::vector<GameObject*> vGO)
{
	m_iId = sm_iCounter;
	sm_iCounter++;
	m_vGameObjects = vGO;
	
}

void Scene::loadScene()
{
	sm_bReload = true;
	//GameObject::vGameObjects = vGameObjects;
	for (GameObject* gO : GameObject::sm_vGameObjects) {
		if (gO->m_bGlobal)
			continue;
		gO->setActive(false);
	}
	for (GameObject* gO : m_vGameObjects) {
		gO->setActive(true);
	}
}
