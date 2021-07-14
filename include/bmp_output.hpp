//#pragma once
//#pragma pack(2) 

 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
//#include "QrCode.hpp"
//#include <cstdint>
//#include <cstdlib>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;
//typedef unsigned char BYTE;
typedef uint8_t  BYTE;
//typedef unsigned short WORD;
typedef uint16_t WORD;
//typedef unsigned long  DWORD;
typedef uint32_t DWORD;
//typedef long    LONG;
typedef uint64_t    LONG;
typedef struct {
    WORD    bfType; // Graphic type
    DWORD   bfSize;
    // The size of the interval from the beginning of the file to the storage location
    // of the image data: file header + information header + palette
    WORD    bfReserved1; // Two reserved variables, set to 0
    WORD    bfReserved2;
    DWORD   bfOffBits; //
    // The size of the interval from the beginning of the file to the storage location
    // of the image data: file header + information header + palette + image data

} BITMAPFILEHEADER;  // Define the structure of the header information of the bmp file

typedef struct {
    DWORD      biSize;// Message header size
//    LONG       biWidth; // Image width (in pixels)
    DWORD       biWidth; // Image width (in pixels)
//    LONG       biHeight;
    DWORD       biHeight;
    WORD       biPlanes; // Target device level, must be 1
    WORD       biBitCount;
    // Color depth, pixel type, must be: monochrome (1), 16 colors (4), 256 colors (8), true color (24)
    DWORD      biCompression;
    // The compression method must be: 0, no compression; 1 or 2;
    DWORD      biSizeImage;  // The entire image data size
//    LONG       biXPelsPerMeter;  // Horizontal resolution (unit: pixel/meter)
    DWORD       biXPelsPerMeter;  // Horizontal resolution (unit: pixel/meter)
//    LONG       biYPelsPerMeter;  // Vertical resolution
    DWORD       biYPelsPerMeter;  // Vertical resolution
    DWORD      biClrUsed;  // Colors used in BMP images
    DWORD      biClrImportant;  // Number of important colors
} BITMAPINFOHEADER;  // File header

typedef struct tagRGBQUAD {
BYTE    rgbBlue;
BYTE    rgbGreen;
BYTE    rgbRed;
BYTE    rgbReserved;
} RGBQUAD; // Color palette
