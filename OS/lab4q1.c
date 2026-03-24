#include <stdio.h>
#include <windows.h>


typedef struct {
    int value;
    CRITICAL_SECTION lock;
} CustomSemaphore;

// Initialize semaphore
void init_custom(CustomSemaphore *s, int val) {
    s->value = val;
    InitializeCriticalSection(&s->lock);
}

// wait() operation
void wait_custom(CustomSemaphore *s) {
    while (1) {
        EnterCriticalSection(&s->lock);

        if (s->value > 0) {
            s->value--;   // acquire printer
            LeaveCriticalSection(&s->lock);
            break;
        }

        LeaveCriticalSection(&s->lock);
        Sleep(10); // small delay to avoid 100% CPU (busy wait)
    }
}

// signal() operation
void signal_custom(CustomSemaphore *s) {
    EnterCriticalSection(&s->lock);
    s->value++;   // release printer
    LeaveCriticalSection(&s->lock);
}

// Global semaphore (3 printers)
CustomSemaphore printer_sem;

DWORD WINAPI ClientProcess(LPVOID lpParam) {
    int id = *(int*)lpParam;

    printf("Client %d: Requesting printer...\n", id);

    wait_custom(&printer_sem);

    printf("Client %d: Started printing (2s)...\n", id);
    Sleep(2000);  // print job takes 2 seconds

    printf("Client %d: Finished printing.\n", id);

    signal_custom(&printer_sem);

    return 0;
}

int main() {
    HANDLE threads[5];
    int ids[5];

    // Initialize semaphore with 3 printers
    init_custom(&printer_sem, 3);

    for (int i = 0; i < 5; i++) {
        ids[i] = i + 1;
        threads[i] = CreateThread(NULL, 0, ClientProcess, &ids[i], 0, NULL);
    }

    WaitForMultipleObjects(5, threads, TRUE, INFINITE);

    return 0;
}

