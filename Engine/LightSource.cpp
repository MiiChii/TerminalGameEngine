#include "LightSource.h"

std::vector<LightSource*> LightSource::sm_lightSources = {};

LightSource::LightSource(Vector vPosition, float fIntensity, float fRadius) {
    m_vPosition = vPosition;
    m_fIntensity = fIntensity;
    m_fRadius = fRadius;

    sm_lightSources.push_back(this);
}