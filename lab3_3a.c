int turn = 0;   
#include <stdio.h>
#include <windows.h>

void process(int id) {

    while (turn != id)
        ;

    printf("Process %d is in Critical Section\n", id);
    Sleep(1000);
    turn = (++turn)%2;

    printf("Process %d is in Remainder Section\n", id);
    Sleep(1000);
}

int main() {

    while (1) {
        process(0);
        process(1);
    }

    return 0;
}