#include <stdio.h>

int flag[2] = {0, 0};
int turn = 0;

void process0()
{
    flag[0] = 1;
    turn = 1;

    while (flag[1] && turn == 1);  // busy waiting

    printf("Process 0 in critical section\n");

    flag[0] = 0;
}

void process1()
{
    flag[1] = 1;
    turn = 0;

    while (flag[0] && turn == 0);  // busy waiting

    printf("Process 1 in critical section\n");

    flag[1] = 0;
}

int main()
{
    process0();
    process1();

    return 0;
}