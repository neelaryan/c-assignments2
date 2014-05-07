/*
    to satisfy i+j+k=l and i<j<k<l where i,j,k,l belong to range [1,1000]
    we shall traverse through all possible combinations and display the valid ones
    upon algebraic investigation, the max values of i,j,k satisfying the stated constraints are 332,499,997, respectively.
*/

#include<stdio.h>

int main() {
  int i=1,j=2,k=3,l;
  for(i=1;i<=332;i++)
    for(j=i+1;j<=499;j++) {
        if(i+j+j+1>1000)
            j=499;
        for(k=j+1;k<=997;k++) {
            l=i+j+k;
            if(l>1000)
                k=997;
            if(l<=1000 && k<l) {
                printf("\nI=%d, J=%d, K=%d, L=%d",i,j,k,l);
            }
        }
    }
  return 0;
}
