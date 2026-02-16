#include <stdio.h>
#include <unistd.h>

typedef struct {
    int value;
} semaphore;

void sem_init(semaphore *s, int initial) {
    s->value = initial;
}

void wait(semaphore *s) {
    while (s->value <= 0);
    s->value--;
} 

void signal(semaphore *s) {
    s->value++;
}

void client(int id, semaphore *printer_sem) {
    printf("Client %d: Waiting for printer...\n", id);
    wait(printer_sem);
    printf("Client %d: Printing...\n", id);
    sleep(2);
    printf("Client %d: Finished printing. Releasing printer.\n", id);
    signal(printer_sem);
}

int main() {
    semaphore printer_sem;
    sem_init(&printer_sem, 3);
    for (int i = 1; i <= 5; i++) {
        client(i, &printer_sem);
    }
    printf("All print jobs completed.\n");
    return 0;
}