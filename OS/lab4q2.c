#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define TOTAL_SPOTS 10
#define VEHICLES 20

// Parking lot structure
typedef struct {
    int spots[TOTAL_SPOTS];   // 0 = free, 1 = occupied
    CRITICAL_SECTION lock;
} ParkingSemaphore;

ParkingSemaphore parking;

// Initialize parking lot
void init_parking(ParkingSemaphore *p) {
    InitializeCriticalSection(&p->lock);
    for (int i = 0; i < TOTAL_SPOTS; i++)
        p->spots[i] = 0;
}

// Find n consecutive free spots
int find_consecutive(ParkingSemaphore *p, int n) {
    int count = 0;
    for (int i = 0; i < TOTAL_SPOTS; i++) {
        if (p->spots[i] == 0)
            count++;
        else
            count = 0;

        if (count == n)
            return i - n + 1; // starting index
    }
    return -1;
}

// wait(n): request n consecutive spots
int wait_n(ParkingSemaphore *p, int n) {
    int start = -1;

    while (1) {
        EnterCriticalSection(&p->lock);

        start = find_consecutive(p, n);
        if (start != -1) {
            for (int i = start; i < start + n; i++)
                p->spots[i] = 1;   // occupy spots
            LeaveCriticalSection(&p->lock);
            return start;
        }

        LeaveCriticalSection(&p->lock);
        Sleep(50); // wait and retry
    }
}

// signal(n): release n spots from start
void signal_n(ParkingSemaphore *p, int start, int n) {
    EnterCriticalSection(&p->lock);
    for (int i = start; i < start + n; i++)
        p->spots[i] = 0;
    LeaveCriticalSection(&p->lock);
}

// Vehicle thread
DWORD WINAPI VehicleProcess(LPVOID lpParam) {
    int id = *(int*)lpParam;
    int type = rand() % 3; // 0=car, 1=van, 2=bus
    int needed;

    if (type == 0) needed = 1;
    else if (type == 1) needed = 2;
    else needed = 3;

    char *name = (type == 0) ? "Car" : (type == 1) ? "Van" : "Bus";

    printf("%s %d: Needs %d spot(s). Waiting...\n", name, id, needed);

    int start = wait_n(&parking, needed);

    printf("%s %d: Parked at spots [%d to %d]\n",
           name, id, start, start + needed - 1);

    Sleep(3000); // parked for 3 seconds

    printf("%s %d: Leaving spots [%d to %d]\n",
           name, id, start, start + needed - 1);

    signal_n(&parking, start, needed);

    return 0;
}

int main() {
    HANDLE threads[VEHICLES];
    int ids[VEHICLES];

    srand(GetTickCount());
    init_parking(&parking);

    for (int i = 0; i < VEHICLES; i++) {
        ids[i] = i + 1;
        threads[i] = CreateThread(NULL, 0, VehicleProcess, &ids[i], 0, NULL);
    }

    WaitForMultipleObjects(VEHICLES, threads, TRUE, INFINITE);
    return 0;
}
