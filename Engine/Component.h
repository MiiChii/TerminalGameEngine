#pragma once
class GameObject;

// Component is the base-class for all classes that should be attached to GameObjects
class Component
{
public:
	// Pointer as a reference to the GameObject to which the Component is attached
	GameObject* m_pGameObject = nullptr;
	bool m_bActive = true;

	// tick is called once every frame
	virtual void tick(double deltaTime) {}
	virtual void setActive(bool bState) { m_bActive = bState; }
};

