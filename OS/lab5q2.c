#include <stdio.h>
#include <windows.h>

#define N 5

HANDLE books[N];
HANDLE waiter;

DWORD WINAPI scholar(LPVOID param) {
    int id = *(int*)param;

    while (1) {
        printf("Scholar %d is RESTING\n", id);
        Sleep(1000);

        WaitForSingleObject(waiter, INFINITE);

        WaitForSingleObject(books[id], INFINITE);
        WaitForSingleObject(books[(id + 1) % N], INFINITE);

        printf("Scholar %d is STUDYING\n", id);
        Sleep(2000);

        ReleaseSemaphore(books[id], 1, NULL);
        ReleaseSemaphore(books[(id + 1) % N], 1, NULL);

        ReleaseSemaphore(waiter, 1, NULL);
    }
}

int main() {
    HANDLE threads[N];
    int id[N];

    waiter = CreateSemaphore(NULL, N - 1, N - 1, NULL);

    for (int i = 0; i < N; i++)
        books[i] = CreateSemaphore(NULL, 1, 1, NULL);

    for (int i = 0; i < N; i++) {
        id[i] = i;
        threads[i] = CreateThread(NULL, 0, scholar, &id[i], 0, NULL);
    }

    WaitForMultipleObjects(N, threads, TRUE, INFINITE);
    return 0;
}
