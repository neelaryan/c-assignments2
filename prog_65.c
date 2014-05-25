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
    return pos;
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
    int *arr,n,i,reads;
    char a;
    printf("Enter no. of elements : ");
    while(((reads = scanf("%d%c", &n, &a)) != 2 && reads != EOF) || a != '\n') {
        printf("Please enter an integer only !\nEnter no. of elements : ");
        do {
            reads = scanf("%c", &a);
        }while(reads != EOF && a != '\n');
    }
    arr = (int *)malloc(n*sizeof(int));
    printf("Enter %d elements :\n", n);
    for(i = 0; i < n; i++) {
        printf("Enter element #%d : ",i+1);
        while(((reads = scanf("%d%c", &arr[i], &a)) != 2 && reads != EOF) || a != '\n') {
            printf("Please enter an integer only !\nEnter element #%d : ",i+1);
            do {
                reads = scanf("%c", &a);
            }while(reads != EOF && a != '\n');
        }
    }
    quick(arr,0,n-1);
    printf("Sorted elements :\n");
    for(i = 0; i < n; i++)
        printf("%d\n", arr[i]);
    getch();
    return 0;
}
