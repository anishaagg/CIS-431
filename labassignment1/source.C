/*
Anisha Aggarwal
LabAssignment1
Sources:
    Based off of CIS330 project.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "source.h"

Source::Source(void)
{
	input.SetSrc(this);
}

Source::~Source()
{
}

Image * Source::GetOutput(void)
{
	return &input;
}

void Source::Update()
{
	Execute();
}

Color::Color(int width, int height, int red, int green, int blue)
{
	int i, j;
	unsigned char *data = (unsigned char *) malloc(width*height*3);
	input.SetSize(width, height);
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			int x = (i*height+j);
			data[3*x] = red;
			data[3*x+1] = green;
			data[3*x+2] = blue;
		}
	}
	
	input.SetData(data);
	free(data);
}

void Color::Execute()
{
}

const char * Color::SourceName()
{
}



