#pragma once
#include "Engine/Component.h"
class Enemy :
    public Component
{
public:
    Enemy(int iHp);

    void tick(double deltaTime);

    int m_iHp;
};

