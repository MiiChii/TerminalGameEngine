#pragma once
#include "Vector.h"
#include "Pixel.h"
#include "Window.h"

#include <vector>
#include <array>
#include <string>

#include "defines.h"


namespace Screen
{
	//extern Window windowCurrent;				// Window containing all the pixel-data that is currently displayed
	extern PixelStack aaPixelStacks[X_RES][Y_RES];
	extern std::vector<Window*> vWindowImages;	// One window for every Sprite that is being displayed


		
	extern void init();
	extern void addImage(int iL);
	extern void printToPixel(int x, int y, Pixel* p, double dHeight, unsigned int id);
	extern void resetImage(unsigned int id);
	extern std::string calculatePixelRow(int y);
	extern void updateScreen();
}

