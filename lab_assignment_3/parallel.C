#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <utility>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
#include <omp.h>

#define NITERS 10000
#define N 100

using namespace std;

int main(int argc, char* argv[])
{

    if (argc < 2) {
        printf("Errof in number of inputs\n");
        return -1;
    } 

    omp_set_num_threads(atoi(argv[1]));
    int n = NITERS;
    double** input_temp = new double*[N+2];
    double** output_temp = new double*[N+2];

    auto start = Clock::now();

    for(int i = 0; i < N+2; i++)
    {
        input_temp[i] = new double[N+2];
        output_temp[i] = new double[N+2];
    }

    int i,j;

    for(i = 0; i < N+2; i++)
    {
        for(j = 0; j < N+2; j++)
        {
            input_temp[i][j] = -100;
            output_temp[i][j] = -100;
        }
    }

    for(int i = 0; i < N+2; i++)
    {
        input_temp[0][i] = 100;
        input_temp[N+1][i] = 100;
        input_temp[i][0] = 100;
        input_temp[i][N+1] = 100;
        output_temp[0][i] = 100;
        output_temp[N+1][i] = 100;
        output_temp[i][0] = 100;
        output_temp[i][N+1] = 100;
    }


    /*for(int i = 0; i < N+2; i++)
    {
            for(int j = 0; j < N+2; j++)
            {
                    cout << output_temp[i][j] <<" ";
            }
            cout << endl;
    }*/

    double c, delta_t, delta_s;

    c = 0.1;
    delta_s = 1.0/(N+1);
    double delta_s2 = (delta_s*delta_s);
    delta_t = (delta_s2)/(4*c);
    double** temp = NULL;

    int chunksize = n/5;

    for(int iter = 0; iter < NITERS; iter++)
    {
        #pragma omp parallel private(i,j)
        for(int i = 1; i < N+1; i++)
        {
            #pragma omp for nowait, schedule(dynamic, chunksize)
            for(int j = 1; j < N+1; j++)
            {
                output_temp[i][j] = input_temp[i][j] + c * (delta_t/delta_s2) *
                    (input_temp[i+1][j] + input_temp[i-1][j] - 4*input_temp[i][j]
                        + input_temp[i][j+1] + input_temp[i][j-1]);
            }
        }

        #pragma omp for nowait, schedule(dynamic, chunksize)
        for (int i = 0; i < n+2; i++){
            for (int j = 0; j < n+2; j++) {
                temp = input_temp;
                input_temp = output_temp;
                output_temp = temp;
            }
            
        }
        
    }

    double min_temp = 1000;
    int min_i, min_j;
    for (int i = 0; i < n+2; i++) {
        for (int j = 0; j < n+2; j++) {
            if (output_temp[i][j] < min_temp) {
                min_temp = output_temp[i][j];
                min_i = i;
                min_j = j;
            }
        }
    }

    auto stop = Clock::now();

    std::cout << "Timer: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
        << " milliseconds\n";

    printf("min temp is %3.7f\n", temp);

    /*for(int i = 0; i < N+2; i++)
    {
            for(int j = 0; j < N+2; j++)
            {
                    cout << output_temp[i][j] <<" ";
            }
            cout << endl;
    }*/

    return 0;
}