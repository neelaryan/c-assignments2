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

typedef enum
{
    ascending=1,descending=2
} order;

void swap(long *x, long *y)
{
    *x = *x + *y;
    *y = *x - *y;
    *x = *x - *y;
}

int needSwap(int x, int y, order dir)
{
    if(dir == ascending)
        return x > y;
    if(dir == descending)
        return x < y;
    return 0;
}

void bubble_sort(long a[], int n, order dir)
{
    int i, j, swaped;
    for(i = 0; i < n-1; ++i)
    {
        swaped = 0;
        for(j = 1; j <= n-i-1; ++j)
            if(needSwap(a[j-1], a[j], dir))
            {
                swap(&a[j-1], &a[j]);
                swaped = 1;
            }
        if(swaped == 0)
            break;
    }
}

int main()
{
    clrscr();
    long arr[100];
    int n, i, sort_order;
    char *_order[] = {"ascending","descending"};
    printf("Enter number of elements : ");
    scanf("%d", &n);
    printf("Enter %d integers :\n", n);
    for(i = 0; i < n; i++)
        scanf("%ld", &arr[i]);
    printf("Sort : 1. Ascending\t2. Descending ? ");
    scanf("%d",&sort_order);
    bubble_sort(arr,n,sort_order);
    printf("Sorted list in %s order :\n",_order[sort_order-1]);
    for(i = 0 ; i < n ; i++)
        printf("%ld\n", arr[i]);
    getch();
    return 0;
}
