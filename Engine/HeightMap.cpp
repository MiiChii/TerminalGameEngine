#include "HeightMap.h"
#include "ImageFile.h"


HeightMap::HeightMap(std::string sFilePath) : HeightMap(new ImageFile(sFilePath)) {}

HeightMap::HeightMap(ImageFile* img, bool bSetNoHeight)
{
	m_iWidth = img->m_iWidth;
	m_iHeight = img->m_iHeight;

	m_ppiHeightPixels = new int* [m_iWidth];
	for (int i = 0; i < m_iWidth; i++)
		m_ppiHeightPixels[i] = new int[m_iHeight];

	for (int x = 0; x < m_iWidth; x++)
	{
		for (int y = 0; y < m_iHeight; y++)
		{
			const Pixel& pxl = img->m_ppPixel[x][y];
			if (pxl.m_cA == 0) {
				m_ppiHeightPixels[x][y] = 0;
				continue;
			}
			if (bSetNoHeight) {
				m_ppiHeightPixels[x][y] = 0;
				continue;
			}
			m_ppiHeightPixels[x][y] = (float)(pxl.m_cR + pxl.m_cG + pxl.m_cB) / 3;
		}
	}
}
