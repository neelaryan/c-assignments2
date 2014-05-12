#include<stdio.h>
#include<float.h>
#include<math.h>

/* If we are compiling on Windows compile these functions and/or add these headers */
#if defined(_WIN16)

#include <conio.h>
/* Clear the screen using this function when conio.h is not present */
void clrscr() {
    system("cls");
}

/* Otherwise define getch() and getche() */
#elif defined(__linux__)

#include <termios.h>
static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(int echo) {
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    new = old; /* make new settings same as old settings */
    new.c_lflag &= ~ICANON; /* disable buffered i/o */
    new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
    tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) {
    tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) {
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

/* Read 1 character without echo */
char getch(void) {
    return getch_(0);
}

/* Read 1 character with echo */
char getche(void) {
    return getch_(1);
}

/* Clear the screen */
void clrscr() {
    system("clear");
}

#endif

int main()
{
    char c, c_prev ;
    short s, s_prev ;
    int i, i_prev ;
    long l, l_prev ;
    float f, f_prev;
    double d, d_prev;

    for( c = 1, c_prev = -1; c > c_prev ; c = c << 1)
	c_prev = c ;

    for( s = 1, s_prev = -1 ; s > s_prev ; s = s << 1)
	s_prev = s ;

    for( i = 1, i_prev = -1 ; i > i_prev ; i = i << 1)
	i_prev = i ;

    for( l = 1, l_prev = -1 ; l > l_prev ; l = l << 1)
	l_prev = l ;

	clrscr();
	printf("\tData Type Ranges\n");
    printf("\nCharacter\t\t: %d\t\t to\t%d",c,abs(c+1));
    printf("\nUnsigned Character\t: %d\t\t to\t%d",c-c,abs(c*2+1));
    printf("\nShort\t\t\t: %d\t to\t%d",s,abs(s+1));
    printf("\nUnsigned Short\t\t: %u\t\t to\t%u",s-s,(abs(s+1)*2)+1);
    printf("\nInteger\t\t\t: %d\t to\t%d",i,abs(i+1));
    printf("\nLong\t\t\t: %ld\t to\t%ld",l,abs(l+1));
    printf("\nFloat\t\t\t: %f\n\t\t\t\tto\n\t\t\t  %f",FLT_MAX,FLT_MAX);
    printf("\nDouble\t\t\t: %lf\n\t\t\t\tto\n\t\t\t  %lf",DBL_MIN,DBL_MAX);
    getch();
    return 0;
}
