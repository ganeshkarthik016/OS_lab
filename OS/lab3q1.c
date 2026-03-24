#include <stdio.h>

int turn = 0;   

void process_0()
{
    printf("Process 0 in critical section\n");
    turn = 1;
}


void process_1()
{
    while (turn != 1);   
    printf("Process 1 in critical section\n");
    turn = 0;           
}

int main()
{
    // process_1();
    process_0();
    process_1();
    process_0();
    process_1();
    return 0;
}