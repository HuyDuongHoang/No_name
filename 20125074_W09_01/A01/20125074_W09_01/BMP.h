//#pragma once
#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <windows.h>
#include <fstream>
#pragma pack(1)
using namespace std;

//----------------Các struct cơ bản ------------------
struct BmpSignature {
    unsigned char data[2];
};

struct BmpHeader {
    BmpSignature signature = { 'B', 'M' };
    uint32_t fileSize{ 0 };
    uint16_t reserved1{ 0 };
    uint16_t reserved2{ 0 };
    uint32_t dataOffset{ 0 };
};

struct BmpDib {
    uint32_t dibsSize{ 0 };
    int32_t imageWidth{ 0 };
    int32_t imageHeight{ 0 };

                                          
    uint16_t colorPlaneCount{ 1 };          
    uint16_t pixelSize{ 0 };        
    uint32_t compressMethod{ 0 };               
    uint32_t bitmapByteCount{ 0 };  
    int32_t horizontalResolution{ 0 };
    int32_t verticalResolution{ 0 };
    uint32_t colorsCount{ 0 };             
    uint32_t importantColorCount{ 0 };      
};

struct Color {
    unsigned char blue = { 255 };
    unsigned char green = { 255 };
    unsigned char red = { 255 };
};

struct ColorTable {
    Color* colors;
    uint32_t length;
};

struct PixelArray {
    Color** pixels;
    uint32_t rowCount;
    uint32_t columnCount;
};


void drawBmp(BmpDib dib, PixelArray data);

void releaseBmpPixelArray(PixelArray data);

void writeBmp(string fname, BmpHeader& englandFlag_Header, BmpDib& englandFlag_Dib, PixelArray& data);

//--------------------------------------------

