/*
Anisha Aggarwal
LabAssignment1 - serial program 
Sources:
    Based off of CIS330 project.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "source.h"


Image::Image(void)
{
	Height = 0;
	Width = 0;
	buffer = NULL;
}

Image::Image(int height, int width, unsigned char *b)
{
	Height = height;
	Width = width;
	buffer = (unsigned char *)malloc(3*Height*Width);
	memcpy(buffer, b, 3*Height*Width);
}

Image::Image(Image &i)
{
	buffer = (unsigned char *)malloc(3*Height*Width);
	Height = i.GetHeight();
	Width = i.GetWidth();
	memcpy(buffer, i.GetData(), 3*Height*Width);
}

void Image::SetSize(int width, int height)
{
	Width = width;
	Height = height;
}

void Image::SetData(unsigned char *b)
{
	if (buffer == NULL)
	{
		buffer = (unsigned char *)malloc(3*Width*Height);
	}
	memcpy(buffer, b, 3*Width*Height);
}

int Image::GetWidth()
{
	return Width;
}

int Image::GetHeight()
{
	return Height;
}

unsigned char* Image::GetData()
{
	return buffer;
} 

void Image::Update()
{
	src->Update();
}

void Image::SetSrc(Source *source)
{
	src = source;
}
