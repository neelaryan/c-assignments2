#include<stdio.h>
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

int main()
{
    int i=1,j=2,k=3,l;
    clrscr();
    for(i=1; i<=332; i++)
        for(j=i+1; j<=499; j++) {
            if(i+j+j+1>1000)
                j=499;
            for(k=j+1; k<=997; k++) {
                l=i+j+k;
                if(l>1000)
                    k=997;
                if(l<=1000 && k<l) {
                    printf("\nI=%d, J=%d, K=%d, L=%d",i,j,k,l);
                }
            }
        }
    getch();
    return 0;
}
