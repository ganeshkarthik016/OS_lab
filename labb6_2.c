#include <stdio.h>
#include <stdbool.h>

#define P 4
#define R 3

int main()
{
    int allocation[P][R] = {
        {0,1,0},
        {2,0,0},
        {3,0,3},
        {2,1,1}
    };

    int need[P][R] = {
        {7,4,3},
        {1,2,2},
        {6,0,0},
        {0,1,1}
    };

    int available[R] = {1,1,0};

    int work[R];
    bool finish[P] = {false};

    for(int i=0;i<R;i++)
        work[i] = available[i];

    bool found = true;

    while(found)
    {
        found = false;

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

                    finish[i] = true;
                    found = true;
                }
            }
        }
    }

    bool deadlock = false;

    printf("Processes in deadlock:\n");

    for(int i=0;i<P;i++)
    {
        if(!finish[i])
        {
            printf("P%d ", i);
            deadlock = true;
        }
    }

    if(!deadlock)
        printf("No deadlock");

    printf("\n");

    return 0;
}