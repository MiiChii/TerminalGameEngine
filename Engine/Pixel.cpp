#include "Pixel.h"
#include "defines.h"
#include "LightSource.h"

Pixel::Pixel() : Pixel(0, 0, 0, 0, 0) {}
Pixel::Pixel(unsigned char cR, unsigned char cG, unsigned char cB, unsigned char cA, double dHeight)
{
	setPixel(cR, cG, cB, cA, dHeight);
}

void Pixel::deletePixel()
{
	m_cR = 0;
	m_cG = 0;
	m_cB = 0;
	m_cA = 0;
	m_dHeight = 0;
}

void Pixel::setPixel(Pixel p)
{
	m_cR = p.m_cR;
	m_cG = p.m_cG;
	m_cB = p.m_cB;
	m_cA = p.m_cA;
	m_dHeight = p.m_dHeight;
}

void Pixel::setPixel(unsigned char cR, unsigned char cG, unsigned char cB, unsigned char cA, double dHeight)
{
	m_cR = cR;
	m_cG = cG;
	m_cB = cB;
	m_cA = cA;
	m_dHeight = dHeight;
}

Pixel Pixel::applyBackground(Pixel p)
{
	Pixel pixelOut(m_cR,m_cG,m_cB,m_cA);
	double dAlphaTemp = (double)m_cA / 255;
	pixelOut.m_cR = ((1 - dAlphaTemp) * p.m_cR) + (dAlphaTemp * m_cR);
	pixelOut.m_cG = ((1 - dAlphaTemp) * p.m_cG) + (dAlphaTemp * m_cG);
	pixelOut.m_cB = ((1 - dAlphaTemp) * p.m_cB) + (dAlphaTemp * m_cB);
	return pixelOut;
}

std::string Pixel::getColorString(int x, int y) {
    char acTemp[100];
    sprintf(acTemp, "\033[%i;%iH""\033[48;2;%i;%i;%im" PIXEL_STRING, y, x, m_cR, m_cG, m_cB);
    return acTemp;
}

float Pixel::intensity() {
    return (float)(m_cR+m_cG+m_cB) / 3;
}

bool Pixel::operator==(Pixel p)
{
	return (m_cR == p.m_cR && m_cG == p.m_cG && m_cB == p.m_cB && m_cA != 0 && m_cA != 0) || (m_cA == 0 && m_cA == 0);
}

bool Pixel::operator!=(Pixel p)
{
	return !(*this == p);
}

bool Pixel::operator<(const Pixel p) const
{
	return m_dHeight < p.m_dHeight;
}

Pixel Pixel::operator*=(float f) {
    int i;
    i = m_cR * f;
    m_cR = i > 255 ? 255 : i;
    i = m_cG * f;
    m_cG = i > 255 ? 255 : i;
    i = m_cB * f;
    m_cB = i > 255 ? 255 : i;
    return *this;
}

Pixel Pixel::operator+=(Pixel p) {
    m_cR += p.m_cR;
    m_cG += p.m_cG;
    m_cB += p.m_cB;
    return *this;
}




void PixelStack::add(Pixel* pxl)
{
	//vPixel.insert(std::upper_bound(vPixel.begin(), vPixel.end(), pxl), pxl);
	vPixel.insert(pxl);
}

Pixel PixelStack::getColour(int x, int y)
{
	Pixel pixelOut = Pixel(0,0,0,255);

	for (Pixel* p : vPixel) {
		pixelOut = p->applyBackground(pixelOut);
        pixelOut.m_dHeight = p->m_dHeight;
	}

    float fLightIntensity = LightSource::sm_lightSources.empty() ? 1 : 0;
    for(LightSource*& s : LightSource::sm_lightSources){
        Vector pos(x, y, pixelOut.m_dHeight);
        Vector diff = s->m_vPosition - pos;
        if(diff.m_dZ < 0 || diff.magnitude3d() >= s->m_fRadius)
            continue;

        float fCurrentLightIntensity = s->m_fIntensity * ((s->m_fRadius-diff.magnitude3d()) / s->m_fRadius );
        if(fLightIntensity < fCurrentLightIntensity) fLightIntensity = fCurrentLightIntensity;
    }
    pixelOut *= fLightIntensity;
	return pixelOut;
}

void PixelStack::deleteStack()
{
	vPixel.clear();
}
