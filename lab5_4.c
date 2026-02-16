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

void controller(int id, semaphore *sensor_sem) {
    printf("Controller %d waiting to read sensor\n", id);
    P(sensor_sem);
    printf("Controller %d reading sensor data\n", id);
    sleep(1);
    printf("Controller %d adjusting heater\n", id);
    V(sensor_sem);
}

void alarm(int id, semaphore *sensor_sem) {
    printf("Alarm %d waiting to read sensor\n", id);
    P(sensor_sem);
    printf("Alarm %d checking temperature\n", id);
    sleep(1);
    printf("Alarm %d done checking\n", id);
    V(sensor_sem);
}

int main() {
    semaphore sensor_sem;
    sem_init(&sensor_sem, 1);

    for (int i = 1; i <= 3; i++) {
        controller(i, &sensor_sem);
    }

    for (int i = 1; i <= 2; i++) {
        alarm(i, &sensor_sem);
    }

    printf("All sensor accesses completed.\n");
    return 0;
}