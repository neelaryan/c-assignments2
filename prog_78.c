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

struct node
{
    int data;
    struct node *next;
}*top;

void popStack()
{
    struct node *var=top;
    if(var==top)
    {
        top = top->next;
        printf("\nElement popped : %d", var->data);
        free(var);
    }
    else
        printf("\nStack Empty");
}

void push(int value)
{
    struct node *temp;
    temp=(struct node *)malloc(sizeof(struct node));
    temp->data=value;
    if (top == NULL)
    {
        top=temp;
        top->next=NULL;
    }
    else
    {
        temp->next=top;
        top=temp;
    }
}

void display()
{
    struct node *var=top;
    if(var!=NULL)
    {
        printf("\nElements are as:\n");
        while(var!=NULL)
        {
            printf("\t%d\n",var->data);
            var=var->next;
        }
        printf("\n");
    }
    else
        printf("\nStack is Empty");
}

int main()
{
    clrscr();
    int i=0,value,reads;
    char a;
    struct node *temp;
    top=NULL;
    while(i!=4)
    {
        printf("\n1. Push to stack");
        printf("\n2. Pop from Stack");
        printf("\n3. Display data of Stack");
        printf("\n4. Exit\n");
        printf("\nChoose Option: ");
        scanf("%d",&i);
        switch(i)
        {
        case 1:
        {
            printf("How many numbers do you want to push ? (Enter a number > 0) : ");
            scanf("%d",&i);
            while(i>0) {
                printf("What no. do you want to push in stack ? ");
                while(((reads = scanf("%d%c", &value, &a)) != 2 && reads != EOF) || a != '\n') {
                    printf("Please enter an integer only !\nWhat no. do you want to push in stack ? ");
                    do {
                        reads = scanf("%c", &a);
                    }while(reads != EOF && a != '\n');
                }
                push(value);
                i--;
            }
            break;
        }
        case 2:
        {
            printf("How many numbers do you want to pop ? (Enter a number > 0) : ");
            scanf("%d",&i);
            while(i>0) {
                popStack();
                i--;
            }
            break;
        }
        case 3:
        {
            display();
            break;
        }
        case 4:
        {
            while(top!=NULL)
            {
                temp = top->next;
                free(top);
                top=temp;
            }
            exit(0);
        }
        default:
            printf("\nWrong Choice");
        }
    }
    getch();
    return 0;
}
