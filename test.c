#include <stdio.h>
#include <time.h>
#include <omp.h>

int main()
{
    int x = 1;
    double secs = 0;
    clock_t begin = clock();
    #pragma omp parallel num_threads (2)
    {
        #pragma omp for schedule (static, 400)
        for (int i = 0; i<800; i++)
        {
            //printf("%d",x);
            x++;
        }
    }
    clock_t end = clock();
    secs = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("\nTime taken = %f\n", secs);
    return 0;
}