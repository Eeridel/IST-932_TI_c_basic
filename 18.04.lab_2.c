#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
    typedef struct sObject
    {
        int hp;
        int mp;
        char name[10];
        struct sObject *next;
    } tObject;
    tObject *get_struct(void)
        {
            tObject *p = (tObject *) malloc(sizeof(tObject));
            printf("Player Name: ");
            gets(p -> name);
            printf ("\n\n");
            srand(time(NULL) );
            p -> hp = rand() % 100;
            p -> mp = rand() % 100;

            if(!p)
            {
                printf("Allocation error!\n");
                exit(0);
            };
            return p;
        };

    tObject *pi = NULL;
    tObject *p_begin = NULL;
    tObject *p = NULL;
    tObject *prev_p = NULL;
    char choice;

    do
    {
        printf("    Player creator \n");
        printf(" 1) Create first player\n");
        printf(" 2) Create additional player\n");
        printf(" 3) Delete last player\n");
        printf(" 4) Show player list\n");
        printf(" 5) Delete player list\n");
        printf(" 6) Search player characteristic\n");
        printf(" 7) Quit\n");
        printf("   Enter your choice: ");
        choice = getch();
        printf ("\n\n");

        switch(choice)
        {
            case '1':
                {
                    if(p_begin == NULL)
                    {
                        p_begin = get_struct();
                        p_begin -> next = NULL;
                        p = p_begin;
                        prev_p = p_begin;
                    }
                    else printf("Delete list first!\n\n");
                }break;
            case '2':
                {
                    if(p_begin)
                    {
                        p -> next = get_struct();
                        prev_p = p;
                        p = p -> next;
                        p -> next = NULL;
                    }
                    else printf("There is no any Player. Create a first one!\n\n");
                }break;
            case '3':
                {
                    if(prev_p)
                        if(prev_p -> next)
                        {
                            free(p);
                            prev_p -> next = NULL;
                            for(p = p_begin; (p -> next != prev_p) & (p -> next != NULL); p = p -> next);
                            prev_p = p;
                            if(prev_p -> next)
                                p = prev_p -> next;
                        }
                        else printf("Cannot delete first Player!\n\n");
                    else printf("There is no any Player. Create a first one!\n\n");
                }break;
            case '4':
                {
                    int i;
                    if(p_begin)
                    for(i = 1, pi = p_begin; pi; pi = pi -> next, i++)
                        {
                            printf("%d)\n", i);
                            printf("    Name: %s\n\n", pi -> name);
                            printf("    Health Points: %d\n", pi -> hp);
                            printf("    Mana Points: %d\n", pi -> mp);
                            printf("\n");
                        }
                    else printf("There is no any Player. Create a first one!\n\n");
                }break;
            case '5':
                {
                    if(p_begin)
                    {
                        int i = -1;
                        for(pi = p_begin; pi; pi = pi -> next)
                            i++;
                        for(;i > 0; i--)
                        {
                            if(prev_p)
                                if(prev_p -> next)
                                {
                                    free(p);
                                    prev_p -> next = NULL;
                                    for(p = p_begin; (p -> next != prev_p) & (p -> next != NULL); p = p -> next);
                                    prev_p = p;
                                    if(prev_p -> next)
                                    p = prev_p -> next;
                                }
                                else printf("Cannot delete first Player!\n\n");
                            else printf("There is no any Player. Create a first one!\n\n");
                        }
                        free(p);
                        p_begin = NULL;
                        prev_p = NULL;
                        p = NULL;
                        printf("Current list is deleted!\n\n");
                    }
                    else printf("There is no any Player. Create a first one!\n\n");
                }break;
            case '6':
                {
                    if(p_begin)
                        {
                            printf("    What kind of characteristic do you want to search?:\n");
                            printf(" 1) Health Points\n");
                            printf(" 2) Mana Points\n");
                            printf("   Enter your choice: ");
                            choice = getch();
                            printf ("\n\n");
                            printf("   Enter value: ");
                            switch(choice)
                            {
                                case '1':
                                    {
                                        int i, h, n;
                                        n = scanf("%d", &h);
                                        if(n != 1) return 0;
                                        n = 0;
                                        printf ("\n\n");
                                        printf("Found:\n");
                                        for(i = 1, pi = p_begin; pi; pi = pi -> next, i++)
                                            {
                                                if(pi -> hp == h)
                                                    {
                                                        printf("%d)\n", i);
                                                        printf("    Name: %s\n\n", pi -> name);
                                                        printf("    Health Points: %d\n", pi -> hp);
                                                        printf("\n");
                                                        n = 1;
                                                    }
                                            }
                                        if(!n) printf("     Nothing!\n");
                                    }break;
                                case '2':
                                    {
                                        int i, h, n;
                                        n = scanf("%d", &h);
                                        if(n != 1) return 0;
                                        n = 0;
                                        printf ("\n\n");
                                        printf("Found:\n");
                                        for(i = 1, pi = p_begin; pi; pi = pi -> next, i++)
                                            {
                                                if(pi -> mp == h)
                                                    {
                                                        printf("%d)\n", i);
                                                        printf("    Name: %s\n\n", pi -> name);
                                                        printf("    Mana Points: %d\n", pi -> mp);
                                                        printf("\n");
                                                        n = 1;
                                                    }
                                            }
                                        if(!n) printf("     Nothing!\n");
                                    }break;
                            }
                        }
                    else printf("There is no any Player. Create a first one!\n\n");
                    printf("\n\n");
                }break;
            case '7': break;
            default: printf("Wrong command!\n\n");
        }
    } while(choice != '7');
    return 0;
}
