#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,j;
    printf("Enter number : ");
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=i;j++)
            printf("%d ",j);
        printf("\n");
    }
    return 0;
}
