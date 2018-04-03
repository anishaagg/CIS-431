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
	public:
		virtual void Execute();
		virtual const char * FilterName();
};


