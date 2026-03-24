
#include <stdio.h>
#include <stdbool.h>

bool flag[2] = {false, false};
int turn = 0;

void process1() {
    int i = 0, j = 1;

    while (1) {
        flag[i] = true;   
        turn = j;      

        while (flag[j] == true && turn == j);  

        printf("Process 1 in critical section\n");
       

        flag[i] = false;
        break; // exit CS
    }
}

void process2() {
    int i = 1, j = 0;

    while (1) {
        flag[i] = true;   
        turn = j;       

        while (flag[j] == true && turn == j)
            ;   

        printf("Process 2 in critical section\n");
       

        flag[i] = false;
        break; // exit CS
    }
}

int main() {
    process2();
    process1();
    process2();
    process2();
    return 0;
}