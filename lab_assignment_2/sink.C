#include "sink.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Sink::Sink(void)
{
	input1 = NULL;
	input2 = NULL;
}

Sink::~Sink()
{
}

void Sink::SetInput(Image *_input)
{
	input1 = _input;
}

void Sink::SetInput2(Image *_input2)
{
	input2 = _input2;
}


