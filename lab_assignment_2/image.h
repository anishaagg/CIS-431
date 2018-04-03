#include <stdio.h>
#ifndef IMAGE_H
#define IMAGE_H

class Source;

class Image 
{
	private:
		int Height, Width;
		unsigned char *buffer;
		Source *src;
	public:
		Image();
		Image(int height, int width, unsigned char *b);
		Image(Image &i);

		void SetSize(int width, int height);
		void SetData(unsigned char *b);
		int GetHeight();
		int GetWidth();
		unsigned char * GetData();
		void Update();
		void SetSrc(Source *);
};

#endif

