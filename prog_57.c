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
#define INFINITY 2000
#define MAXNODES 20
#define MEMBER 1
#define NONMEMBER 0

void shortpath(int NODES, int weight[][NODES], int s, int t, int *pd, int precede[NODES])
{
    int distance[NODES],perm[NODES];
    int current,i,k,dc;
    int smalldist,newdist;
    for(i=0; i<NODES; i++)
    {
        perm[i]=NONMEMBER;
        distance[i]=INFINITY;
    }
    perm[s] = MEMBER;
    distance[s] = 0;
    current = s;
    while(current != t)
    {
        smalldist=INFINITY;
        dc=distance[current];
        for(i=0; i<NODES; i++)
            if(perm[i]==NONMEMBER)
            {
                newdist = dc + weight[current][i];
                if(newdist < distance[i])
                {
                    distance[i]=newdist;
                    precede[i]=current;
                }
                if(distance[i] < smalldist)
                {
                    smalldist = distance[i];
                    k=i;
                }
            }
        current = k;
        perm[current]=MEMBER;
    }
    *pd=distance[t];
}

int main()
{
    clrscr();
    int i,j,s,t,NODES,flag=-1;
    do{
        flag++;
        if(flag)
            printf("No. of nodes should lie b/w 0 & 20.\nEnter no. of nodes : ");
        else
            printf("Enter no. of nodes : ");
        scanf("%d",&NODES);
    }while((NODES<=0)||(NODES>MAXNODES));
    int weight[NODES][NODES],precede[NODES],pd;
    printf("Enter weight matrix :\n\n");
    for(i=0; i<NODES; i++)
        for(j=0; j<NODES; j++)
        {
            printf("weight [%d][%d] : ",i,j);
            scanf("%d",&weight[i][j]);
        }
    flag=-1;
    do{
        flag++;
        if(flag)
            printf("Enter VALID starting and ending node : ");
        else
            printf("Enter starting node and the ending node : ");
        scanf("%d%d",&s,&t);
    }while(((s<0)||(s>=NODES))||((t<0)||(t>=NODES)));   /* starting & ending nodes lie b/w 0 to NODES-1 */
    shortpath(NODES,weight,s,t,&pd,precede);
    printf("\nThe shortest path from node %d to %d is : %d",s,t,pd);
    getch();
    return(0);
}
