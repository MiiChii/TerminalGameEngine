#include "Screen.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <array>
// #include <windows.h>

#include <thread>
#include <future>
#include <execution>


//Window Screen::windowCurrent(0, true);
PixelStack Screen::aaPixelStacks[X_RES][Y_RES];
std::vector<Window*> Screen::vWindowImages;

void Screen::init() {
    /*for(int i = 0; i < X_RES*Y_RES; i++){
        aaPixelStacks[i].x = i % X_RES;
        aaPixelStacks[i].y = (i - aaPixelStacks[i].x) / X_RES;
    }*/
}

void Screen::addImage(int iL)
{
	vWindowImages.push_back(new Window(iL));
}

void Screen::printToPixel(int x, int y, Pixel* pixel, double dHeight, unsigned int id)
{
	if (x < 0 || x >= X_RES || y < 0 || y >= Y_RES)
		return;


	if (Pixel* p = vWindowImages[id]->m_aaPixels[x][y]) delete p;
	vWindowImages[id]->m_aaPixels[x][y] = new Pixel(*pixel);
	vWindowImages[id]->m_aaPixels[x][y]->m_dHeight = dHeight;

}

void Screen::resetImage(unsigned int id)
{
	for (int x = 0; x < X_RES; x++) {
		for (int y = 0; y < Y_RES; y++) {
			if(Pixel* p = vWindowImages[id]->m_aaPixels[x][y])
				vWindowImages[id]->m_aaPixels[x][y]->deletePixel();
		}
	}
}



/*
void Screen::updateScreen()
{
	std::string sOut = "";

	// iterate through every pixel on the screen

    sOut = std::transform_reduce(std::execution::par_unseq, std::begin(aaPixelStacks), std::end(aaPixelStacks), (std::string)"", std::plus<std::string>(), [=](PixelStack& p) {

        Pixel pixelOut(0,0,0,255);
        std::string sTemp = "";

        for(Window* w : vWindowImages){
            if (w->m_aaPixels[p.x][p.y] == nullptr || w->m_aaPixels[p.x][p.y]->m_cA == 0)
                continue;

            p.add(w->m_aaPixels[p.x][p.y]);
        }

        pixelOut = p.getColour();
        p.deleteStack();



        // most importantly, skip writing the character if it hasn't changed
        if (pixelOut == p.lastPixel)
            return sTemp;

        p.lastPixel.setPixel(pixelOut);
        return p.lastPixel.getColorString(p.x, p.y);
    });

	//printf("%s", sOut.c_str());
	DWORD charsWritten;
	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), sOut.c_str(), sOut.length(), &charsWritten, NULL);
}*/




std::string Screen::calculatePixelRow(int y) {
	std::string slut;
	for (int x = 0; x < X_RES; x++) {
		Pixel pixelOut(0, 0, 0, 255);

		// check if the pixel is or should be transparent
		bool bTransparent = true;
		for (Window*& w : vWindowImages) {
			if (w->m_aaPixels[x][y] && w->m_aaPixels[x][y]->m_cA != 0)
				bTransparent = false;
		}

		// print out black if the pixel is transparent
		//if (bEmpty && !windowCurrent.m_aaPixels[x][y]->m_cA == 0) {
		if (!(bTransparent && aaPixelStacks[x][y].lastPixel.m_cA == 0)) {
			for (Window*& w : vWindowImages) {
				// skip transparent pixels for speed
				if (w->m_aaPixels[x][y] == nullptr || w->m_aaPixels[x][y]->m_cA == 0)
					continue;

				aaPixelStacks[x][y].add(w->m_aaPixels[x][y]);
			}

			pixelOut = aaPixelStacks[x][y].getColour(x, y);
			//aaPixelStacks[x][y].deleteStack();
		}



		// most importantly, skip writing the character if it hasn't changed
		if (pixelOut == aaPixelStacks[x][y].lastPixel)
			continue;

		aaPixelStacks[x][y].lastPixel.setPixel(pixelOut);
		char acTemp[100];
		sprintf(acTemp, "\033[%i;%iH""\033[48;2;%i;%i;%im" PIXEL_STRING, y, x*2, pixelOut.m_cR, pixelOut.m_cG, pixelOut.m_cB);
        slut += acTemp;
	}
	return slut;
}


void Screen::updateScreen()
{
	std::string sOut = "";

	// iterate through every pixel on the screen
	//std::thread threads[Y_RES];
	std::future<std::string> futures[Y_RES];


	for (int y = 0; y < Y_RES; y++) {
		//std::thread thread_obj(calculatePixelRow, y, std::ref(sOut));
		//threads[y] = std::thread(calculatePixelRow, y, std::ref(sOut));
		futures[y] = std::async(std::launch::async, calculatePixelRow, y);
	}


	for (int y = 0; y < Y_RES; y++) {
		sOut += futures[y].get();
		for (int x = 0; x < X_RES; x++) {
			aaPixelStacks[x][y].deleteStack();
		}
	}
	
	
	
    std::cout << sOut;
	//DWORD charsWritten;
	//WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), sOut.c_str(), sOut.length(), &charsWritten, NULL);
}



/*
void Screen::updateScreen()
{
	std::string sOut = "";
	char acTemp[100];

	// iterate through every pixel on the screen


	for (int y = 0; y < Y_RES; y++) {
		for (int x = 0; x < X_RES; x++) {
			Pixel pixelOut(0,0,0,255);

			// check if the pixel is or should be transparent
			bool bTransparent = true;
			for (Window* w : vWindowImages) {
				if (w->m_aaPixels[x][y] && w->m_aaPixels[x][y]->m_cA != 0)
					bTransparent = false;
			}

			// print out black if the pixel is transparent
			//if (bEmpty && !windowCurrent.m_aaPixels[x][y]->m_cA == 0) {
			if (!(bTransparent && aaPixelStacks[x][y].lastPixel.m_cA == 0)) {
				for (Window* w : vWindowImages) {
					// skip transparent pixels for speed
					if (w->m_aaPixels[x][y] == nullptr || w->m_aaPixels[x][y]->m_cA == 0)
						continue;

					aaPixelStacks[x][y].add(w->m_aaPixels[x][y]);
				}

				pixelOut = aaPixelStacks[x][y].getColour();
				aaPixelStacks[x][y].deleteStack();
			}



			// most importantly, skip writing the character if it hasn't changed
			if (pixelOut == aaPixelStacks[x][y].lastPixel)
				continue;

			aaPixelStacks[x][y].lastPixel.setPixel(pixelOut);
			sprintf(acTemp, "\033[%i;%iH""\033[48;2;%i;%i;%im" PIXEL_STRING, y, x, pixelOut.m_cR, pixelOut.m_cG, pixelOut.m_cB);
			sOut += acTemp;
		}
	}

	//printf("%s", sOut.c_str());
	DWORD charsWritten;
	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), sOut.c_str(), sOut.length(), &charsWritten, NULL);
}

/*
#include "Screen.h"
#include <string>
#include <stdio.h>
#include <array>
#include <Windows.h>


Window Screen::windowCurrent(0);
std::vector<Window*> Screen::vWindowImages;

void Screen::addImage(int iL)
{
	vWindowImages.push_back(new Window(iL));
}

void Screen::printToPixel(int x, int y, Pixel p, unsigned int id)
{
	if (x < 0 || x >= X_RES || y < 0 || y >= Y_RES)
		return;
	vWindowImages[id]->m_aaPixels[x][y].setPixel(p);
}

void Screen::resetImage(unsigned int id)
{
	for (int x = 0; x < X_RES; x++) {
		for (int y = 0; y < Y_RES; y++) {
			vWindowImages[id]->m_aaPixels[x][y].deletePixel();
		}
	}
}


void Screen::updateScreen()
{
	std::vector<Window*> vW = vWindowImages;

	for (int i = 0; i < vW.size(); i++)
	{
		for (int j = 0; j < vW.size() - 1; j++)
		{
			if (vW[j]->m_iLayer > vW[j + 1]->m_iLayer)
				std::swap(vW[j], vW[j + 1]);
		}
	}





	std::string sOut = "";
	char acTemp[100];

	for (int y = 0; y < Y_RES; y++) {
		for (int x = 0; x < X_RES; x++) {
			Pixel pixelOut(0, 0, 0, 255);

			bool bEmpty = true;
			for (Window* w : vW) {
				if (!w->m_aaPixels[x][y].m_cA == 0)
					bEmpty = false;
			}

			if (bEmpty && !windowCurrent.m_aaPixels[x][y].m_cA == 0) {
				sprintf(acTemp, "\033[%i;%iH""\033[0m" PIXEL_STRING, y, x);
				sOut += acTemp;
				windowCurrent.m_aaPixels[x][y].deletePixel();
			}
			else for (Window* w : vW) {
				if (w->m_aaPixels[x][y].m_cA == 0)
					continue;

				pixelOut = w->m_aaPixels[x][y].applyBackground(pixelOut);
			}
			if (pixelOut == windowCurrent.m_aaPixels[x][y])
				continue;

			windowCurrent.m_aaPixels[x][y].setPixel(pixelOut);
			sprintf(acTemp, "\033[%i;%iH""\033[48;2;%i;%i;%im" PIXEL_STRING, y, x, pixelOut.m_cR, pixelOut.m_cG, pixelOut.m_cB);
			sOut += acTemp;
		}
	}

	//printf("%s", sOut.c_str());
	DWORD charsWritten;
	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), sOut.c_str(), sOut.length(), &charsWritten, NULL);
}
*/
