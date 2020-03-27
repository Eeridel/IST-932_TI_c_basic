#include <stdio.h>
#include <stdlib.h>

char* str_chr(char* s, char c)
{
    int i;
    for(i = 0; s[i] != 0; i++)                          /* Loop iterating over characters from s [0] to the last                  */
        if(s[i] == c) return &s[i];
    return 0;
}

int main()
{
    char a[31] = { 0 }, b;

    printf("\nEnter text:");
    gets(a);
    printf("\nEnter char:");
    b = getchar();

    if(str_chr(a, b) != 0)
        printf("\nYour char address in string: %d", str_chr(a, b));
    else
        printf("\nThere is no such character");
        printf("\nThere is no such character");

    return 0;
}
