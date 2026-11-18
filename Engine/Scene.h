#pragma once
#include "GameObject.h"
#include "Vector.h"
#include <vector>

class Scene
{
public:
	Scene(std::vector<GameObject*> vGameObjects);

	void loadScene();

	std::vector<GameObject*> m_vGameObjects;
	int m_iId;

	static bool sm_bReload;
	static int sm_iCounter;
	static std::vector<Scene> sm_vScenes;
};

