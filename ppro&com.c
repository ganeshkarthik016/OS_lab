#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 5

typedef struct {
    int value;
} semaphore;

void sem_init(semaphore *s, int initial) {
    s->value = initial;
}

void P(semaphore *s) {
    while (s->value <= 0);
    s->value--;
}

void V(semaphore *s) {
    s->value++;
}

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void produce(int item) {
    printf("Producing item %d\n", item);
}

void consume(int item) {
    printf("Consuming item %d\n", item);
}

void producer(semaphore *empty, semaphore *full, semaphore *mutex) {
    for (int i = 1; i <= 10; i++) {
        produce(i);
        P(empty);
        P(mutex);
        buffer[in] = i;
        in = (in + 1) % BUFFER_SIZE;
        V(mutex);
        V(full);
    }
}

void consumer(semaphore *empty, semaphore *full, semaphore *mutex) {
    for (int i = 1; i <= 10; i++) {
        P(full);
        P(mutex);
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        V(mutex);
        V(empty);
        consume(item);
    }
}

int main() {
    semaphore empty, full, mutex;
    sem_init(&empty, BUFFER_SIZE);
    sem_init(&full, 0);
    sem_init(&mutex, 1);

    producer(&empty, &full, &mutex);
    consumer(&empty, &full, &mutex);

    printf("Producer-consumer execution completed.\n");
    return 0;
}