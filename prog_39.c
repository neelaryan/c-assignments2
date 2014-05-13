#include <stdio.h>
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

void reduction(float a[][6],int size,int pivot ,int col)
{
    int i,j;
    float factor;

    factor=a[pivot][col];

    for(i=0; i<2*size; i++)
        a[pivot][i]/=factor;

    for(i=0; i<size; i++)
        if(i!=pivot) {
            factor=a[i][col];
            for(j=0; j<2*size; j++)
                a[i][j]=a[i][j]-a[pivot][j]*factor;
        }
}

int main()
{
    float a[3][6];
    int i,j;
    clrscr();
    for(i=0; i<3; i++)
        for(j=0; j<6; j++) {
            if(j==i+3)
                a[i][j]=1;
            else
                a[i][j]=0;
        }
    printf("\nEnter a 3 X 3 Matrix :\n\n");
    for(i=0; i<3; i++)
        for(j=0; j<3; j++) {
            printf("Enter element [%d][%d] = ",i,j);
            scanf("%f",&a[i][j]);
        }
    for(i=0; i<3; i++)
        reduction(a,3,i,i);
    printf("\nInvers Matrix :\n");
    for(i=0; i<3; i++) {
        printf("\n");
        for(j=0; j<3; j++)
            printf("%8.3f ",a[i][j+3]);
    }
    getch();
    return 0;
}
