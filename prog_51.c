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
#define MAXVERTICES 1000
#define INFINITY 99999

struct vertex
{
    int visited, predecessor;
    int dist;
};

int treeEdge[MAXVERTICES][2], mstCost;
int graphEdge[MAXVERTICES][MAXVERTICES], nodeCount;
struct vertex node[MAXVERTICES];

/* construct the input graph */
void buildGraph()
{
    int i = 1, source, dest, weight;
    printf("Enter the no of vertices : ");
    scanf("%d", &nodeCount);
    while (i <= (nodeCount * (nodeCount - 1) / 2))
    {
        printf("Edge (x<->y) / (x<->x to exit) : ");
        scanf("%d%d", &source, &dest);
        if (source == dest)
            break;
        if (source > nodeCount || dest > nodeCount ||
                source <= 0 || dest <= 0)
        {
            printf("Not a valid edge!!\n");
            continue;
        }
        else
        {
            printf("Weight for the edge %d to %d : ", source, dest);
            scanf("%d", &weight);

            /* update weight of the edge */
            graphEdge[source][dest] = weight;
            graphEdge[dest][source] = weight;
        }
        i++;
    }
    if (i < nodeCount - 1)
    {
        printf("Unable to build Minimum Spanning Tree.\n");
        exit(0);
    }
    return;
}

/* all vertices are visited or not */
int allVisited()
{
    int i;
    for (i = 1; i <= nodeCount; i++)
        if (node[i].visited == 0)
            return 0;
    return 1;
}

/* construct minimum spanning tree */
int buildTree()
{
    int i = 1, currentNode, count = 0, mindist;
    while (i <= nodeCount)
    {
        node[i].visited = 0;
        node[i].predecessor = 0;
        node[i].dist = INFINITY;
        i++;
    }

    node[1].visited = 1;
    node[1].dist = 0;

    currentNode = 1;
    while (allVisited() == 0)
    {
        for (i = 1; i <= nodeCount; i++)
        {

            /* Find the adjacent vertices and update the edge lenght */
            if(graphEdge[currentNode][i] > 0 && node[i].visited == 0)
            {
                if (graphEdge[currentNode][i] < node[i].dist)
                {
                    node[i].predecessor = currentNode;
                    node[i].dist = graphEdge[currentNode][i];
                }
            }
        }

        mindist = INFINITY;
        /* find the edge with minimum legth */
        for (i = 1; i <= nodeCount; i++)
        {
            if (node[i].dist < mindist && node[i].visited == 0)
            {
                mindist = node[i].dist;
                currentNode = i;
            }
        }
        /* Mark the vertex as visited - edge with min cost */
        node[currentNode].visited = 1;
        count++;
        treeEdge[count][0] = node[currentNode].predecessor;
        treeEdge[count][1] = currentNode;

        /* calculate cost of MST */
        mstCost = mstCost + graphEdge[treeEdge[count][0]][treeEdge[count][1]];
    }
    return count;
}

int main()
{
    clrscr();
    int i, count;
    /* construct graph */
    buildGraph();
    count = buildTree();
    printf("MST is composed of below edges :\n");
    for (i = 1; i <= count; i++)
    {
        printf("%d<->%d\n", treeEdge[i][0], treeEdge[i][1]);
    }
    printf("\n");
    printf("Cost of Minimum Spanning Tree : %d\n", mstCost);
    getch();
    return 0;
}
