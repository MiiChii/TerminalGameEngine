#pragma once
#include "Pixel.h"
#include "defines.h"

class Window
{
public:
	Window(int iL, bool filled = false);
	//Pixel m_aaPixels[X_RES][Y_RES];
	Pixel* m_aaPixels[X_RES][Y_RES];
	int m_iLayer;
};

