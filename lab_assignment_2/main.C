/*
Anisha Aggarwal
LabAssignment2
*/

#include <PNMreader.h>
#include <PNMwriter.h>
#include <filters.h>
#include <sink.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "timing.h"
#include "tbb/tbb.h"
#include "tbb/task_scheduler_init.h"
using namespace tbb;

class MyTask: public task {
	private:
		std::string Infile;
		std::string Outfile;
	public:
	// Constructor
	MyTask(std::string In, std::string Out) {
		Infile = In;
		Outfile = Out;
	}

	// Execute function
	tbb::task *execute() {
    	PNMreader reader((char*)Infile.c_str());

	    Invert i;
   	 	i.SetInput(reader.GetOutput());
   	 	i.GetOutput()->Update();

	    PNMwriter writer;
    	writer.SetInput(i.GetOutput());
    	writer.Write((char*)Outfile.c_str());

    	//std::cout << "MyTask\n";
    	return NULL;
	}
};

class RootTask: public task {
	private:
		std::string *Infiles;
		std::string *Outfiles;
		int		FileCount;

	public:
	// Constructor
	RootTask(std::string *in, std::string *out, int n) {
		Infiles = in;
		Outfiles = out;
		FileCount = n;
	};

	// Execute function
	tbb::task *execute() {
		int	i;
		task_list	list1;

		// Create tasks to process each file
		for (i=0; i<FileCount; i++) {
			list1.push_back( *new (allocate_child()) MyTask(Infiles[i], 
															   Outfiles[i]));
		}
		set_ref_count(FileCount+1);
		spawn_and_wait_for_all(list1);
		return NULL;
	}
};

using namespace std;
int main(int argc, char *argv[])
{
	string in_files[20];
	string out_files[20];
	ifstream file;

	if (argc < 2) {
		printf("file not specified\n");
		return 1;
	}

	file.open(argv[1]);

	int FileCount = 0;
	for(int i = 0; i < 20; i++) {
		if (getline(file, in_files[i])){
			//std::cout << in_files[i] << '\n';
			
			#ifdef STEP_1
			out_files[i] = "STEP_1/";
			#endif

			#ifdef STEP_2
			out_files[i]= "STEP_2/";
			#endif

			#ifdef STEP_3
			out_files[i] = "STEP_3/";
			#endif

			//std::cout << out_files[i] << '\n';


			int index = in_files[i].find_last_of("/");
			out_files[i] += in_files[i].substr(index+1);

			//std::cout << out_files[i] << '\n';

			FileCount++;
		}
		else{
			break;
		}
	}

	reset_and_start_timer();

	#ifdef STEP_1

	for (int i = 0; i < FileCount; i++) {
		//std::cout << "in STEP_1" << '\n';
		//std::cout << (char*)in_files[i].c_str() << '\n';
		PNMreader reader((char*)in_files[i].c_str());

	    Invert invert;
   	 	invert.SetInput(reader.GetOutput());
   	 	invert.GetOutput()->Update();

	    PNMwriter writer;
    	writer.SetInput(invert.GetOutput());
    	writer.Write((char*)out_files[i].c_str());
	}

	#else
	// Create TBB tasks to process them	
	tbb::task_scheduler_init init(tbb::task_scheduler_init::automatic);
	RootTask& R = *new(tbb::task::allocate_root()) RootTask(in_files, 
															out_files, 
															FileCount);
	tbb::task::spawn_root_and_wait(R);
	#endif
	
	double dt = get_elapsed_mcycles();
    printf("@time of run:\t\t\t[%.3f] million cycles\n", dt);
    
    return 0;

}
