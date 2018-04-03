#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <utility>

#define NITERS 10090
#define N 100

using namespace std;

int main(int argc, char* argv[])
{

    double** input_temp = new double*[N+2];
    double** output_temp = new double*[N+2];
    for(int i = 0; i < N+2; i++)
    {
        input_temp[i] = new double[N+2];
        output_temp[i] = new double[N+2];
    }

    for(int i = 0; i < N+2; i++)
    {
        for(int j = 0; j < N+2; j++)
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

    for(int iter = 0; iter < NITERS; iter++)
    {
        for(int i = 1; i < N+1; i++)
        {
            for(int j = 1; j < N+1; j++)
            {
                output_temp[i][j] = input_temp[i][j] + c * (delta_t/delta_s2) *
                    (input_temp[i+1][j] + input_temp[i-1][j] - 4*input_temp[i][j]
                        + input_temp[i][j+1] + input_temp[i][j-1]);
            }
        }

        temp = input_temp;
        input_temp = output_temp;
        output_temp = temp;

    }

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