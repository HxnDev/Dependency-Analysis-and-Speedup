#include <stdio.h>
#include <time.h>
#include <omp.h>

int main()
{
    int m=4, n =16384;
    int i,j;

    double a[m][n];
    double s[m];
    
    double secs = 0;
    clock_t begin = clock();

    #pragma omp parallel num_threads (8)
    {
        #pragma omp for schedule(static, 3)
        for (i=0; i<m; i++) // 24 iterations
        {
            s[i] = 1.0;
            for (j=0; j<n; j++) // 16384 iterations
            {
                s[i] = s[i] + a[i][j];
            }
        }
        
    }
    printf("%f", s[1]);
    clock_t end = clock();
    secs = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("\nTime taken = %f\n", secs);
    return 0;
}