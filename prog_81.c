#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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
    struct tree *left, *right;
    int data;
} tree;

tree* getnode(int x)
{
    tree *p;
    p=(tree *)malloc(sizeof(tree));
    p->left=p->right=NULL;
    p->data=x;
    return p;
}

tree* createbst()
{
    tree *root=NULL, *p, *ptr;
    char a;
    int reads,x;
    printf("\nEnter root element (0 to stop) : ");
    while(((reads = scanf("%d%c", &x, &a)) != 2 && reads != EOF) || a != '\n') {
        printf("Please enter an integer only !\nEnter root element (0 to stop) : ");
        do {
            reads = scanf("%c", &a);
        }while(reads != EOF && a != '\n');
    }
    root = getnode(x);
    printf("\nEnter another element (0 to stop) : ");
    while(((reads = scanf("%d%c", &x, &a)) != 2 && reads != EOF) || a != '\n') {
        printf("Please enter an integer only !\nEnter another element (0 to stop) : ");
        do {
            reads = scanf("%c", &a);
        }while(reads != EOF && a != '\n');
    }
    do
    {
        ptr = root;
        p = root;
        while(p != NULL)
        {
            ptr = p;
            if(x < p->data)
                p = p->left;
            else
                p = p->right;
        }
        if(x < ptr->data)
            ptr->left = getnode(x);
        else
            ptr->right = getnode(x);
        printf("\nEnter an element (0 to stop) : ");
        while(((reads = scanf("%d%c", &x, &a)) != 2 && reads != EOF) || a != '\n') {
            printf("Please enter an integer only !\nEnter an element (0 to stop) : ");
            do {
                reads = scanf("%c", &a);
            }while(reads != EOF && a != '\n');
        }
    }
    while(x != 0);
    return root;
}

void inorder(tree *root)
{
    static int flag = 0;
    if(root != NULL)
    {
        flag++;
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    }
    else if(flag == 0)
        printf("NULL");
}

void insertnode(tree *root, tree *ptr)
{
    if(root->data > ptr->data)
    {
        if(root->left==NULL)
            root->left=ptr;
        else
            insertnode(root->left,ptr);
    }
    else
    {
        if(root->right==NULL)
            root->right=ptr;
        else
            insertnode(root->right,ptr);
    }
}

tree* deltree(tree *root,int x)
{
    tree *ptr1, *ptr2, *ptr3, *ptr4;
    ptr1=ptr2=root;

    // search the item x
    while(ptr2!=NULL && ptr2->data!=x)
    {
        ptr1=ptr2;
        if(x < ptr2->data)
            ptr2=ptr2->left;
        else
            ptr2=ptr2->right;
    }
    if(ptr2 == NULL)
    {
        printf("Not Found !");
        return root;
    }

    // if ptr2 has no child
    if(ptr2->left==NULL && ptr2->right==NULL && ptr1->left==ptr2)
        ptr1->left=NULL;
    else if(ptr2->left==NULL && ptr2->right==NULL && ptr1->right==ptr2)
        ptr1->right=NULL;
    // if ptr2 has one child
    else if(ptr2->left==NULL)
    {
        // when left subtree is NULL
        if(ptr1==ptr2)
        {
            root=ptr2->right;
            free(ptr2);
            return root;
        }
        else if(ptr1->right==ptr2)
            ptr1->right=ptr2->right;
        else
            ptr1->left=ptr2->right;
    }
    else if(ptr2->right==NULL)
    {
        // when right subtree is NULL
        if(ptr1==ptr2)
        {
            root=ptr2->left;
            free(ptr2);
            return root;
        }
        else if(ptr1->right==ptr2)
            ptr1->right=ptr2->left;
        else
            ptr1->left=ptr2->left;
    }
    // if ptr2 has two child
    else
    {
        //find the inorder successor of ptr2
        ptr3=ptr4=ptr2->right;
        while(ptr4->left!=NULL)
        {
            ptr3=ptr4;
            ptr4=ptr4->left;
        }
        //just right node is inorder successor
        if(ptr3==ptr4)
            ptr4->left=ptr2->left;
        //connecting successor to the left & right of ptr2
        else
        {
            ptr3->left=ptr4->right;
            ptr4->left=ptr2->left;
            ptr4->right=ptr2->right;
        }
        //connecting ptr1 to ptr4
        if(ptr1->right==ptr2)
            ptr1->right=ptr4;
        else if(ptr1->left==ptr2)
            ptr1->left=ptr4;
    }
    if(ptr1==ptr2)
        root=ptr4;
    free(ptr2);
    return root;
}

int main()
{
    clrscr();
    int x,i,reads;
    char a;
    tree *myTree;
    printf("Building BST...");
    myTree = createbst();
    while(i!=3) {
        printf("\n\nInorder Traversal :\n");
        inorder(myTree);
        printf("\n\n==== Menu ====\n\n1. Insert node\n2. Delete node\n3. Exit\nChoose an options : ");
        scanf("%d",&i);
        switch(i) {
            case 1:
                printf("How many nodes do you want to insert ? (Enter a number > 0) : ");
                scanf("%d",&i);
                while(i>0) {
                    printf("Enter node data to insert : ");
                    while(((reads = scanf("%d%c", &x, &a)) != 2 && reads != EOF) || a != '\n') {
                        printf("Please enter an integer only !\nWhich node do you want to insert ? ");
                        do {
                            reads = scanf("%c", &a);
                        }while(reads != EOF && a != '\n');
                    }
                    insertnode(myTree,getnode(x));
                    i--;
                }
                break;
            case 2:
                printf("How many nodes do you want to delete ? (Enter a number > 0) : ");
                scanf("%d",&i);
                while(i>0) {
                    printf("Which node do you want to delete ? ");
                    while(((reads = scanf("%d%c", &x, &a)) != 2 && reads != EOF) || a != '\n') {
                        printf("Please enter an integer only !\nWhich node do you want to delete ? ");
                        do {
                            reads = scanf("%c", &a);
                        }while(reads != EOF && a != '\n');
                    }
                    myTree=deltree(myTree,x);
                    i--;
                }
                break;
            case 3:
                free(myTree);
                printf("\nPress any key to continue...");
                getch();
                exit(0);
                break;
            default:
                printf("\nWrong Choice");
        }
    }
    getch();
    return 0;
}
