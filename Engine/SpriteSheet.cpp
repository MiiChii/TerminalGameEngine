#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(ImageFile* pImg, int iSpriteWidth, int iSpriteHeight)
{
	m_pImageSource = pImg;

	m_iSpriteWidth = iSpriteWidth;
	m_iSpriteHeight = iSpriteHeight;
	
	m_iColumns = m_pImageSource->m_iWidth / iSpriteWidth;
	m_iRows = m_pImageSource->m_iHeight / iSpriteHeight;



	for (int c = 0; c < m_iColumns; c++) {
		for (int r = 0; r < m_iRows; r++) {

			// Create pixel arrays
			Pixel** ppPixel = new Pixel * [m_iSpriteWidth];
			for (int x = 0; x < m_iSpriteHeight; x++) {
				ppPixel[x] = new Pixel[iSpriteHeight];
			}

			for (int x = 0; x < m_iSpriteWidth; x++) {
				for (int y = 0; y < m_iSpriteHeight; y++) {
					ppPixel[x][y] = m_pImageSource->m_ppPixel[c*m_iSpriteWidth+x][r*m_iSpriteHeight + y];
				}
			}

			ImageFile* pF = new ImageFile(ppPixel, m_iSpriteWidth, m_iSpriteHeight);
			m_vImages.push_back(pF);
		}
	}
}

SpriteSheet::SpriteSheet(std::string sFilePath, int iSpriteWidth, int iSpriteHeight, std::string sHMapPath)
	: SpriteSheet(new ImageFile(sFilePath, sHMapPath), iSpriteWidth, iSpriteHeight) {}
