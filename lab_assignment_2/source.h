#include "image.h"
#ifndef SOURCE_H
#define SOURCE_H

class Source
{
	protected:
		Image input;
		virtual void Execute() = 0;
	
	public:
		Source();
		~Source();
		virtual void Update();
		virtual Image * GetOutput();
		virtual const char * SourceName() = 0;
};

class Color:public Source
{
	public:
		Color(int w, int h, int r, int g, int b);
		virtual void Execute();
		virtual const char * SourceName();
};

#endif

