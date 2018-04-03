/*
Anisha Aggarwal
LabAssignment1 - serial program 
Sources:
    Based off of CIS330 project.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PNMwriter.h"


void PNMwriter::Write(char *name)
{
	FILE *file = fopen(name, "wb");
	fprintf(file, "%s\n%d %d\n%d\n", "P6", input1->GetWidth(), input1->GetHeight(), 255);
	fwrite(input1->GetData(), sizeof(unsigned char)*3, input1->GetWidth()*input1->GetHeight(), file);
	fclose(file);
} 

const char * PNMwriter::SinkName()
{
	const char *name = "PNMwriter";
	return name;
}
