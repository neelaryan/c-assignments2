#include <stdio.h>
#include <stdlib.h>
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

int LCM(int x,int y)
{
    int hcf=1,lcm=x*y,max,i;

    max=(x>y)?x:y;
    for(i=2; i<max/2;)
    {
        if(x%i==0 && y%i==0)
        {
            hcf=hcf*i;
            x=x/i;
            y=y/i;
        }
        else i++;
    }
    lcm=lcm/hcf;
    return(lcm);
}

int HCF(int x,int y)
{
    int hcf=1,max,i;
    max=(x>y)?x:y;
    for(i=2; i<max/2;)
    {
        if(x%i==0 && y%i==0)
        {
            hcf=hcf*i;
            x=x/i;
            y=y/i;
        }
        else i++;
    }
    return(hcf);
}

int main()
{
    int a[20],n,i,x,y;
    clrscr();
    printf("How many elements do you want to enter(<=20) ? ");
    scanf("%d",&n);
    printf("Enter the elements: ");

    for(i=0; i<n; i++)
        scanf("%d",&a[i]);

    x=HCF(a[0],a[1]);
    for(i=2; i<n; i++)
        x=HCF(x,a[i]);

    y=LCM(a[0],a[1]);
    for(i=2; i<n; i++)
        y=LCM(y,a[i]);

    printf("The HCF is : %d\nThe LCM is : %d",x,y);
    getch();
    return 0;
}
