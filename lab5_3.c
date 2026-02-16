#include <stdio.h>
#include <unistd.h>

typedef struct {
    int value;
} semaphore;

void sem_init(semaphore *s, int initial) {
    s->value = initial;
}

void P(semaphore *s) {
    while (s->value == 0);
    s->value = 0;
}

void V(semaphore *s) {
    s->value = 1;
}

void writer(int id, semaphore *log_sem) {
    printf("Writer %d waiting to access log file\n", id);
    P(log_sem);
    printf("Writer %d writing to log file\n", id);
    sleep(2);
    printf("Writer %d finished writing\n", id);
    V(log_sem);
}

void reader(int id, semaphore *log_sem) {
    printf("Reader %d waiting to access log file\n", id);
    P(log_sem);
    printf("Reader %d reading log file\n", id);
    sleep(2);
    printf("Reader %d finished reading\n", id);
    V(log_sem);
}

int main() {
    semaphore log_sem;
    sem_init(&log_sem, 1);

    for (int i = 1; i <= 4; i++) {
        writer(i, &log_sem);
    }

    for (int i = 1; i <= 6; i++) {
        reader(i, &log_sem);
    }

    printf("All log accesses completed.\n");
    return 0;
}