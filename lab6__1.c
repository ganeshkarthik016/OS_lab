
#include <stdio.h>
#include <stdbool.h>

#define P 5  
#define R 3  

int main()
{
    int allocation[P][R] = {
        {0,1,0},
        {2,0,0},
        {3,0,2},
        {2,1,1},
        {0,0,2}
    };

    int max[P][R] = {
        {7,5,3},
        {3,2,2},
        {9,0,2},
        {2,2,2},
        {4,3,3}
    };

    int available[R] = {3,3,2};

    int need[P][R];
    int safeSeq[P];

    bool finish[P] = {false};

    int work[R];
    int count = 0;

    for(int i=0;i<P;i++)
    {
        for(int j=0;j<R;j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    for(int i=0;i<R;i++)
        work[i] = available[i];

    while(count < P)
    {
        bool found = false;

        for(int i=0;i<P;i++)
        {
            if(!finish[i])
            {
                int j;

                for(j=0;j<R;j++)
                {
                    if(need[i][j] > work[j])
                        break;
                }

                if(j == R)
                {
                    for(int k=0;k<R;k++)
                        work[k] += allocation[i][k];

                    safeSeq[count++] = i;
                    finish[i] = true;

                    found = true;
                }
            }
        }

        if(!found)
        {
            printf("System is NOT in safe state\n");
            return 0;
        }
    }

    printf("System is in SAFE state\nSafe Sequence: ");

    for(int i=0;i<P;i++)
        printf("P%d ", safeSeq[i]);

    printf("\n");

    return 0;
}