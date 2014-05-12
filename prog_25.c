#include <stdio.h>
/* If we are compiling on Windows compile these functions and/or add these headers */
#if defined(_WIN16)

#include <conio.h>
/* Clear the screen using this function when conio.h is not present */
void clrscr()
{
    system("cls");
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
    system("clear");
}

#endif
int main()
{
    int order, output =  0, i, j, mat[3][3];
    clrscr();
    printf("Enter the order of the matrix(2/3): ");
    scanf("%d", &order);
    if (order < 2 || order > 3) {
        printf("\nWrong input!!");
        getch();
        return 0;
    }

    printf("Enter your matrix input:\n");
    for (i = 0; i < order; i++)
        for (j = 0; j < order; j++) {
            printf("Element #[%d][%d] : ", i,j);
            scanf("%d",&mat[i][j]);
        }

    if (order == 2) {
        output = (mat[0][0] * mat[1][1]) -
                 (mat[0][1] * mat[1][0]);
    }
    else if (order == 3) {
        output = (mat[0][0] * mat[1][1] * mat[2][2]) -
                 (mat[0][0] * mat[2][1] * mat[1][2]) -
                 (mat[0][1] * mat[1][0] * mat[2][2]) +
                 (mat[0][1] * mat[2][0] * mat[1][2]) +
                 (mat[0][2] * mat[1][0] * mat[2][1]) -
                 (mat[0][2] * mat[1][1] * mat[2][0]);
    }

    printf("Determinant for the given matrix: %d\n", output);
    getch();
    return 0;
}
