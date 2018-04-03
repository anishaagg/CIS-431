#include "source.h"
#ifndef PNMREADER_H
#define PNMREADER_H

class PNMreader:public Source
{
	private:
		char *filename; 
	public:
		PNMreader(char *file);
		~PNMreader();
		virtual void Execute();
		virtual void Update();
		const char *SourceName();
};

#endif
