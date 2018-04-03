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
#include "filters_ph_ispc.h"
using namespace ispc;
#include "timing.h"


struct image_ISPC {
	int		height;
	int 	width;
	unsigned char	*buffer;
};

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
	/*std::clock_t start;*/

	if (input1 == NULL)
	{
		return;
	}
	
	int height = input1->GetHeight();
	int width = input1->GetWidth();
	input.SetSize(width, height);
	
	int i, j;

	ispc::image_ISPC	image_in, image_out;

	// setup input image
	image_in.height = input1->GetHeight();
	image_in.width = input1->GetWidth();
	image_in.buffer = input1->GetData();


	// setup output image
	unsigned char *data = (unsigned char *) malloc(width*height*3);

	image_out.height = image_in.height;
	image_out.width = image_in.width;
	image_out.buffer = data;

	reset_and_start_timer();

	parallel_execute(image_in, image_out);
	/*
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
	*/
	
	double dt = get_elapsed_mcycles();
    printf("@time of serial run:\t\t\t[%.3f] million cycles\n", dt);

	input.SetData(data);
	free(data);

}

const char * Invert::FilterName()
{
	return "Invert";
}


