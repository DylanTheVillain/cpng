
#ifndef CPNGMANIP_H
#define CPNGMANIP_H


#include <png.h>

struct FileInfo
{
	int width;
	int heigth;
	int numberOfPasses;
	png_byte colorType;
	png_byte bitDepth;
	png_structp pngPtr;
	png_infop infoPtr;
	png_bytep * rowPointers;
};

struct FileInfo ReadInFile(char * fileName);  //Reads in a file and returns a struct that represents an image.
void WriteToFile(char * fileName, struct FileInfo file); //Writes an image struct to a png file.
struct FileInfo MakeImageStruct(int width, int heigth); //Makes a new image struct.
#endif
