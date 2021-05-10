#include "BMP.h"

//Hàm vẽ pixel array lên console:
void drawBmp(BmpDib dib, PixelArray data) {
    HWND console = GetConsoleWindow();
    HDC hdc = GetDC(console);

    for (int i = 0; i < dib.imageHeight; ++i) {
        for (int j = 0; j < dib.imageWidth; ++j) {
            Color pixel = data.pixels[i][j];
            SetPixel(hdc, j, i, RGB(pixel.red, pixel.green, pixel.blue));
        }
    }
    ReleaseDC(console, hdc);
}

// Hàm release data:
void releaseBmpPixelArray(PixelArray data) {
    for (int i = 0; i < data.rowCount; ++i) {
        delete[] data.pixels[i];
    }
    delete[] data.pixels;
}
//---------------WRITE BMP ------------------
void writeBmp(string fname, BmpHeader &englandFlag_Header, BmpDib &englandFlag_Dib, PixelArray &data) {
    ofstream fout;
    fout.open(fname, ios::out | ios::binary);
    if (!fout.is_open()) {
        cout << "Can not create the file\n";
        return;
    }
    
    //BmpHeader
    englandFlag_Header.signature = { 'B', 'M' };
    englandFlag_Header.fileSize = 14;
    englandFlag_Header.reserved1 = 0;
    englandFlag_Header.reserved2 = 0;
    englandFlag_Header.dataOffset = 54; 
    fout.write((char*)&englandFlag_Header, sizeof(englandFlag_Header));

    // BmpDib
    // Input the pixel array
    int32_t height, width;
    cout << "Enter the height of the flag: ";
    cin >> height; //504
    cout << "Enter the width of the flag: ";
    cin >> width; //840
    englandFlag_Dib.imageHeight = height;
    englandFlag_Dib.imageWidth = width;

    englandFlag_Dib.dibsSize = 40;

    englandFlag_Dib.colorPlaneCount = 1;
    englandFlag_Dib.pixelSize = 24;         
    englandFlag_Dib.compressMethod = 0;
    englandFlag_Dib.bitmapByteCount = 16;
    englandFlag_Dib.horizontalResolution = 2835;
    englandFlag_Dib.verticalResolution = 2835;
    englandFlag_Dib.colorsCount = 0;
    englandFlag_Dib.importantColorCount = 0;
    fout.write((char*)&englandFlag_Dib, sizeof(englandFlag_Dib));

    //PixelArray
    data.pixels = new Color * [height];
    for (int i = 0; i < height; ++i) {
        data.pixels[i] = new Color[width];
    }

    // Vẽ  | dưới:
    for (int i = 0; i < (height / 7) * 3; ++i) {
        for (int j = (width / 9) * 4; j < (width / 9) * 5; ++j) {
            data.pixels[i][j].blue = { 0 };
            data.pixels[i][j].green = { 0 };
        }
    }

    // Vẽ ngang -:
    for (int i = (height / 7) * 3; i < (height / 7) * 4; ++i) {
        for (int j = 0; j < width; ++j) {
            data.pixels[i][j].blue = { 0 };
            data.pixels[i][j].green = { 0 };
        }
    }

    // Vẽ  | trên:
    for (int i = (height / 7) * 4; i < height; ++i) {
        for (int j = (width / 9) * 4; j < (width / 9) * 5; ++j) {
            data.pixels[i][j].blue = { 0 };
            data.pixels[i][j].green = { 0 };
        }
    }  

    //fout.write((char*)&data, sizeof(data));;
    int padSize = (width*3)%4;
    Color pad = { 0,0,0 };
    for (int i = 0 ; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            fout.write((char*)&data.pixels[i][j], 3);
        }
        fout.write((char*)&pad, padSize);
    }

    fout.close();
}