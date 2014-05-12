#include <stdio.h>
#include <stdlib.h>
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

void get_value(int *arr,int SIZE)
{
    int i, j;
    for (i = 0; i < SIZE; i++) {
	j = i + 1;
	printf("\n Enter element %d: ", j);
	scanf("%d", &arr[i]);
    }
}

void print_value(int *arr, int n)
{
    int i;
    if(n == 0) {
	printf("NULL");
	return;
    }
    printf("{ ");
    for (i = 0; i < n; i++) {
	printf("%d ", arr[i]);
    }
    printf("}");
}

void function_sort(int *arr, int SIZE)
{
    int i, j, temp, swapping;

    for (i = 1; i < SIZE; i++) {
	swapping = 0;
	for (j = 0; j < SIZE-i; j++) {
	    if (arr[j] > arr[j+1]) {
		temp = arr[j];
		arr[j] = arr[j + 1];
		arr[j + 1] = temp;
		swapping = 1;
	    }
	}
	if (swapping == 0) {
	    break;
	}
    }
}

int find_intersection(int *array1, int *array2, int *intersection_array, int SIZE)
{
    int i = 0, j = 0, k = 0;
    while ((i < SIZE) && (j < SIZE)) {
        if (array1[i] < array2[j]) {
            i++;
        } else if (array1[i] > array2[j]) {
            j++;
        } else {
            intersection_array[k] = array1[i];
            i++;
            j++;
            k++;
        }
    }
    return(k);
}

int find_union(int *array1, int *array2, int *_union, int SIZE1, int SIZE2)
{
    int i, j, k = 0;
    for(i = 0; i < SIZE1; i++)
        _union[k++]=array1[i];
    for(i = 0; i < SIZE2; i++) {
        int flag=0;
        for(j = 0; j < SIZE1; j++) {
            if(array1[j] == array2[i])
                flag=1;
        }
        if(flag == 0)
            _union[k++] = array2[i];
    }
    return(k);
}

int find_difference(int *array1, int *array2, int *diff, int SIZE1, int SIZE2)
{
    int i, j, k=0;
    for(i = 0; i < SIZE1; i++) {
        int flag=0;
	for(j = 0; j < SIZE2; j++) {
            if(array2[j] == array1[i])
                flag=1;
        }
        if(flag == 0)
            diff[k++] = array1[i];
    }
    return(k);
}

int main()
{
    int *setA, *setB, *intersection, *_union, num_elements, *AminusB, *BminusA, SIZE1, SIZE2;
    clrscr();

    printf("Enter size the size for set A : ");
    scanf("%d",&SIZE1);
    setA=(int *)malloc(SIZE1*sizeof(int));
    printf("Enter the elements of set A :\n");
    get_value(setA,SIZE1);

    function_sort(setA,SIZE1);

    printf("\nEnter size the size for set B : ");
    scanf("%d",&SIZE2);
    setB=(int *)malloc(SIZE2*sizeof(int));
    printf("Enter the elements of set B :\n");
    get_value(setB,SIZE2);

    function_sort(setB,SIZE2);

    printf("\nSet A\t\t: ");
    print_value(setA,SIZE1);
    printf("\nSet B\t\t: ");
    print_value(setB,SIZE2);

    intersection=(int *)malloc(((SIZE1>=SIZE2)?SIZE2:SIZE1)*sizeof(int));
    num_elements = find_intersection(setA, setB, intersection,(SIZE1>=SIZE2)?SIZE2:SIZE1);
    printf("\nIntersection\t: ");
    print_value(intersection, num_elements);

    _union=(int *)malloc((SIZE1+SIZE2)*sizeof(int));
    num_elements = find_union(setA, setB, _union, SIZE1, SIZE2);
    printf("\nUnion\t\t: ");
    print_value(_union, num_elements);

    AminusB=(int *)malloc(SIZE1*sizeof(int));
    num_elements = find_difference(setA, setB, AminusB, SIZE1, SIZE2);
    printf("\nDifference (A-B): ");
    print_value(AminusB, num_elements);

    BminusA=(int *)malloc(SIZE2*sizeof(int));
    num_elements = find_difference(setB, setA, BminusA, SIZE2, SIZE1);
    printf("\nDifference (B-A): ");
    print_value(BminusA, num_elements);

    free(BminusA);
    free(AminusB);
    free(_union);
    free(intersection);
    free(setB);
    free(setA);
    getch();
    return 0;
}
