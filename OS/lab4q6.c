#include <stdio.h>
#include <windows.h>

#define READERS 3
#define WRITERS 2

// Semaphore structure
typedef struct {
    int value;
    CRITICAL_SECTION lock;
} Semaphore;

// Initialize semaphore
void init_sem(Semaphore *s, int val) {
    s->value = val;
    InitializeCriticalSection(&s->lock);
}

// P() operation (wait)
void P(Semaphore *s) {
    while (1) {
        EnterCriticalSection(&s->lock);

        if (s->value > 0) {
            s->value--;
            LeaveCriticalSection(&s->lock);
            break;
        }

        LeaveCriticalSection(&s->lock);
        Sleep(10);
    }
}

// V() operation (signal)
void V(Semaphore *s) {
    EnterCriticalSection(&s->lock);
    s->value++;
    LeaveCriticalSection(&s->lock);
}

// Semaphores
Semaphore mutex, wrt;
int readcount = 0;

// Reader thread
DWORD WINAPI Reader(LPVOID lpParam) {
    int id = *(int*)lpParam;

    // Entry section
    P(&mutex);
    readcount++;
    if (readcount == 1)
        P(&wrt);   // first reader blocks writer
    V(&mutex);

    // Critical section (reading)
    printf("Reader %d: Reading data...\n", id);
    Sleep(1500);

    // Exit section
    P(&mutex);
    readcount--;
    if (readcount == 0)
        V(&wrt);   // last reader releases writer
    V(&mutex);

    return 0;
}

// Writer thread
DWORD WINAPI Writer(LPVOID lpParam) {
    int id = *(int*)lpParam;

    P(&wrt);   // exclusive access

    printf("Writer %d: Writing data...\n", id);
    Sleep(2000);

    V(&wrt);

    return 0;
}

int main() {
    HANDLE rthreads[READERS], wthreads[WRITERS];
    int rids[READERS], wids[WRITERS];

    // Initialize semaphores
    init_sem(&mutex, 1); // protects readcount
    init_sem(&wrt, 1);   // controls access to data

    // Create reader threads
    for (int i = 0; i < READERS; i++) {
        rids[i] = i + 1;
        rthreads[i] = CreateThread(NULL, 0, Reader, &rids[i], 0, NULL);
    }

    // Create writer threads
    for (int i = 0; i < WRITERS; i++) {
        wids[i] = i + 1;
        wthreads[i] = CreateThread(NULL, 0, Writer, &wids[i], 0, NULL);
    }

    WaitForMultipleObjects(READERS, rthreads, TRUE, INFINITE);
    WaitForMultipleObjects(WRITERS, wthreads, TRUE, INFINITE);

    return 0;
}
