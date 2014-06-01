#include<stdio.h>
#include<stdlib.h>
/* If we are compiling on Windows compile these functions and/or add these headers */
#if defined(_WIN16)

#include <conio.h>
/* Clear the screen using this function when conio.h is not present */
void clrscr()
{
    printf("\x1B[2J\x1B[0;0f");
}

/* Otherwise define getch() and getche() */
#elif defined(__linux__)

#include <termios.h>
static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    new = old; /* make new settings same as old settings */
    new.c_lflag &= ~ICANON; /* disable buffered i/o */
    new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
    tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* Read 1 character without echo */
char getch(void)
{
    return getch_(0);
}

/* Read 1 character with echo */
char getche(void)
{
    return getch_(1);
}

/* Clear the screen */
void clrscr()
{
    printf("\x1B[2J\x1B[0;0f");
}

#endif

int main(int argc, char *argv[])
{
    FILE *fptr1, *fptr2, *fptr3;
    char str[256], ch1, ch2;
    if(argc!=4)
    {
        printf("Usage : %s FILE1 FILE2 FILE3\nMerge lines from FILE1 and FILE2 alternatively to FILE3, ",argv[0]);
        printf("then display FILE1 FILE2 FILE3.\n");
        getch();
        exit(1);
    }
    fptr1=fopen(argv[1], "r");
    if(fptr1==NULL)
    {
        printf("\n%s doesn't exist.\n",argv[1]);
        getch();
        exit(1);
    }
    fptr2=fopen(argv[2], "r");
    if(fptr2==NULL)
    {
        printf("\n%s doesn't exist.\n",argv[2]);
        getch();
        exit(1);
    }
    fptr3=fopen(argv[3], "w+");
    if(fptr3==NULL)
    {
        printf("\n%s doesn't exist.\n",argv[3]);
        getch();
        exit(1);
    }
    printf("\nMergeing alternative lines from %s and %s to %s ...",argv[1],argv[2],argv[3]);
    while(((ch1=fgetc(fptr1)) != EOF) || ((ch2 = fgetc(fptr2)) != EOF))
    {
        if (ch1 != EOF)
        {
            ungetc(ch1, fptr1);
            fgets(str, 255, fptr1);
            fputs(str, fptr3);
        }
        if (ch2 != EOF)
        {
            ungetc(ch2, fptr2);
            fgets(str, 255, fptr2);
            fputs(str, fptr3);
        }
    }
    if (ch1 != EOF)
    {
        ungetc(ch1, fptr1);
        fgets(str, 255, fptr1);
        fputs(str, fptr3);
    }
    if (ch2 != EOF)
    {
        ungetc(ch2, fptr2);
        fgets(str, 255, fptr2);
        fputs(str, fptr3);
    }
    printf("\nMerging Complete !\nDisplaying all files...");
    rewind(fptr1);
    rewind(fptr2);
    rewind(fptr3);
    printf("\n\n%s :\n\n",argv[1]);
    while((ch1 = fgetc(fptr1)) != EOF)
      printf("%c",ch1);
    fclose(fptr1);
    printf("\n\n%s :\n\n",argv[2]);
    while((ch1 = fgetc(fptr2)) != EOF)
      printf("%c",ch1);
    fclose(fptr2);
    printf("\n\n%s :\n\n",argv[3]);
    while((ch1 = fgetc(fptr3)) != EOF)
      printf("%c",ch1);
    fclose(fptr3);
    getch();
    return 0;
}
