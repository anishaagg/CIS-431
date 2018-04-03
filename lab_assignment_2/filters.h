#ifndef FILTERS_H
#define FILTERS_H

#include "source.h"
#include "sink.h"
#include "image.h"
#include <stdio.h>

class Filter:public Source, public Sink
{
	void Update();
	virtual void Execute();
	virtual const char * FilterName() = 0;
	public:
		const char * SourceName(){ return FilterName();};
		const char * SinkName(){ return FilterName();};

};

class Invert:public Filter
{
/*	private:
		unsigned char * in_buffer;
		unsigned char * out_buffer;
		*/

	public:
		virtual void Execute();
		virtual const char * FilterName();
		//void parallel_execute(int);
};

#endif
