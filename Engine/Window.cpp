#include "Window.h"

Window::Window(int iL, bool bFilled)
{
	m_iLayer = iL;

	for (int x = 0; x < X_RES; x++)
	{
		for (int y = 0; y < Y_RES; y++)
		{
			if (bFilled) {
				m_aaPixels[x][y] = new Pixel;
				continue;
			}
			m_aaPixels[x][y] = nullptr;
		}
	}
}
