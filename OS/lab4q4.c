#include <stdio.h>
#include <windows.h>

#define CONTROLLERS 3
#define ALARMS 2


typedef struct {
    int value;               // 0 or 1
    CRITICAL_SECTION lock;
} BinarySemaphore;


void init_sem(BinarySemaphore *s, int val) {
    s->value = val;
    InitializeCriticalSection(&s->lock);
}


void P(BinarySemaphore *s) {
    while (1) {
        EnterCriticalSection(&s->lock);

        if (s->value == 1) {
            s->value = 0;   // acquire sensor
            LeaveCriticalSection(&s->lock);
            break;
        }

        LeaveCriticalSection(&s->lock);
        Sleep(10); // wait and retry
    }
}

// V() operation (signal)
void V(BinarySemaphore *s) {
    EnterCriticalSection(&s->lock);
    s->value = 1;   // release sensor
    LeaveCriticalSection(&s->lock);
}

// Global semaphore for temperature sensor
BinarySemaphore sensor_sem;

// Simulated temperature read
int readTemperature() {
    return (rand() % 100); // random temperature
}

// Heater controller thread
DWORD WINAPI HeaterController(LPVOID lpParam) {
    int id = *(int*)lpParam;

    while (1) {
        printf("Controller %d: Waiting to read sensor...\n", id);
        P(&sensor_sem);

        int temp = readTemperature();
        printf("Controller %d: Read temperature = %d°C, adjusting heater...\n", id, temp);
        Sleep(1000); // simulate heater adjustment

        V(&sensor_sem);

        Sleep(5000); // reads every 5 seconds
    }
    return 0;
}

// Alarm system thread
DWORD WINAPI AlarmSystem(LPVOID lpParam) {
    int id = *(int*)lpParam;

    while (1) {
        printf("Alarm %d: Waiting to read sensor...\n", id);
        P(&sensor_sem);

        int temp = readTemperature();
        printf("Alarm %d: Checked temperature = %d°C\n", id, temp);

        if (temp > 80) {
            printf("Alarm %d: !!! CRITICAL TEMPERATURE !!!\n", id);
        }

        V(&sensor_sem);

        Sleep(4000); // periodic check
    }
    return 0;
}

int main() {
    HANDLE cthreads[CONTROLLERS], athreads[ALARMS];
    int cids[CONTROLLERS], aids[ALARMS];

    srand(GetTickCount());

    // Initialize binary semaphore to 1 (sensor is free)
    init_sem(&sensor_sem, 1);

    // Create heater controller threads
    for (int i = 0; i < CONTROLLERS; i++) {
        cids[i] = i + 1;
        cthreads[i] = CreateThread(NULL, 0, HeaterController, &cids[i], 0, NULL);
    }

    // Create alarm threads
    for (int i = 0; i < ALARMS; i++) {
        aids[i] = i + 1;
        athreads[i] = CreateThread(NULL, 0, AlarmSystem, &aids[i], 0, NULL);
    }

    WaitForMultipleObjects(CONTROLLERS, cthreads, TRUE, INFINITE);
    WaitForMultipleObjects(ALARMS, athreads, TRUE, INFINITE);

    return 0;
}
