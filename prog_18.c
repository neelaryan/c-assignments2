#include <stdio.h>
#include <math.h>
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

int smaller(int x, int y, int z)
{
    return (((x<y?x:y)<z)?(x<y?x:y):z);
}

void angle_check(int thin,int medium,int thick)
{
    char *triangle[3] = {"Acute-angled","Obtuse-angled","Right-angled"};
    if(pow(thin,2)+pow(medium,2) < pow(thick,2))
        printf("\nGiven numbers form sides of a %s triangle",triangle[1]);
    else if(pow(thin,2)+pow(medium,2) == pow(thick,2))
        printf("\nGiven numbers form sides of a %s triangle",triangle[2]);
    else
        printf("\nGiven numbers form sides of a %s triangle",triangle[0]);
}

int small(int x, int y, int z, int smallest)
{
    if(smallest==x) {
        if(smaller(y,z,z)==y)
            angle_check(x,y,z);
        else
            angle_check(x,z,y);
        return smaller(y,z,z);
    }
    else if(smallest==y) {
        if(smaller(y,z,z)==x)
            angle_check(y,x,z);
        else
            angle_check(y,z,x);
        return smaller(x,z,z);
    }
    else {
        if(smaller(y,z,z)==x)
            angle_check(z,x,y);
        else
            angle_check(z,y,x);
        return smaller(x,y,y);
    }
}

int main()
{
    int a,b,c,_shorter;
    clrscr();
    printf("Enter 3 positive number : ");
    scanf("%d %d %d", &a, &b, &c);
    if((a+b > c) && (a+c > b) && (b+c > a)) {
        _shorter = smaller(a,b,c);
        small(a,b,c,_shorter);
    }
    else
        printf("\nGiven numbers don't form sides of triangle.");
    getch();
    return 0;
}
