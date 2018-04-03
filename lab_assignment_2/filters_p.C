/*
Anisha Aggarwal
LabAssignment2
*/

#include <iostream>
#include <cstdio>
#include "source.h"
#include "sink.h"
#include "filters.h"
#include <stdio.h>
#include <stdlib.h>
#include "tbb/tbb.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "timing.h"
using namespace tbb;

void Filter::Execute()
{
}

void Filter::Update()
{
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

unsigned char * in_buffer;
unsigned char * out_buffer; 

void parallel_execute(int index){

	//std::cout << "parallel_for\n";
	out_buffer[index] = 255 - in_buffer[index];

}

#ifdef STEP_2	// STEP_2

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

	//reset_and_start_timer();

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

	//double dt = get_elapsed_mcycles();
    //printf("@time of serial run:\t\t\t[%.3f] million cycles\n", dt);
	
	input.SetData(data);
	free(data);

}

#else // STEP_1 or STEP_3

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

	in_buffer = input1->GetData();

	// setup output image
	unsigned char *data = (unsigned char *) malloc(width*height*3);

	out_buffer = data;

	//reset_and_start_timer();
		//std::cout << "parallel_for call\n";
	
	tbb::parallel_for(0, 3*width*height, parallel_execute);
		//std::cout << "parallel_for done\n";

	//double dt = get_elapsed_mcycles();
    //printf("@time of serial run:\t\t\t[%.3f] million cycles\n", dt);
	

	input.SetData(data);
	free(data);

}

#endif //Step 2


const char * Invert::FilterName()
{
	return "Invert";
}


