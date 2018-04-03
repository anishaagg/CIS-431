/*
Anisha Aggarwal
LabAssignment2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PNMreader.h"
#include "filters.h"

PNMreader::PNMreader(char *file)
{
	filename = (char *) malloc(strlen(file +1));
	strcpy(filename, file);
}

PNMreader::~PNMreader(void)
{
	free(filename);
}

void PNMreader::Execute(void){
	FILE *file = fopen(filename, "rb");
	char magicNum[128];
	int width, height, maxVal;
	if (file == NULL)
	{
		fprintf(stderr, "Couldn't open file %s\n", filename);
	}
	fscanf(file, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxVal);
	unsigned char *data= (unsigned char*) malloc(sizeof(unsigned char)*3*height*width);
	fread(data, sizeof(unsigned char)*3, width*height, file);
	input.SetSize(width, height);
	input.SetData(data);
	fclose(file);
	free(data);
	//fprintf(stderr, "width: %d height: %d\n", width, height);
}

void PNMreader::Update()
{
	Execute();
}

const char * PNMreader::SourceName()
{
	const char *name = "PNMreader";
	return name;
}

