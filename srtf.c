#include <stdio.h>

int main() {
    int n, time = 0, completed = 0;
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

    printf("\nGantt Chart:\n|");

    while (completed < n) {
        int idx = -1, min_rt = 9999;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && rt[i] < min_rt) {
                min_rt = rt[i];
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
        } else {
            printf(" P%d |", pid[idx]);
            rt[idx]--;
            time++;

            if (rt[idx] == 0) {
                completed++;
                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
            }
        }
    }

    printf("\n\nPID\tAT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\n", pid[i],at[i], wt[i], tat[i]);

    return 0;
}