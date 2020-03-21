#include <stdio.h>                                      /* comment */
#include <stdlib.h>

int count_digits(char* s)                               /* Function address of the zero character of the string                   */
{
    int i, j, cd = 0;                                   /* cd - variable for counting digits                                      */
    char a[11];                                         /* A string of 10 characters (1 cell for "/ 0")                           */

    for(i = 0; i < 10; i++) a[i] = i + '0';             /* Filling a string with numbers from 0 to 9                              */

    for(i = 0; s[i] != 0; i++)                          /* Loop iterating over characters from s [0] to the last                  */
        for(j = 0; j < 10; j++)                         /* Loop iterating over characters of a string with numbers from 0 to 9    */
            if(s[i] == a[j]) cd++;                      /* Compares the current character with all digits                         */

    return cd;
}

int main()
{
    char a[31];

    printf("\nEnter text:");
    scanf("%30s", a);                                   /* Enter 30 characters in string "a"                                      */
    printf("\nYour text: %s", a);
    printf("\nDigits count in your text: %d", count_digits(a));

    return 0;
}
