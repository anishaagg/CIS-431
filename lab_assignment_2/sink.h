#include "image.h"
#ifndef SINK_H
#define SINK_H

class Sink
{
	protected:
		Image *input1;
		Image *input2;
		
	public:
		Sink();
		~Sink();
		virtual void SetInput(Image *);
		virtual void SetInput2(Image *);
		virtual const char * SinkName() = 0;
};

#endif
