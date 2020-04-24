#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define wordlen 20
#define words 5

int main()
{
    char dictBuf[words][wordlen];
    int i = 0, j = 0;
    int word_count = 0;
    char word[wordlen];


    while(word_count < words)
    {
        printf("%d. ", i);
        scanf("%s", word);
        strcpy(dictBuf[word_count++], word);
        i++;
    };


    for(i = 0; i < word_count; i++)
        for(j = i + 1; j < word_count; j++)
        {
            if(strlen(dictBuf[i]) < strlen(dictBuf[j]))
            {
                strcpy(word, dictBuf[j]);
                strcpy(dictBuf[j], dictBuf[i]);
                strcpy(dictBuf[i], word);
            }
        };


    printf("\n");
    printf("Sort by lenght\n");
    for(i = 0; i < word_count; i++)
    {
        printf("%d. %s\n", i, dictBuf[i]);
    };


    for(i = 0; i < word_count; i++)
        for(j = i + 1; j < word_count; j++)
        {
            if(strcmp(dictBuf[i], dictBuf[j]) >= 0)
            {
                strcpy(word, dictBuf[j]);
                strcpy(dictBuf[j], dictBuf[i]);
                strcpy(dictBuf[i], word);
            }
        };


    printf("\n");
    printf("Sort by alphabet\n");
    for(i = 0; i < word_count; i++)
    {
        printf("%d. %s\n", i, dictBuf[i]);
    };


    printf("\n");
    printf("Search by word. Enter the word: ");
    scanf("%s", word);
    printf("Found: \n");
    for(i = 0; i < word_count; i++)
    {
        if(!strcmp(dictBuf[i], word))
        {
            printf("%d. %s\n", i, dictBuf[i]);
        }
    };


    printf("\n");
    printf("Search by first letter. Enter the letter: ");
    scanf("%s", word);
    printf("Found: \n");
    for(i = 0; i < word_count; i++)
    {
        if(strchr(dictBuf[i], (int)word[0]))
        {
            printf("%d. %s\n", i, dictBuf[i]);
        }
    };

    return 0;
}
