/*
Anisha Aggarwal
LabAssignment1
Sources:
    Based off of CIS330 project.
*/
#include <iostream>
#include <cstdio>
#include "source.h"
#include "sink.h"
#include "filters.h"
#include <stdio.h>
#include <stdlib.h>
#include "timing.h"

void Filter::Execute()
{
}

void Filter::Update()
{
	char msg[128];
	if (input1 != NULL) 
	{
		input1->Update();
	}
	if (input2 != NULL)
	{
		input2->Update();
	}

	Execute();

}

void Invert::Execute()
{
	std::clock_t start;

	if (input1 == NULL)
	{
		return;
	}
	
	int height = input1->GetHeight();
	int width = input1->GetWidth();
	input.SetSize(width, height);
	
	unsigned char *data = (unsigned char *) malloc(width*height*3);
	
	int i, j;

	reset_and_start_timer();

	for (i = 0; i < width; i++)
	{
		
		for (j = 0; j < height; j++)
		{
			int x = (i*height+j);
			data[3*x] = 255-(input1->GetData()[3*x]);
			data[3*x+1] = 255-(input1->GetData()[3*x+1]);
			data[3*x+2] = 255-(input1->GetData()[3*x+2]);
		}

	}

	double dt = get_elapsed_mcycles();
    printf("@time of serial run:\t\t\t[%.3f] million cycles\n", dt);
	
	input.SetData(data);
	free(data);

}

const char * Invert::FilterName()
{
	return "Invert";
}


