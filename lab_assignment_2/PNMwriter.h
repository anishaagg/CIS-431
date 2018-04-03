#include "sink.h"
#ifndef PNMWRITER_H
#define PNMWRITER_H

class PNMwriter:public Sink
{
	public:
		void Write(char *);
		virtual const char *SinkName();
};

#endif
