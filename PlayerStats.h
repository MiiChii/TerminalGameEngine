#pragma once
#include "Engine/engine.h"
#include <vector>

class PlayerStats :
    public Component
{
public:
    PlayerStats();

    int m_iHp;
    int m_iHpMax;
    int m_iIFrames;

    ImageFile* m_imgHeart;
    ImageFile* m_imgHeartEmpty;

    std::vector<GameObject*> m_gameObjectLifes;

    void tick(double deltaTime);
    void addLife();
};

