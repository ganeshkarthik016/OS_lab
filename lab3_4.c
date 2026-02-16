#include <stdio.h>
#include <windows.h>

int flag[2] = {0, 0};
int turn = 0;

void process(int i) {
    int j = 1 - i;

    flag[i] = 1;    
    turn = j;       

    while (flag[j] == 1 && turn == j)
        ;  

    printf("Process %d ENTERED Critical Section\n", i);
    Sleep(1000);

    flag[i] = 0;

    printf("Process %d EXITED Critical Section\n", i);
    Sleep(1000);
}

int main() {
    while (1) {
        process(0);
        process(1);
    }
    return 0;
}