#include <stdio.h>
#include <windows.h>

#define N 5

HANDLE forks[N];
HANDLE waiter;

DWORD WINAPI philosopher(LPVOID param) {
    int id = *(int*)param;

    while (1) {
        printf("Philosopher %d is THINKING\n", id);
        Sleep(10);

        WaitForSingleObject(waiter, INFINITE);

        WaitForSingleObject(forks[id], INFINITE);
        WaitForSingleObject(forks[(id + 1) % N], INFINITE);

        printf("Philosopher %d is EATING\n", id);
        Sleep(20);

        ReleaseSemaphore(forks[id], 1, NULL);
        ReleaseSemaphore(forks[(id + 1) % N], 1, NULL);

        ReleaseSemaphore(waiter, 1, NULL);
    }
}

int main() {
    HANDLE threads[N];
    int id[N];

    waiter = CreateSemaphore(NULL, N - 1, N - 1, NULL);

    for (int i = 0; i < N; i++)
        forks[i] = CreateSemaphore(NULL, 1, 1, NULL);

    for (int i = 0; i < N; i++) {
        id[i] = i;
        threads[i] = CreateThread(NULL, 0, philosopher, &id[i], 0, NULL);
    }

    WaitForMultipleObjects(N, threads, TRUE, INFINITE);
    return 0;
}
