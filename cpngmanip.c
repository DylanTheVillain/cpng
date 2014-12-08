#include "cpngmanip.h"
#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include <string.h>

int x=0;
int y=0;

struct FileInfo ReadInFile(char * fileName)
{
	struct FileInfo newFile;
	FILE * fi=fopen(fileName,"rb");
	char header[8];
	fread(header,1,8,fi);
	if(png_sig_cmp(header,0,8))
	{
		printf("%s\n","File not a png!");
		abort();
	}
	newFile.pngPtr=png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
	newFile.infoPtr=png_create_info_struct(newFile.pngPtr);
	png_init_io(newFile.pngPtr,fi);
	png_set_sig_bytes(newFile.pngPtr,8);
	png_read_info(newFile.pngPtr,newFile.infoPtr);
	newFile.width=png_get_image_width(newFile.pngPtr,newFile.infoPtr);
	newFile.heigth=png_get_image_height(newFile.pngPtr,newFile.infoPtr);
	newFile.colorType=png_get_color_type(newFile.pngPtr,newFile.infoPtr);
	newFile.bitDepth=png_get_bit_depth(newFile.pngPtr,newFile.infoPtr);
	newFile.numberOfPasses=png_set_interlace_handling(newFile.pngPtr);
	png_read_update_info(newFile.pngPtr,newFile.infoPtr);
	newFile.rowPointers=malloc(newFile.heigth*sizeof(png_bytep));
	for (y=0;y<newFile.heigth;y++)
	{
		newFile.rowPointers[y]=malloc(png_get_rowbytes(newFile.pngPtr,newFile.infoPtr));
	}
	png_read_image(newFile.pngPtr,newFile.rowPointers);
	fclose(fi);
	return newFile;
}
void WriteToFile(char * fileName, struct FileInfo file)
{
	FILE * fi=fopen(fileName,"wb");
	file.pngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    file.infoPtr = png_create_info_struct(file.pngPtr);
	png_init_io(file.pngPtr,fi);
	png_set_IHDR(file.pngPtr,file.infoPtr,file.width,file.heigth,file.bitDepth,file.colorType,PNG_INTERLACE_NONE,PNG_COMPRESSION_TYPE_BASE,PNG_FILTER_TYPE_BASE);
	png_write_info(file.pngPtr,file.infoPtr);
	png_write_image(file.pngPtr,file.rowPointers);
	png_write_end(file.pngPtr,NULL);
	fclose(fi); 
}
struct FileInfo MakeImageStruct(int width, int heigth)
{
	struct FileInfo newImg;
	newImg.pngPtr=png_create_write_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
	newImg.infoPtr=png_create_info_struct(newImg.pngPtr);
	newImg.numberOfPasses=png_set_interlace_handling(newImg.pngPtr);
	newImg.colorType=PNG_COLOR_TYPE_RGB;
	newImg.width=width;
	newImg.heigth=heigth;
	newImg.bitDepth=8;
	png_read_update_info(newImg.pngPtr,newImg.infoPtr);
	newImg.rowPointers=malloc(newImg.heigth*sizeof(png_bytep));
	for (y=0;y<newImg.heigth;y++)
	{
		newImg.rowPointers[y]=malloc(3*newImg.width);
	}
	for (y=0;y<newImg.heigth;y++)
	{
		for (x=0;x<newImg.width*3;x++)
		{
			newImg.rowPointers[y][x]=0;
		}
	}
	return newImg;
}