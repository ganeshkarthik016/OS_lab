#include <stdio.h>
#include <unistd.h>

volatile int lock = 0;   
volatile int in_cs = 0;  

void P0_step() {

    if (lock == 0) {
        usleep(1);    
        lock = 1;

       
        in_cs++;
        printf("P0 in CS\n");
        if (in_cs > 1)
            printf("VIOLATION! Both in CS\n");

        usleep(1);

        
        in_cs--;
        lock = 0;
    }
}


void P1_step() {
  
    if (lock == 0) {
        usleep(1);   
        lock = 1;

        
        in_cs++;
        printf("P1 in CS\n");
        if (in_cs > 1)
            printf("VIOLATION! Both in CS\n");

        usleep(1);

      
        in_cs--;
        lock = 0;
    }
}

int main() {
    for (int i = 0; i < 10; i++) {
       
        P0_step();
        P1_step();
    }
    return 0;
}
