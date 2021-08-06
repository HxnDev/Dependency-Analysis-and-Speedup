#include <stdio.h>
#include <time.h>
#include <omp.h>

#define N 800

int function_call(int j){
    int a;
    a = 2*2+j;
    return a;
}

int main()
{ 
    int i,j;
    int a[N][N];
    int b[N][N];
    int c[N][N];
    double secs = 0;
    clock_t begin = clock();

    #pragma omp parallel num_threads(2)
    {
        for (i=1; i<N; i++){
            for (j=0; j<N; j++){
                b[i-1][j] = function_call(j);
            }
        }
    }
    

    #pragma omp parallel num_threads(2)
    {
        #pragma omp for schedule(static,395)
        for (j=1; j<N-10; j++){
            for (i=0; i<N-10; i++){
                a[i][j+2] = b[i+2][j];
                c[i+1][j] = b[i][j+3];
            }
        }
    }
    
    clock_t end = clock();
    secs = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("\nTime taken = %f\n", secs);
    return 0;
}