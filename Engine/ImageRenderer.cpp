#include "ImageRenderer.h"

#include "GameObject.h"
#include "Screen.h"

unsigned int ImageRenderer::sm_iImageCounter = 0;

ImageRenderer::ImageRenderer(ImageFile* pFile) : ImageRenderer(pFile, 0) {}

ImageRenderer::ImageRenderer(ImageFile* pFile, int iL)
{
    m_vecOldPosition = Vector(-1000, -1000);
    m_iId = sm_iImageCounter;
    sm_iImageCounter++;

	m_pImgFile = pFile;
    m_iLayer = iL;
    Screen::addImage(m_iLayer);


    if (m_pGameObject != nullptr && m_pGameObject->m_bActive)
        printToScreen();
}

void ImageRenderer::tick(double deltaTime)
{
    if (m_pGameObject->m_vecPosition != m_vecOldPosition) {
        m_vecOldPosition = m_pGameObject->m_vecPosition;
        printToScreen();
    }
}

void ImageRenderer::setActive(bool bState)
{
    m_bActive = bState;

    if (m_bActive) {
        printToScreen();
    }
    else {
        Screen::resetImage(m_iId);
    }
}

void ImageRenderer::printToScreen()
{
    Screen::resetImage(m_iId);

    Vector vectorP = m_pGameObject->m_vecPosition;

    vectorP.m_dX -= m_pImgFile->m_iWidth / 2;
    vectorP.m_dY -= m_pImgFile->m_iHeight / 2;


    for (unsigned int y = 0; y < m_pImgFile->m_iHeight; y++) {
        for (unsigned int x = 0; x < m_pImgFile->m_iWidth; x++) {
            //Screen::printToPixel(vectorP.m_dX + x, vectorP.m_dY + y, m_pImgFile->m_ppPixel[x][y], m_iId);
            Screen::printToPixel(vectorP.m_dX + x, vectorP.m_dY + y, &(m_pImgFile->m_ppPixel[x][y]),
                                 m_pGameObject->m_vecPosition.m_dZ + m_pImgFile->m_pHeightMap->m_ppiHeightPixels[x][y] / 25.5, m_iId);
        }
    }
}

void ImageRenderer::setImage(ImageFile* pImg)
{
    if (m_pImgFile == pImg) return;

    m_pImgFile = pImg;

    printToScreen();
}
