#include <stdio.h>
#include <windows.h>

#define N 5

HANDLE printer;
HANDLE scanner;

DWORD WINAPI student(LPVOID param) {
    int id = *(int*)param;

    while (1) {
        printf("Student %d is WAITING\n", id);
        Sleep(1000);

        WaitForSingleObject(printer, INFINITE);
        WaitForSingleObject(scanner, INFINITE);

        printf("Student %d is USING PRINTER & SCANNER\n", id);
        Sleep(2000);

        ReleaseSemaphore(scanner, 1, NULL);
        ReleaseSemaphore(printer, 1, NULL);

        printf("Student %d COMPLETED work\n", id);
        Sleep(1000);
    }
}

int main() {
    HANDLE threads[N];
    int id[N];

    printer = CreateSemaphore(NULL, 1, 1, NULL);
    scanner = CreateSemaphore(NULL, 1, 1, NULL);

    for (int i = 0; i < N; i++) {
        id[i] = i;
        threads[i] = CreateThread(NULL, 0, student, &id[i], 0, NULL);
    }

    WaitForMultipleObjects(N, threads, TRUE, INFINITE);
    return 0;
}