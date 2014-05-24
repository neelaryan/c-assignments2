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

int _partition(int *arr, int beg, int last)
{
    int x=arr[last], i=(beg-1), j;
    for(j = beg; j <= last-1; j++)
    {
        if (arr[j] <= x)
        {
            i++;
            _swap(&arr[i], &arr[j]);
        }
    }
    _swap(&arr[i+1], &arr[last]);
    return (i+1);
}

void quickSort(int *arr, int beg, int last)
{
    // Create an auxiliary stack
    int _stack[last-beg+1],top=-1,p;
    // push initial values of l and h to stack
    _stack[++top] = beg;
    _stack[++top] = last;
    while(top >= 0)
    {
        last = _stack[top--];
        beg = _stack[top--];
        p = _partition(arr, beg, last);
        // If there are elements on left side of pivot, then push leftside to stack
        if(p-1 > beg)
        {
            _stack[++top] = beg;
            _stack[++top] = p-1;
        }
        // If there are elements on right side of pivot, then push rightside to stack
        if(p+1 < last)
        {
            _stack[++top] = p+1;
            _stack[++top] = last;
        }
    }
}

int main()
{
    clrscr();
    int *arr,n,i;
    start:
    printf("Enter no. of elements : ");
    scanf("%d",&n);
    if((n<=0)&&(n!=-1)) {
        printf("Wrong Input ! No. of elements can't be 0. Enter -1 to exit.\n");
        goto start;
    }
    else if(n==-1) {
        printf("Press any key to exit...");
        getch();
        return 0;
    }
    arr = malloc(n*sizeof(int));
    printf("Enter %d elements :\n", n);
    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    quickSort(arr,0,n-1);
    printf("Sorted elements :\n");
    for(i = 0; i < n; i++)
        printf("%d\n", arr[i]);
    getch();
    return 0;
}
