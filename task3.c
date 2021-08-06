#include <stdio.h>
#include <time.h>
#include <omp.h>
#define N 1024

int main()
{
    int i,j;
    int X[N][N];
    int Y[N];
    int Z[N];
    int k=1;
    
    double secs = 0;
    clock_t begin = clock();

    #pragma omp parallel num_threads(2)
    {
        #pragma omp for schedule(static,512)
        for (i=0; i<N; i++)
        {
            Y[i] = k;
            k=k*2;
            Z[i] = -1;
            for (j=0; j<N; j++)
            {
                X[i][j] =2;
            }
        }
    }

    #pragma omp parallel num_threads(2)
    {
        #pragma omp for schedule(static,512)
        for (i=0; i<N; i++)
        {
            for (j=0; j<N; j++)
            {
                Z[i] += Y[j] + X[i][j];
            }
        }
    }
    clock_t end = clock();
    secs = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("\nTime taken = %f\n", secs);
    return 0;
}