#pragma once
#include "Engine/engine.h"
class PlayerMovement :
    public Component
{
public:
    void tick(double deltaTime);

    bool m_bCanMove = true;
};

