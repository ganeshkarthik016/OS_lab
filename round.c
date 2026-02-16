#include <stdio.h>

int main() {
    int n, tq, time = 0, completed = 0;
    int pid[10], at[10], bt[10], rt[10];
    int wt[10], tat[10], ct[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter AT and BT for P%d: ", pid[i]);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    printf("\nGantt Chart:\n|");

    while (completed < n) {
        int executed = 0;

        for (int i = 0; i < n; i++) {
            if (rt[i] > 0 && at[i] <= time) {
                executed = 1;
                printf(" P%d |", pid[i]);

                if (rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    rt[i] = 0;
                    completed++;
                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                }
            }
        }

        if (!executed)
            time++;
    }

    printf("\n\nPID\tAT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%D\t%d\t%d\n", pid[i],at[i], wt[i], tat[i]);

    return 0;
}