#include <stdio.h>

int main()
{
    int R = 10;               
    int n = 4;             

    int maxNeed[4] = {7,4,5,3};
    int alloc[4] = {2,3,1,1};

    int totalAlloc = 0;

    for(int i=0;i<n;i++)
        totalAlloc += alloc[i];

    int available = R - totalAlloc;

    int sum = 0;

    for(int i=0;i<n;i++)
        sum += (maxNeed[i] - 1);

    if(R >= sum + 1)
        printf("System satisfies sufficient condition for NO DEADLOCK\n");
    else
        printf("Deadlock may occur\n");

    printf("Available printers: %d\n", available);

    return 0;
}