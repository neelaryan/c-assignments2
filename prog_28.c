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

int main()
{
    int m, n, p, q, i, j, k, sum = 0;
    int matA[10][10], matB[10][10], matC[10][10];
    clrscr();
    printf("Enter the number of rows and columns of Matrix A : \n");
    scanf("%d%d", &m, &n);
    printf("Enter the elements of Matrix A : \n");
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &matA[i][j]);
    printf("Enter the number of rows and columns of Matrix B : \n");
    scanf("%d%d", &p, &q);
    if (n != p)
        printf("Matrices with entered orders can't be multiplied with each other.\n");
    else {
        printf("Enter the elements of Matrix B : \n");
        for (i = 0; i < p; i++)
            for (j = 0; j < q; j++)
                scanf("%d", &matB[i][j]);
        for (i = 0; i < m; i++) {
            for (j = 0; j < q; j++) {
                for (k = 0; k < p; k++) {
                    sum = sum + matA[i][k]*matB[k][j];
                }
                matC[i][j] = sum;
                sum = 0;
            }
        }
        printf("\nProduct : \n\n");
        for (i = 0; i < m; i++) {
            for (j = 0; j < q; j++)
                printf("%d\t", matC[i][j]);
            printf("\n");
        }
    }
    getch();
    return 0;
}
