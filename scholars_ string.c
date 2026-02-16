 #include <stdio.h>

int book[5] = {1,1,1,1,1};
int library = 4;

void wait(int *S)
{
    while(*S <= 0);
    (*S)--;
}

void signal(int *S)
{
    (*S)++;
}

void scholar(int i)
{
    printf("Scholar %d is RESTING\n", i+1);

    wait(&library);

    wait(&book[i]);
    wait(&book[(i+1)%5]);

    printf("Scholar %d is STUDYING\n", i+1);

    signal(&book[i]);
    signal(&book[(i+1)%5]);

    signal(&library);
}

int main()
{
    int i;

    for(i=0;i<5;i++)
        scholar(i);

    return 0;
}