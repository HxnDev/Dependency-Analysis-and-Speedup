#include <stdio.h>
#include <time.h>
#include <omp.h>
#define N 1024

int main()
{
    int i, k =10;
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    int c[1000];
    int b[N][N];
    int loc = -1;
    int tmp= -1;
    double secs = 0;
    clock_t begin = clock();

    for (i =0; i<k; i++){
        b[i][k] = b[a[i]][k];
    }
    printf("%d %d", a[0], b[0][0]);

    for (i = 0; i<1000; i++){
        tmp = tmp+1;
        c[i] = tmp;
    }

    #pragma omp parallel num_threads(8)
    {
        #pragma omp for schedule(static,125)
        for (i=0; i<1000; i++){
            if (c[i]%4 == 0){
                loc = i;
            }
        }
    }
    clock_t end = clock();
    secs = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("\nTime taken = %f\n", secs);
    return 0;
}