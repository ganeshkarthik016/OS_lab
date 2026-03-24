#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BUFFER_SIZE 5

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

// Shared buffer
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores
Semaphore empty, full, mutex;

// Producer thread
DWORD WINAPI Producer(LPVOID lpParam) {
    int item;

    while (1) {
        item = rand() % 100; // produce item
        printf("Producer produced: %d\n", item);

        P(&empty);  // wait for empty slot
        P(&mutex);  // enter critical section

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        printf("Producer inserted: %d\n", item);

        V(&mutex);  // exit critical section
        V(&full);   // signal item available

        Sleep(1000);
    }
    return 0;
}

// Consumer thread
DWORD WINAPI Consumer(LPVOID lpParam) {
    int item;

    while (1) {
        P(&full);   // wait for item
        P(&mutex);  // enter critical section

        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumer consumed: %d\n", item);

        V(&mutex);  // exit critical section
        V(&empty);  // signal empty slot

        Sleep(1500);
    }
    return 0;
}

int main() {
    HANDLE pThread, cThread;

    srand(GetTickCount());

    // Initialize semaphores
    init_sem(&empty, BUFFER_SIZE); // all slots empty
    init_sem(&full, 0);            // no items initially
    init_sem(&mutex, 1);           // binary semaphore

    // Create producer and consumer threads
    pThread = CreateThread(NULL, 0, Producer, NULL, 0, NULL);
    cThread = CreateThread(NULL, 0, Consumer, NULL, 0, NULL);

    WaitForSingleObject(pThread, INFINITE);
    WaitForSingleObject(cThread, INFINITE);

    return 0;
}
