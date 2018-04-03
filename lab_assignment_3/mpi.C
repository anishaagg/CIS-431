#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
using namespace std;

#define NITERS 10
#define N 100

int main(int argc, char** argv){

	int numProc;
	int myID;

	MPI_Init(&argc, &argv);
	
	MPI_Comm_size(MPI_COMM_WORLD, &numProc);
	MPI_Comm_rank(MPI_COMM_WORLD, &myID);
	
	int lastProc = myID - 1;
	int nextProc = myID + 1;
	
	if(lastProc < 0) lastProc = MPI_PROC_NULL;
	if(nextProc >= numProc) nextProc = MPI_PROC_NULL;
	
	// 100 / 4 = 25 (rows)	
    int partition_size = (N)/(numProc);
	
	std::cout << "Rank: " << myID << " partition size: " << partition_size <<"\n";
    double** input_temp = new double*[partition_size+2];
 	double** output_temp = new double*[partition_size+2];
    				
    for (int i = 0; i < partition_size+2; i++) {
		input_temp[i] = new double[N+2];
		output_temp[i] = new double[N+2];
	}

	for (int i = 0; i < partition_size+2; i++) {
		for (int j = 0; j <N+2; j++) {
			input_temp[i][j] = -100.0;
			output_temp[i][j] = -100.0;
		}
	}
	
	if (myID == 0) {
		for (int i = 0; i < N+2; i++) {
			input_temp[0][i] = 100.0;
			output_temp[0][i] = 100.0;
		}
	} else if (myID == numProc - 1) {
		for (int i = 0; i < N + 2; i++){
			input_temp[partition_size+1][i] = 100.0;
			output_temp[partition_size+1][i] = 100.0;	
		}
	}
	
	for (int i = 0; i < partition_size+2; i++)
	{
		input_temp[i][0] = 100.0;
		input_temp[i][N+1] = 100.0;
		output_temp[i][0] = 100.0;
		output_temp[i][N+1] = 100.0;
	}

	double c, delta_t, delta_s;
	c = 0.1;
	delta_s = 1.0/(N+1);
	delta_t = (delta_s*delta_s)/(4*c);
	double** temp = NULL;
	
	MPI_Request request1, request2;
	MPI_Status stat1, stat2;	

	for(int iter = 0; iter < NITERS; iter++) {
		for(int i = 1; i < partition_size+1; i++) {
			for(int j = 1; j < N+1; j++) {
				output_temp[i][j] = input_temp[i][j] + c*(delta_t/(delta_s*delta_s)) * (input_temp[i+1][j]+input_temp[i-1][j] - 4*input_temp[i][j] + input_temp[i][j+1] +input_temp[i][j-1]);
			}
		}
		MPI_Isend(output_temp[1], N+3, MPI_DOUBLE, lastProc, 1, MPI_COMM_WORLD, &request1);
		MPI_Isend(output_temp[partition_size], N+3, MPI_DOUBLE, nextProc, 1, MPI_COMM_WORLD, &request2); 

		MPI_Recv(input_temp[0], N+3, MPI_DOUBLE, lastProc, 1, MPI_COMM_WORLD, &stat1);
		MPI_Recv(input_temp[partition_size+1], N+3, MPI_DOUBLE, nextProc, 1, MPI_COMM_WORLD, &stat2);	
			
	/*	if ((myID % 2) == 0)
		{
			MPI_Send(&output_temp[1], N+2, MPI_DOUBLE, lastProc, 0, MPI_COMM_WORLD);
			MPI_Send(&output_temp[partition_size], N+2, MPI_DOUBLE, nextProc, 0, MPI_COMM_WORLD);
		}
		else
		{
			MPI_Recv(&input_temp[0], N+2, MPI_DOUBLE, lastProc, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&input_temp[partition_size], N+2, MPI_DOUBLE, nextProc, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);		
		}
		
		if((myID % 2) == 1)
		{
			MPI_Send(&output_temp[1], N+2, MPI_DOUBLE, lastProc, 0, MPI_COMM_WORLD);
			MPI_Send(&output_temp[partition_size], N+2, MPI_DOUBLE, nextProc, 0, MPI_COMM_WORLD);
		}
		else
		{
			MPI_Recv(&input_temp[0], N+2, MPI_DOUBLE, lastProc, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&input_temp[partition_size], N+2, MPI_DOUBLE, nextProc, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);		
		}*/
		
		temp = input_temp;
		input_temp = output_temp;
		output_temp = temp;
	}
		
	fprintf(stderr, "rank = %d, past heat\n", myID);
	fprintf(stderr, "rank = %d, heat = %f\n", myID, output_temp[1][1]);
	MPI_Finalize();
	
	return 0;	
}	




									
