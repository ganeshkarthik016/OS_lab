#include <stdio.h>

int printer = 1;
int scanner = 1;

void wait(int *S)
{
    while(*S <= 0);
    (*S)--;
}

void signal(int *S)
{
    (*S)++;
}

void student(int i)
{
    printf("Student %d preparing experiment\n", i+1);

    wait(&printer);
    wait(&scanner);

    printf("Student %d USING printer and scanner\n", i+1);

    signal(&scanner);
    signal(&printer);

    printf("Student %d completed experiment\n", i+1);
}

int main()
{
    int i;

    for(i=0;i<5;i++)
        student(i);

    return 0;
}