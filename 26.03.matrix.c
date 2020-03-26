#include <stdio.h>                                                                                                                                                                                          /* Eeridel */
#include <stdlib.h>
#include <limits.h>
#define M 10
#define N 10
#define L 100

int main()
{
    int i, j, k, n, temp_min, temp_max, a[M][N], min_N[N], min_M[M], max_M[M];

    srand(time(NULL));

    printf("\n1.\n");
    for(i = 0; i < M; i++)
    {
        for(j = 0; j < N; j++)
        {
            a[i][j] = rand() % L;
            printf("    a[%d][%d] = %d", i, j, a[i][j]);
        }
        printf("\n");
    }

    for(j = 0; j < N; j++)
    {
        temp_min = INT_MAX;
        for(i = 0; i < M; i++)
        {
            if(a[i][j] < temp_min)
            {
                temp_min = a[i][j];
            }
        }
        min_N[j] = temp_min;
    }
    for(i = 0; i < N; i++) printf("\n    min[0..%d][%d] = %d", M - 1, i, min_N[i]);

    printf("\n2.\n");
    for(i = 0; i < M; i++)
    {
        temp_max = INT_MIN;
        temp_min = INT_MAX;
        for(j = 0; j < N; j++)
        {
            if(a[i][j] < temp_min)
            {
                temp_min = a[i][j];
            }
            if(a[i][j] > temp_max)
            {
                temp_max = a[i][j];
            }
        }
        min_M[i] = temp_min;
        max_M[i] = temp_max;
    }
    for(i = 0; i < M; i++)
    {
        for(j = 0; j < N; j++)
        {
            if(a[i][j] == min_M[i])
                a[i][j] = max_M[i];
            else
            if(a[i][j] == max_M[i])
                a[i][j] = min_M[i];
        }
    }

    for(i = 0; i < M; i++)
    {
        for(j = 0; j < N; j++)
        {
            printf("    a[%d][%d] = %d", i, j, a[i][j]);
        }
        printf("\n");
    }







    return 0;
}
