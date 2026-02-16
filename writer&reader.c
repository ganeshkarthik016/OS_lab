#include <stdio.h>
#include <unistd.h>

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

int read_count = 0;
semaphore mutex, rw_mutex;

void reader(int id) {
    P(&mutex);
    read_count++;
    if (read_count == 1)
        P(&rw_mutex); // first reader locks resource
    V(&mutex);

    printf("Reader %d is reading\n", id);
    sleep(1);
    printf("Reader %d finished reading\n", id);

    P(&mutex);
    read_count--;
    if (read_count == 0)
        V(&rw_mutex); // last reader releases resource
    V(&mutex);
}

void writer(int id) {
    P(&rw_mutex);
    printf("Writer %d is writing\n", id);
    sleep(2);
    printf("Writer %d finished writing\n", id);
    V(&rw_mutex);
}

int main() {
    sem_init(&mutex, 1);
    sem_init(&rw_mutex, 1);

    // Simulate readers
    for (int i = 1; i <= 3; i++)
        reader(i);

    // Simulate writers
    for (int i = 1; i <= 2; i++)
        writer(i);

    printf("All reading and writing completed.\n");
    return 0;
}