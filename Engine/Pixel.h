#pragma once
#include <set>
#include <string>

class Pixel{
public:
	// Constructors
	Pixel();
	Pixel(unsigned char cR, unsigned char cG, unsigned char cB, unsigned char cA = 255, double dHeight = 0);
	
	// Methods to change the pixel-data
	void deletePixel();
	void setPixel(Pixel p);
	void setPixel(unsigned char cR, unsigned char cG, unsigned char cB, unsigned char cA = 255, double dHeight = 0);

	// Changes the rgb values of the Pixel as if p was a pixel with alpha-value 255 right behind it.
	Pixel applyBackground(Pixel p);
    std::string getColorString(int x, int y);
	
	// Pixel-data (red, green, blue, alpha)
	unsigned char m_cR;
	unsigned char m_cG;
	unsigned char m_cB;
	unsigned char m_cA;
	double m_dHeight; // Not implemented yet

    float intensity();

    Pixel operator*=(float f);
    Pixel operator+=(Pixel p);

    // Compare-operators
	bool operator==(Pixel p);
	bool operator!=(Pixel p);
	bool operator<(const Pixel p) const;
};




class PixelStack {
private:
	struct comp {
		bool operator()(const Pixel* lhs, const Pixel* rhs) const {
			return *lhs < *rhs;
		}
	};
public:
	std::set<Pixel*, comp> vPixel;
	Pixel lastPixel;

    int x;
    int y;

	void add(Pixel* p);
	Pixel getColour(int x, int y);
	void deleteStack();
};