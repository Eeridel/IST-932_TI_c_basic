#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <errno.h>
#include <malloc.h>
#include <time.h>

#define up      72
#define down    80
#define enter   13
#define esc     27

void ErrPrint(int ErrCode, const char* Message)
{
    errno = ErrCode;
    perror(Message);
    exit(errno);
}

FILE* OpenDict(const char* mode)
{
    FILE* fDict;
    char fName[] = "Dictionary.bin";
    if( !(fDict = fopen(fName, mode)) )
    ErrPrint(EIO, "Нет доступа к файлу ""Dictionary.bin""");
    return(fDict);
}

void PageUp()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD  position;
    position.X = 0;
    position.Y = 0;
    SetConsoleCursorPosition(hConsole, position);
}

void BrkPnt()
{
    printf("\nНажмите любую клавишу, чтобы продолжить...");
    getch();
    system("cls");
}

int WordNum; /* Глобальная переменная для освобождения RAM под словарь */
char** DictMem()
{
    /* Создание файла */
    FILE* fDict = OpenDict("ab");
    fclose(fDict);

    /* Определение размера файла */
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

void DictFree(char** sDict)
{
    int i;
    for(i = 0; i < WordNum; ++i)
        free(sDict[i]);
    free(sDict);
}

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
        printf("\n\n*Свободные ячейки*");
        for(i = 0; i < WordNum; ++i)
            if(sDict[i][0] == 32)
            printf("\n%d) Места в ячейке: %d букв", i, strlen(sDict[i]) );
        DictFree(sDict);
    } else printf("Словарь пуст. Вы можете добавить слова в меню словаря.");
    BrkPnt();
}

char* WordMem()
{
    int i = 0;
    char* str = (char*) malloc(sizeof(char));
    do
    {
        str[i] = getch();
        if( (str[i] > -64) && (str[i] < 0) )
        {
            if(str[i] > -33)
                str[i] -= 32;
            putc(str[i], stdout); ++i;
            str = (char*) realloc(str, sizeof(char) * (i + 1));
            str[i] = -64;
        }
        else if(str[i] == enter)
            str[i] = 0;
        else if( (str[i] == 8) && (i > 0) )
        {
            --i;
            printf("\b \b");
        }
    } while(str[i]);
    if(str[0]) return(str);
    else return(NULL);
}



void AddWord()
{
    printf("Введите слово, которое нужно добавить: ");
    char*  sWord = WordMem();
    char** sDict = DictMem();
    int i;
    system("cls");
    if(sWord)
    {
        if(sDict)
        {
            for(i = 0; i < WordNum; ++i)
            {
                if( (sDict[i][0] == 32) && (strlen(sDict[i]) == strlen(sWord)) )
                {
                    FILE* fDict = OpenDict("r+b");
                    char ch;
                    int j = 0;
                    while( fread(&ch, sizeof(char), 1, fDict) && (j != i) )
                        if(!ch) ++j;
                    fseek(fDict, -1, SEEK_CUR);
                    for(j = 0; j < strlen(sWord); ++j) putc(sWord[j], fDict);
                    fclose(fDict);
                    break;
                }
            }
            DictFree(sDict);
            ++i;
            if(i > WordNum)
            {
                FILE* fDict = OpenDict("ab");
                fwrite(sWord, sizeof(char), strlen(sWord) + 1, fDict);
                fclose(fDict);
            }
        }
        else
        {
            FILE* fDict = OpenDict("ab");
            fwrite(sWord, sizeof(char), strlen(sWord) + 1, fDict);
            fclose(fDict);
        }
        printf("Слово \"%s\" успешно добавлено!", sWord);
    }
    else printf("Слово не было добавлено!");
    free(sWord);
    BrkPnt();
}

void DeleteWord()
{
    printf("Введите слово, которое нужно удалить: ");
    int i;
    char*  sWord = WordMem();
    char** sDict = DictMem();
    system("cls");
    if(sDict)
    {
        if(sWord)
        {
            for(i = 0; i < WordNum; ++i)
                if( !strcmp(sWord, sDict[i]) )
                {
                    FILE* fDict = OpenDict("r+b");
                    char ch;
                    int j = 0;
                    while( fread(&ch, sizeof(char), 1, fDict) && (j != i) )
                        if(!ch) ++j;
                    fseek(fDict, -1, SEEK_CUR);
                    for(j = 0; j < strlen(sWord); ++j) putc(32, fDict);
                    fclose(fDict);
                    printf("Слово \"%s\" успешно удалено!", sWord);
                    break;
                }
            ++i;
            if(i > WordNum) printf("Слово \"%s\" не найдено в словаре!", sWord);
        }
        else printf("Слово не было введено.");
        DictFree(sDict);
    } else
        printf("Словарь пуст. Вы можете добавить слова в меню словаря.");
    free(sWord);
    BrkPnt();
}

void DictRndr(int crs)
{
    PageUp();
    printf("\n%15s", "*Словарь*"           );
    printf("\n%20s", "Показать все слова"); if(!crs)     printf("%3s", "<-"); else printf("%3s", "");
    printf("\n%20s", "Добавить слово"    ); if(crs == 1) printf("%3s", "<-"); else printf("%3s", "");
    printf("\n%20s", "Удалить слово"     ); if(crs == 2) printf("%3s", "<-"); else printf("%3s", "");
    printf("\n");
}

void DictCtrl()
{
    int input, crs = 0;
    DictRndr(crs);
    while(input != esc)
    {
        input = getch();
        if(input == enter)
        {
            system("cls");
            switch(crs)
            {
            case 0: DictPrint(); break;
            case 1: AddWord();   break;
            case 2: DeleteWord();
            }
        } else
        switch(input)
        {
        case    up: if(!crs)     crs = 2; else --crs; break;
        case  down: if(crs == 2) crs = 0; else ++crs;
        }
        DictRndr(crs);
    }
    system("cls");
}

void GameRndr(char* sWord, char* sWordMask, int attmpt, int bWin)
{
    PageUp();
    printf("Прогресс: %s", sWordMask);
    printf("\nОсталось попыток: %d\n", attmpt);
    if(bWin)
    {
        printf("\nПобеда!");
    }
    if(!attmpt)
    {
        printf("\nПоражение.");
        printf("\nВы не угадали слово \"%s\".", sWord);
    }
}

void GameCtrl()
{
    char** sDict = DictMem();
    if(sDict)
    {
        srand(time(NULL));
        int n, i, wlen;
        do
        {
            n = rand() % WordNum;
        } while(sDict[n][0] == 32);
        wlen = strlen(sDict[n]);
        char* sWord     = (char*) malloc(sizeof(char) * (wlen + 1) );
        char* sWordMask = (char*) malloc(sizeof(char) * (wlen + 1) );
        strcpy(sWord, sDict[n]);
        strcpy(sWordMask, sDict[n]);
        DictFree(sDict);
        char ch;
        for(i = 1; i < (wlen - 1); i++) if( (sWordMask[i] != sWord[0]) && (sWordMask[i] != sWord[wlen]) ) sWordMask[i] = '_';
        int bWin = 0, attmpt = 5, bGuess;
        GameRndr(sWord, sWordMask, attmpt, bWin);
        while(!bWin && attmpt)
        {
            for(;;)
            {
                ch = getch();
                if( (ch > -64) && (ch < 0) )
                {
                    if(ch > -33)
                    ch -= 32;
                    break;
                }
            }
            bGuess = 0;
            for(i = 0; sWord[i]; ++i)
                if(ch == sWord[i])
                {
                    sWordMask[i] = sWord[i];
                    bGuess = 1;
                }
            if(!bGuess) --attmpt;
            if(!strcmp(sWord, sWordMask)) bWin = 1;
            GameRndr(sWord, sWordMask, attmpt, bWin);
        }
        free(sWord);
        free(sWordMask);
    } else printf("Словарь пуст. Вы можете добавить слова в меню словаря.");
    BrkPnt();
}

void MenuRndr(int crs)
{
    PageUp();
    printf("\n%15s", "*Главное меню*");
    printf("\n%15s", "Начать игру"   ); if(!crs)     printf("%3s", "<-"); else printf("%3s", "");
    printf("\n%15s", "Словарь"       ); if(crs == 1) printf("%3s", "<-"); else printf("%3s", "");
    printf("\n%15s", "Выйти"         ); if(crs == 2) printf("%3s", "<-"); else printf("%3s", "");
    printf("\n");
}

int MenuCtrl()
{
    int input, crs = 0;
    MenuRndr(crs);
    for(;;)
    {
        input = getch();
        if(input == enter)
        {
            system("cls");
            switch(crs)
            {
            case 0: GameCtrl(); break;
            case 1: DictCtrl(); break;
            case 2: return(0);
            }
        } else
        switch(input)
        {
        case    up: if(!crs)     crs = 2; else --crs; break;
        case  down: if(crs == 2) crs = 0; else ++crs;
        }
        MenuRndr(crs);
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    return(MenuCtrl());
}
