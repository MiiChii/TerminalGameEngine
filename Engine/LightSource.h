#pragma once
#include "Vector.h"
#include <vector>

class LightSource {
public:
    LightSource(Vector vPosition, float fIntensity, float fRadius = 100);

    Vector m_vPosition;
    float m_fIntensity;
    float m_fRadius;

    static std::vector<LightSource*> sm_lightSources;
};