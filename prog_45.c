#include<stdio.h>
#include<string.h>
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

void computeLPSArray(char *pat, int M, int *lps)
{
    int len = 0;    /* lenght of the previous longest prefix suffix */
    int i;
    lps[0] = 0;     /* lps[0] is always 0 */
    i = 1;
    /* the loop calculates lps[i] for i = 1 to M-1 */
    while(i < M)
    {
        if(pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else /* (pat[i] != pat[len]) */
        {
            if( len != 0 )
            {
                /* This is tricky. Consider the example AAACAAAA and i = 7. */
                len = lps[len-1];
                /* Also, note that we do not increment i here */
            }
            else /* if (len == 0) */
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
    /* create lps[] that will hold the longest prefix suffix values for pattern */
    int *lps = (int *)malloc(sizeof(int)*M);
    int j  = 0;  /* index for pat[] */
    int i = 0;  /* index for txt[] */
    /* Preprocess the pattern (calculate lps[] array) */
    computeLPSArray(pat, M, lps);
    while(i < N)
    {
        if(pat[j] == txt[i])
        {
            j++;
            i++;
        }
        if (j == M)
        {
            printf("Pattern found at location %d \n", (i-j)+1);
            j = lps[j-1];
        }
        /* mismatch after j matches */
        else if(pat[j] != txt[i])
        {
            /* Do not match lps[0..lps[j-1]] characters,
                they will match anyway */
            if(j != 0)
                j = lps[j-1];
            else
                i = i+1;
        }
    }
    free(lps);
}

int main()
{
    char txt[1024],pat[256];
    clrscr();
    printf("Enter text : ");
    fgets(txt,1024,stdin);
    if((strlen(txt)>0) && (txt[strlen(txt)-1] == '\n'))
        txt[strlen(txt)-1]='\0';
    printf("Enter search pattern : ");
    fgets(pat,256,stdin);
    if((strlen(pat)>0) && (pat[strlen(pat)-1] == '\n'))
        pat[strlen(pat)-1]='\0';
    KMPSearch(pat, txt);
    getch();
    return 0;
}
