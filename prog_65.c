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

void _swap(int* a, int* b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

int quickSort(int *a, int left, int right)
{
    int pos = left;
    do{
        while((a[pos]<=a[right]) && (pos != right))
            right = right-1;
        if(pos == right)
            return pos;
        else {
            _swap(&a[pos],&a[right]);
            pos = right;
        }
        while((a[pos]>=a[left]) && (pos != left))
            left = left+1;
        if(pos == left)
            return pos;
        else {
            _swap(&a[pos],&a[left]);
            pos = left;
        }
    }while(left <= right);
}

void quick(int *arr, int beg, int last)
{
    int pos;
    if(beg > last)
        return;
    pos = quickSort(arr,beg,last);
    quick(arr,beg,pos-1);
    quick(arr,pos+1,last);
}

int main()
{
    clrscr();
    int *arr,n,i;
start:
    printf("Enter no. of elements : ");
    scanf("%d",&n);
    if((n<=0)&&(n!=-1))
    {
        printf("Wrong Input ! No. of elements can't be 0. Enter -1 to exit.\n");
        goto start;
    }
    else if(n==-1)
    {
        printf("Press any key to exit...");
        getch();
        return 0;
    }
    arr = (int *)malloc(n*sizeof(int));
    printf("Enter %d elements :\n", n);
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    quick(arr,0,n-1);
    printf("Sorted elements :\n");
    for(i = 0; i < n; i++)
        printf("%d\n", arr[i]);
    getch();
    return 0;
}
