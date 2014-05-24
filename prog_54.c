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

typedef struct node
{
    struct node *next;
    int vertex;
} node;

node *g[20];
int n,visited[20];
int indegree(int i);
int outdegree(int i);
void dfs(int i);

void _insert(int vi,int vj)
{
    node *p,*q;
    q=(node*)malloc(sizeof(node));
    q->vertex=vj;
    q->next=NULL;

    if(g[vi]==NULL)
        g[vi]=q;
    else
    {
        p=g[vi];
        while(p->next!=NULL)
            p=p->next;
        p->next=q;
    }
}

void readgraph()
{
    int vi,vj,i,no_of_edges;
    printf("\nEnter the no. of Vertices : ");
    scanf("%d",&n);
    for(i=0; i<n; i++)
        g[i]=NULL;
    printf("\nEnter the no of Edges : ");
    scanf("%d",&no_of_edges);
    for(i=0; i<no_of_edges; i++)
    {
        printf("\nEnter the Edge(u,v) : ");
        scanf("%d%d",&vi,&vj);
        _insert(vi,vj);
    }
}


int main()
{
    clrscr();
    int i,j,k;
    readgraph();
    for(i=0; i<n; i++)
        visited[i]=0;

    printf("\n===========================================");
    printf("\nNode\tIndegree\tOutdegree");
    printf("\n===========================================");
    for(i=0; i<n; i++)
    {
        j=indegree(i);
        k=outdegree(i);
        printf("\n%2d\t%4d\t\t%5d",i,j,k);
    }
    printf("\n-------------------------------------------");
    dfs(0);
    getch();
    return 0;
}

int outdegree(int i)
{
    int j=0;
    node *p;
    p=g[i];
    while(p!=NULL)
    {
        p=p->next;
        j++;
    }
    return(j);
}

int indegree(int v)
{
    int i,j=0;
    node *p;
    for(i=0; i<n; i++)
    {
        p=g[i];
        while(p!=NULL)
        {
            if(p->vertex==v)
                j++;
            p=p->next;
        }
    }
    return(j);
}

void dfs(int i)
{
    node *p;
    p=g[i];
    visited[i]=1;
    printf("\nVisit->%d",i);
    while(p!=NULL)
    {
        i=p->vertex;
        if(!visited[i])
            dfs(i);
        p=p->next;
    }
}
