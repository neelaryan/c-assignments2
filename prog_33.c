#include <stdio.h>
#include <math.h>
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

float f(float x) {
    return (pow(x,3)-(4*x)+1);
}

float df(float x) {
    return ((3*pow(x,2))-4);
}

int main()
{
    int i,n=30;
    float x_new,x_old;
    clrscr();
    printf("Finding real roots of x^3 - 4x + 1 = 0 by Newton Raphson\n\n");
    printf("Enter x : ");
    scanf("%f",&x_new);
    printf("\nComputing roots...\n");
    for(i=0;i<n;i++)
    {
        x_old=x_new;
        if(df(x_new)<=0) {
            printf("\nDerivate of f(x) is approx. 0.\nMethod Failed.");
            getch();
            return 1;
        }
        x_new=x_old-(f(x_new)/df(x_new));
        printf("\nPass[%d] :\tx = %.4f",i+1,x_new);
        if(fabs((x_new-x_old)/x_old)<=0.0001)
        {
            printf("\n\nReal roots is %.4f",x_new);
            getch();
            return 0;
        }
    }
    printf("\nThe required solution does not converge or iterations are insufficient.");
    getch();
    return 1;
}
