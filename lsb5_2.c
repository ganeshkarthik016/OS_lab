#include <stdio.h>
#include <unistd.h>

typedef struct {
    int value;
} semaphore;

void sem_init(semaphore *s, int initial) {
    s->value = initial;
}

void wait_n(semaphore *s, int n) {
    while (s->value < n);
    s->value -= n;
}

void signal_n(semaphore *s, int n) {
    s->value += n;
}

void vehicle(int id, int type, semaphore *parking) {
    int spots;

    if (type == 1) spots = 1;
    else if (type == 2) spots = 2;
    else spots = 3;

    printf("Vehicle %d requesting %d spot(s)\n", id, spots);
    wait_n(parking, spots);

    printf("Vehicle %d parked using %d spot(s)\n", id, spots);
    sleep(2);

    printf("Vehicle %d leaving and releasing %d spot(s)\n", id, spots);
    signal_n(parking, spots);
}

int main() {
    semaphore parking;
    sem_init(&parking, 10);

    for (int i = 1; i <= 20; i++) {
        int type = (i % 3) + 1;
        vehicle(i, type, &parking);
    }

    printf("All vehicles processed.\n");
    return 0;
}