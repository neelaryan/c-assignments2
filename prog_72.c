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

struct node
{
    float coef;
    int expo;
    struct node *link;
};

struct node *insert_s(struct node *start,float co,int ex)
{
    struct node *ptr,*tmp;
    tmp=(struct node *)malloc(sizeof(struct node));
    tmp->coef=co;
    tmp->expo=ex;
    /*list empty or exp greater than first one */
    if(start==NULL || ex > start->expo)
    {
        tmp->link=start;
        start=tmp;
    }
    else
    {
        ptr=start;
        while(ptr->link!=NULL && ptr->link->expo >= ex)
            ptr=ptr->link;
        tmp->link=ptr->link;
        ptr->link=tmp;
    }
    return start;
}

struct node *create(struct node *start)
{
    int i,n,ex;
    float co;
    printf("Enter the number of terms : ");
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        printf("Enter coeficient for term %d : ",i);
        scanf("%f",&co);
        printf("Enter exponent for term %d : ",i);
        scanf("%d",&ex);
        start=insert_s(start,co,ex);
    }
    return start;
}

struct node *insert(struct node *start,float co,int ex)
{
    struct node *ptr,*tmp;
    tmp=(struct node *)malloc(sizeof(struct node));
    tmp->coef=co;
    tmp->expo=ex;
    /*If list is empty*/
    if(start==NULL)
    {
        tmp->link=start;
        start=tmp;
    }
    else    /*Insert at the end of the list*/
    {
        ptr=start;
        while(ptr->link!=NULL)
            ptr=ptr->link;
        tmp->link=ptr->link;
        ptr->link=tmp;
    }
    return start;
}

void display(struct node *ptr)
{
    if(ptr==NULL)
    {
        printf("Zero polynomial\n");
        return;
    }
    while(ptr!=NULL)
    {
        printf("(%.1fx^%d)", ptr->coef,ptr->expo);
        ptr=ptr->link;
        if(ptr!=NULL)
            printf(" + ");
        else
            printf("\n");
    }
}

void poly_add(struct node *p1,struct node *p2)
{
    struct node *start3;
    start3=NULL;

    while(p1!=NULL && p2!=NULL)
    {
        if(p1->expo > p2->expo)
        {
            start3=insert(start3,p1->coef,p1->expo);
            p1=p1->link;
        }
        else if(p2->expo > p1->expo)
        {
            start3=insert(start3,p2->coef,p2->expo);
            p2=p2->link;
        }
        else if(p1->expo==p2->expo)
        {
            start3=insert(start3,p1->coef+p2->coef,p1->expo);
            p1=p1->link;
            p2=p2->link;
        }
    }
    /*if poly2 has finished and elements left in poly1*/
    while(p1!=NULL)
    {
        start3=insert(start3,p1->coef,p1->expo);
        p1=p1->link;
    }
    /*if poly1 has finished and elements left in poly2*/
    while(p2!=NULL)
    {
        start3=insert(start3,p2->coef,p2->expo);
        p2=p2->link;
    }
    printf("\nAdded polynomial is : ");
    display(start3);
}

void poly_mult(struct node *p1, struct node *p2)
{
    struct node *start3;
    struct node *p2_beg = p2;
    start3=NULL;
    if(p1==NULL || p2==NULL)
    {
        printf("\nMultiplied polynomial is zero polynomial\n");
        return;
    }
    while(p1!=NULL)
    {
        p2=p2_beg;
        while(p2!=NULL)
        {
            start3=insert_s(start3,p1->coef*p2->coef,p1->expo+p2->expo);
            p2=p2->link;
        }
        p1=p1->link;
    }
    printf("\nMultiplied polynomial is : ");
    display(start3);
}

int main()
{
    clrscr();
    struct node *start1=NULL,*start2=NULL;
    int ch;

    printf("Enter polynomial 1 :\n");
    start1=create(start1);

    printf("\nEnter polynomial 2 :\n");
    start2=create(start2);

    printf("\nPolynomial 1 is :  ");
    display(start1);
    printf("\nPolynomial 2 is :  ");
    display(start2);

    do{
    printf("\n\n\tMenu :\n1.Add the two polynomials\n2.Multiply the two polynomials\n3.Exit\nChoice : ");
    scanf("%d",&ch);

    if(ch==1)
        poly_add(start1, start2);
    else if(ch==2)
        poly_mult(start1, start2);
    else if(ch==3) {
        printf("Press any key to exit...");
        getch();
        exit(0);
    }
    else
        printf("Input Error.");
    }while((ch!=1) && (ch!=2));
    getch();
    return 0;
}
