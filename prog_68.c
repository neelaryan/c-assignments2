#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
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

typedef struct tree
{
    char data;
    struct tree *left;
    struct tree *right;
} tree_t;

tree_t *getnode(char x)
{
    tree_t *p;
    p = (tree_t *)malloc(sizeof(tree_t));
    p->left = NULL;
    p->right = NULL;
    p->data = x;
    return p;
}

tree_t *createBST()
{
    tree_t *root=NULL, *p, *ptr;
    char a;
    int flag=-1;
    do
    {
        flag++;
        if(flag)
            printf("\nPlease enter a character only !\nEnter root element (0 to stop) : ");
        else
            printf("\nEnter root element (0 to stop) : ");
        a = getche();
        if(a == '0')
            return root;
    }while(!isalpha(a));
    root = getnode(a);
    flag=-1;
    do
    {
        flag++;
        if(flag)
            printf("\nPlease enter a character only !\nEnter another element (0 to stop) : ");
        else
            printf("\nEnter another element (0 to stop) : ");
        a = getche();
        if(a == '0')
            return root;
    }
    while(!isalpha(a));
    do
    {
        ptr = root;
        p = root;
        while(p != NULL)
        {
            ptr = p;
            if(a < p->data)
                p = p->left;
            else
                p = p->right;
        }
        if(a < ptr->data)
            ptr->left = getnode(a);
        else
            ptr->right = getnode(a);
        flag=-1;
        do
        {
            flag++;
            if(flag)
                printf("\nPlease enter an character only !\nEnter an element (0 to stop) : ");
            else
                printf("\nEnter an element (0 to stop) : ");
            a = getche();
            if(a == '0')
                return root;
        }
        while(!isalpha(a));
    }
    while(a != '0');
    return root;
}

void preorder(tree_t *root)
{
    static int flag = 0;
    if(root != NULL)
    {
        flag++;
        printf("%c ",root->data);
        preorder(root->left);
        preorder(root->right);
    }
    else if(flag == 0)
        printf("NULL");
}

void inorder(tree_t *root)
{
    static int flag = 0;
    if(root != NULL)
    {
        flag++;
        inorder(root->left);
        printf("%c ",root->data);
        inorder(root->right);
    }
    else if(flag == 0)
        printf("NULL");
}

void postorder(tree_t * root)
{
    static int flag = 0;
    if(root != NULL)
    {
        flag++;
        postorder(root->left);
        postorder(root->right);
        printf("%c ",root->data);
    }
    else if(flag == 0)
        printf("NULL");
}

int main()
{
    clrscr();
    tree_t *myTree;
    printf("Building BST...\n\n");
    myTree = createBST();
    printf("\n\nPreorder Traversal :\n");
    preorder(myTree);
    printf("\n\nInorder Traversal :\n");
    inorder(myTree);
    printf("\n\nPostorder Traversal :\n");
    postorder(myTree);
    getch();
    return 0;
}
