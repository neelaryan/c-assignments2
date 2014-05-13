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

int det3(int a[3][3])
{
	return (a[0][0]*a[1][1]*a[2][2])-(a[0][0]*a[1][2]*a[2][1])
            +(a[0][1]*a[1][2]*a[2][0])-(a[0][1]*a[1][0]*a[2][2])
            +(a[0][2]*a[1][0]*a[2][1])-(a[0][2]*a[1][1]*a[2][0]);
}

int main(void)
{
	int A[3][3],B[3],detx[3][3],dety[3][3],detz[3][3];
	clrscr();
	printf("\tCramer's Rule Calculator\nEnter coeffiecients only of x1, x2, x3, b of each equation.");
	printf("\n\nEnter eqn. 1 : ");
	scanf("%d %d %d %d", &A[0][0], &A[0][1], &A[0][2], &B[0]);
	printf("\nEnter eqn. 2 : ");
	scanf("%d %d %d %d", &A[1][0], &A[1][1], &A[1][2], &B[1]);
	printf("\nEnter eqn. 3 : ");
	scanf("%d %d %d %d", &A[2][0], &A[2][1], &A[2][2], &B[2]);
	detx[3][3] = ((B[0]*A[0][1]*A[0][2])*(B[1]*A[1][1]*A[1][2])*(B[2]*A[2][1]*A[2][2]));
	dety[3][3] = ((A[0][0]*B[0]*A[0][2])*(A[1][0]*B[1]*A[1][2])*(A[2][0]*B[2]*A[2][2]));
	detz[3][3] = ((A[0][0]*A[0][1]*B[0])*(A[1][0]*A[1][1]*B[1])*(A[2][0]*A[2][1]*B[2]));
    if(det3(A)!=0)
		 printf("\nSystem has a unique solution ( %d, %d, %d)",
		 det3(detx)/det3(A), det3(dety)/det3(A), det3(detz)/det3(A));
	else
		 printf("\nSystem does not have a unique solution because determinant is 0");
    getch();
	return 0;
}
