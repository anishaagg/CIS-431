/*
Anisha Aggarwal
LabAssignment1
Sources: https://stackoverflow.com/questions/3220477/how-to-use-clock-in-c
    Based off of CIS330 project.
*/

#include <ctime>
#include <PNMreader.h>
#include <PNMwriter.h>
#include <filters.h>
#include <sink.h>

int main(int argc, char *argv[])
{
    PNMreader reader(argv[1]);

    Invert i;
    i.SetInput(reader.GetOutput());
    i.GetOutput()->Update();

    PNMwriter writer;
    writer.SetInput(i.GetOutput());
    writer.Write(argv[2]);

}
