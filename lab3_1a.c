int lock = 0;
#include <stdio.h>
#include <windows.h>

void process(int id) {

    while (lock == 1)
        ;

    lock = 1; 

    printf("Process %d is in Critical Section\n", id);
    Sleep(1000);

    lock = 0;   

    printf("Process %d is in Remainder Section\n", id);
    Sleep(1000);
}

int main() {

    while (1) {
        process(1);
        process(2);
    }

    return 0;
}