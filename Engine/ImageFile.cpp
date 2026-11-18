#include "ImageFile.h"

#include <fstream>
#include <iostream>
#include <string>


ImageFile::ImageFile(Pixel** ppPixel, int iWidth, int iHeight)
{
    m_ppPixel = ppPixel;
    m_iWidth = iWidth;
    m_iHeight = iHeight;

    m_pHeightMap = nullptr;

    generateHeightMap();
}

ImageFile::ImageFile(std::string sFilePath, std::string sHMapPath)
{
    m_iWidth = 0;
    m_iHeight = 0;

    m_ppPixel = nullptr;
    m_pHeightMap = nullptr;

    openImage(sFilePath);

    if (sHMapPath == "")
        generateHeightMap();
    else
        initHeightMap(sHMapPath);
}




unsigned char* openFile(std::string sFilePath) {
    std::ifstream file;
    file.open(sFilePath, std::ios::in | std::ios::binary);

    if (!file) {
        printf("Couldn't find image");
        return nullptr;
    }

    file.seekg(0, std::ios::end);
    unsigned long long int size = file.tellg();

    unsigned char* data = new unsigned char[size];
    file.seekg(0);
    file.read((char*)data, size);

    return data;
}

unsigned long long int convertBytesToInt(unsigned char* acByte, bool bInverse) {
    if (!bInverse)
        return ((unsigned int)acByte[0] << 24) + ((unsigned int)acByte[1] << 16) + ((unsigned int)acByte[2] << 8) + (int)acByte[3];
    else
        return ((unsigned int)acByte[3] << 24) + ((unsigned int)acByte[2] << 16) + ((unsigned int)acByte[1] << 8) + (int)acByte[0];
}

void ImageFile::openImage(std::string sFileName)
{
    for (int x = 0; x < m_iWidth; x++) {
        if(m_ppPixel != nullptr)
            delete m_ppPixel[x];
    }
    if (m_ppPixel != nullptr)
        delete m_ppPixel;

    // FileType herausfinden
    std::string sFileType = "";
    for (int i = 0; i < sFileName.length(); i++) {
        if (sFileName[i] == '.' || !sFileType.empty())
            sFileType += sFileName[i];
    }

    // Richtige ?ffnen-Methode anhand des FileType ausf?hren
    if (sFileType == ".bmp") {
        openBmp(sFileName);
        
    }
    else if (sFileType == ".png") {
        openPng(sFileName);
    }
    else {
        printf("Filetype not supported");
    }
}

void ImageFile::initHeightMap(std::string sFilePath)
{
    if (m_pHeightMap) delete m_pHeightMap;
    m_pHeightMap = new HeightMap(sFilePath);
}

void ImageFile::initHeightMap(HeightMap* pHeightMap)
{
    if (m_pHeightMap) delete m_pHeightMap;
    m_pHeightMap = pHeightMap;
}

void ImageFile::generateHeightMap(bool bAutoGenerate)
{
    if (m_pHeightMap) delete m_pHeightMap;
    m_pHeightMap = new HeightMap(this, !bAutoGenerate);
}


void ImageFile::openPng(std::string sFileName) {
    unsigned char* pcData = openFile(sFileName);

    m_iWidth = convertBytesToInt(&pcData[16], false);
    m_iHeight = convertBytesToInt(&pcData[20], false);

    /// TODO - Png implementieren
}

void ImageFile::openBmp(std::string sFileName)
{
    // Load bytes of file into pcData
    unsigned char* pcData = openFile(sFileName);

    // Read dimensions from file
    m_iWidth = convertBytesToInt(&pcData[18], true);
    m_iHeight = convertBytesToInt(&pcData[22], true);

    // Create pixel arrays
    m_ppPixel = new Pixel* [m_iWidth];
    for (int x = 0; x < m_iWidth; x++) {
        m_ppPixel[x] = new Pixel[m_iHeight];
    }

    unsigned long long int iColorByte = convertBytesToInt(&pcData[10], true);

    unsigned int iBitSize = (((unsigned int)pcData[27] << 8) + (int)pcData[28]) / 8;

    char cExtraBytes = 4 - (m_iWidth * iBitSize) % 4;
    cExtraBytes = cExtraBytes == 4 ? 0 : cExtraBytes;

    for (int y = m_iHeight-1; y >= 0; y--) {
        for (int x = 0; x < m_iWidth; x++) {
            if(iBitSize == 4)
                m_ppPixel[x][y].setPixel(pcData[iColorByte+2], pcData[iColorByte + 1], pcData[iColorByte], pcData[iColorByte+3]);
            if (iBitSize == 3)
                m_ppPixel[x][y].setPixel(pcData[iColorByte + 2], pcData[iColorByte + 1], pcData[iColorByte]);
            iColorByte += iBitSize;
        }
        iColorByte += cExtraBytes;
    }
}
