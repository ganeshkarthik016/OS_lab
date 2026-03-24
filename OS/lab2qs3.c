#include <stdio.h>

int main() {
    int n, tq;
    int pid[10], at[10], bt[10], rt[10];
    int wt[10], tat[10], ct[10];

    int queue[50], front = 0, rear = 0;
    int visited[10] = {0};

    int time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", pid[i]);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int min_at = 9999, first = -1;
    for (int i = 0; i < n; i++) {
        if (at[i] < min_at) {
            min_at = at[i];
            first = i;
        }
    }

    time = at[first];
    queue[rear++] = first;
    visited[first] = 1;

    printf("\nGantt Chart:\n|");

    while (completed < n) {
        int idx = queue[front++];

        if (rt[idx] > tq) {
            printf(" P%d |", pid[idx]);
            time += tq;
            rt[idx] -= tq;
        } else {
            printf(" P%d |", pid[idx]);
            time += rt[idx];
            rt[idx] = 0;
            completed++;
            ct[idx] = time;
        }

  
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !visited[i] && rt[i] > 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (rt[idx] > 0) {
            queue[rear++] = idx;
        }


        if (front == rear && completed < n) {
            for (int i = 0; i < n; i++) {
                if (rt[i] > 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                    time = at[i];
                    break;
                }
            }
        }
    }

    printf("\n\nPID\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i],ct[i], wt[i], tat[i]);
    }

    return 0;
}