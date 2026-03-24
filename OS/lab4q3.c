#include <stdio.h>
#include <windows.h>

#define WRITERS 4
#define READERS 6


typedef struct {
    int value;               
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
            s->value = 0;  
            LeaveCriticalSection(&s->lock);
            break;
        }

        LeaveCriticalSection(&s->lock);
        Sleep(10); 
    }
}


void V(BinarySemaphore *s) {
    EnterCriticalSection(&s->lock);
    s->value = 1;   
    LeaveCriticalSection(&s->lock);
}

BinarySemaphore log_sem;


DWORD WINAPI WriterProcess(LPVOID lpParam) {
    int id = *(int*)lpParam;

    printf("Writer %d: Waiting to write log...\n", id);
    P(&log_sem);

    printf("Writer %d: Writing to log file...\n", id);
    Sleep(2000); 

    printf("Writer %d: Done writing.\n", id);
    V(&log_sem);

    return 0;
}


DWORD WINAPI ReaderProcess(LPVOID lpParam) {
    int id = *(int*)lpParam;

    printf("Reader %d: Waiting to read log...\n", id);
    P(&log_sem);

    printf("Reader %d: Reading log file...\n", id);
    Sleep(1500); 

    printf("Reader %d: Done reading.\n", id);
    V(&log_sem);

    return 0;
}

int main() {
    HANDLE wthreads[WRITERS], rthreads[READERS];
    int wids[WRITERS], rids[READERS];

 
    init_sem(&log_sem, 1);

    for (int i = 0; i < WRITERS; i++) {
        wids[i] = i + 1;
        wthreads[i] = CreateThread(NULL, 0, WriterProcess, &wids[i], 0, NULL);
    }


    for (int i = 0; i < READERS; i++) {
        rids[i] = i + 1;
        rthreads[i] = CreateThread(NULL, 0, ReaderProcess, &rids[i], 0, NULL);
    }

    WaitForMultipleObjects(WRITERS, wthreads, TRUE, INFINITE);
    WaitForMultipleObjects(READERS, rthreads, TRUE, INFINITE);

    return 0;
}
