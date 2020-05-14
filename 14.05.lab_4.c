 /* Глобальная переменная, необходимая функции освобождения выделенной памяти */
int WordNum;

/*Функция создания свободного массива со словарём*/
char** DictMem() 
{
    /* Определение размера файла */
    FILE* fDict = OpenDict("ab");
    fDict = OpenDict("rb");
    fseek(fDict, 0, SEEK_END);
    long DictSize = ftell(fDict);
    fclose(fDict);

    /* Если размер не ноль, поместить словарь в RAM */
    if(DictSize)
    {
        fDict = OpenDict("rb");

        /* Выделение RAM под вспомогательные переменные */
        int i; char ch;

        /* Определение количества слов */
        for(WordNum = 0; fread(&ch, sizeof(char), 1, fDict);)
            if(!ch) ++WordNum;

        /* Выделение RAM под свободный массив и его маску */
        int* WordLen = (int*)   malloc(sizeof(int)   * WordNum);
        char** sDict = (char**) malloc(sizeof(char*) * WordNum);

        /* Заполнение маски свободного массива */
        fseek(fDict, 0, SEEK_SET);
        for(WordNum = 0, i = 0; fread(&ch, sizeof(char), 1, fDict);)
        {
            if(ch) ++i;
            else
            {
                WordLen[WordNum] = i + 1;
                ++WordNum;
                i = 0;
            }
        }

        /* Заполнение свободного массива */
        fseek(fDict, 0, SEEK_SET);
        for(i = 0; i < WordNum; ++i)
        {
            sDict[i] = (char*) malloc(sizeof(char) * WordLen[i]);
            fread(sDict[i], sizeof(char), WordLen[i], fDict);
        }
        free(WordLen);

        fclose(fDict);
        return(sDict);
    }   /* Если размер файла ноль, вернуть нулевой адрес */
    else
        return(NULL);
}

/*Функция освобождения выделенной памяти */
void DictFree(char** sDict)
{
    int i;
    for(i = 0; i < WordNum; ++i)
        free(sDict[i]);
    free(sDict);
}

/* Фукция вывода слов */
void DictPrint()
{
    char** sDict = DictMem();
    int i;
    if(sDict)
    {
        printf("*Все слова*");
        for(i = 0; i < WordNum; ++i)
            if(sDict[i][0] != 32)
            printf("\n%d) %s", i, sDict[i]);
        DictFree(sDict);
    } 
}
