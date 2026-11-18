#pragma once
#include "Vector.h"
#include <vector>
#include <string>

#include <iostream>

#include "Component.h"
#include "ImageFile.h"
#include "Input.h"

class GameObject
{
public:
	GameObject();
	GameObject(Vector vecPos);
	GameObject(Vector vecPos, std::vector<Component*> vComponents);
	
	Vector m_vecPosition;
	bool m_bActive;
	bool m_bGlobal = false;

	std::vector<Component*> m_vComponents;

	void setActive(bool bState);
	void addComponent(Component* comp);
	template <class T = Component> T* getComponent();

	static std::vector<GameObject*> sm_vGameObjects;
};

template <class T>
inline T* GameObject::getComponent()
{
	for (Component* c : m_vComponents) {
		if (typeid(*c) == typeid(T)) {
			return (T*)c;
		}
	}

	return nullptr;
}
