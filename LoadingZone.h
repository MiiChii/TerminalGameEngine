#pragma once
#include "Engine/engine.h"

class LoadingZone :
    public Component
{
public:
    LoadingZone(int iSceneId, Vector vecSpawn);

    Vector m_vecSpawn;
    int m_iSceneId;

    void tick(double deltaTime);
};

