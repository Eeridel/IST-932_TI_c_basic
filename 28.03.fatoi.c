#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fatoi(const char* str)
{
    int i, N;
    N = strlen(str);
    int a[N];
    printf("\nString in digits: ");
    for(i = 0; i < N; i++)
    {
       a[i] = (int)str[i];
       printf("%d ", a[i]);
    }
}

int main()
{
    int i, n, len;
    const char str[] = "Diavolo is imbalance";
    printf("\nString: %21s", str);
    fatoi(str);
    return 0;
}
