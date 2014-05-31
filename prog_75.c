#include<stdio.h>
#include<stdlib.h>

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

#define que struct queue
#define pf printf
#define sf scanf

struct queue
{
    int info;
    struct queue *link;
};

que *front=NULL,*rear=NULL;
int count=0;

void push(int n)
{
    que *newnode;
    newnode=(struct queue*)malloc(sizeof(struct queue));
    newnode->info=n;
    newnode->link=NULL;
    if(count==0)
        front=newnode;
    else
        rear->link=newnode;
    rear=newnode;
    rear->link=front;
    count++;
}

int pop(void)
{
    int n;
    que *temp;
    if(count==0)
        return (-1);
    count--;
    if(front==rear)
    {
        n=front->info;
        free(front);
        front=NULL;
        rear=NULL;
    }
    else
    {
        temp= front ;
        n = temp-> info ;
        front = front -> link ;
        rear -> link = front ;
        free ( temp ) ;
    }
    return n;
}

void display(void)
{
    que *temp;
    int i;
    if(count==0)
        pf("Empty");
    else
    {
        temp=front;
        for(i=0; i<count; i++)
        {
            pf("%d ",temp->info);
            temp=temp->link;
        }
    }
    pf("\n");
}

int size(void)
{
    return count;
}

int main()
{
    clrscr();
    int n,ch=10,reads,i;
    char a;
    while(ch!=0)
    {
        pf("\n\tWhat do you want to do??\n");
        pf("1.Push\n");
        pf("2.Pop\n");
        pf("3.SizeOfQueue\n");
        pf("4.Display\n");
        pf("0.EXIT\n");
        sf("%d",&ch);
        switch(ch)
        {
        case 1:
        {
            pf("How many numbers do you want to push ? (Enter a number > 0) : ");
            sf("%d",&i);
            while(i>0) {
                pf("What no. do you want to push in queue ? ");
                while(((reads = sf("%d%c", &n, &a)) != 2 && reads != EOF) || a != '\n') {
                    printf("Please enter an integer only !\nWhat no. do you want to push in queue ? ");
                    do {
                        reads = sf("%c", &a);
                    }while(reads != EOF && a != '\n');
                }
                push(n);
                i--;
            }
            break;
        }
        case 2:
        {
            pf("How many numbers do you want to pop ? (Enter a number > 0) : ");
            sf("%d",&i);
            while(i>0) {
                n=pop();
                if(n==-1)
                    pf("Queue is empty\n");
                else
                    pf("Number poped from queue is %d\n",n);
                i--;
            }
            break;
        }
        case 3:
        {
            n=size();
            pf("Size of queue is %d\n",n);
            break;
        }
        case 4:
        {
            pf("Queue is -->> ");
            display();
        }
        case 0:
            break;
        default:
            pf("Wrong Choice\n");
            break;
        }
    }
    getch();
    return 0;
}
