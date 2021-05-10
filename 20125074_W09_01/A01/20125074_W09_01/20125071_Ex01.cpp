#include "BMP.h"
// Tỉ lệ cờ: 3-5

int main() {
    //Set up data:
    BmpHeader englandFlag_Header;
    BmpDib englandFlag_Dib;
    PixelArray data;

    writeBmp("output.bmp", englandFlag_Header, englandFlag_Dib, data);

    releaseBmpPixelArray(data);
    return 0;
}