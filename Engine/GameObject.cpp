#include "GameObject.h"

#include "Collider.h"
#include "ImageRenderer.h"
#include "Screen.h"

std::vector<GameObject*> GameObject::sm_vGameObjects = {};



GameObject::GameObject()
{
	sm_vGameObjects.push_back(this);
	m_bActive = true;
}

GameObject::GameObject(Vector vectorPos) : GameObject()
{
	m_vecPosition = vectorPos;
}

GameObject::GameObject(Vector vectorPos, std::vector<Component*> vC) : GameObject(vectorPos)
{
	for (Component* c : vC) {
		addComponent(c);
	}
}



void GameObject::setActive(bool bState)
{
    m_bActive = bState;

    ImageRenderer* img;
    if (m_bActive) {
        if (img = getComponent<ImageRenderer>()) {
            img->printToScreen();
        }
        return;
    }

    if (img = getComponent<ImageRenderer>()) {
        Screen::resetImage(img->m_iId);
    }
}

void GameObject::addComponent(Component* comp)
{
	comp->m_pGameObject = this;
	m_vComponents.push_back(comp);
}




