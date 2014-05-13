#include <stdio.h>
#include <stdlib.h>
/* If we are compiling on Windows compile these functions and/or add these headers */
#if defined(_WIN16)

#include <conio.h>
/* Clear the screen using this function when conio.h is not present */
void clrscr() {
    printf("\x1B[2J\x1B[0;0f");
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
    printf("\x1B[2J\x1B[0;0f");
}

#endif

int small(int x,int y)
{
    return (x<y?x:y);
}

int LCM(int x,int y)
{
    int lcm = 1,i;
    for(i = 2; i <= small(x,y)/2; i++)
    {
        if((x%i == 0) && (y%i == 0))
        {
            lcm = lcm*i;
            x = x/i;
            y = y/i;
        }
        else
            i++;
    }
    return lcm;
}

int HCF(int x,int y)
{
    int i;
    for(i = small(x,y); i >= 1; --i)
    {
        if((x%i == 0) && (y%i == 0))
        {
            return i;
        }
    }
}

int main()
{
    int *num,in,c=1,i=-1,lcm,hcf;
    clrscr();
    printf("Enter positive numbers (0 to stop) : ");
    while(c) {
        scanf("%d",&in);
        if(in==0)
            c=0;
        else
            num[++i]=in;
    }
    if(i==-1) {
        printf("\nNo number entered !");
        printf("\nPress any key to exit...");
        getch();
        return 0;
    }
    if(i+1 < 2) {
        lcm=LCM(num[0],1);
        hcf=HCF(num[0],num[0]);
    }
    else if(i+1 == 2) {
        lcm=LCM(num[0],num[1]);
        hcf=HCF(num[0],num[1]);
    }
    else {
        lcm=LCM(num[0],num[1]);
        hcf=HCF(num[0],num[1]);
        for(c = 2; c <= i; c++) {
            lcm=LCM(lcm,num[c]);
            hcf=HCF(hcf,num[c]);
        }
    }
    printf("\nLCM : %d",lcm);
    printf("\nHCF : %d",hcf);
    getch();
    return 0;
}
