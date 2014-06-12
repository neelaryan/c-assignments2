#include<stdio.h>
#include<string.h>

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

void swap_char(int a[], int pos1, int pos2)
{
    int x;
    x=a[pos1];
    a[pos1]=a[pos2];
	a[pos2]=x;
}

void permute(int a[],int beg,int _end)
{
	int i;
	if(beg==_end)
	{
		printf("\n%d",a[beg]);
		return;
	}
	for(i=beg;i<=_end;i++)
	{
	 	swap_char(a,beg,i);
	 	permute(a,beg+1,_end);
	  	swap_char(a,beg,i);
	}
}

int main()
{
	int a[3],n;
	clrscr();
	printf("Enter the 3 ints : ");
	n=scanf("%d%d%d", &a[0], &a[1], &a[2]);
	permute(a,0,n);
	getch();
	return 0;
}
