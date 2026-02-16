#include <stdio.h>

int main() {
    int n, i, time = 0, completed = 0;
    int pid[10], at[10], bt[10], ct[10], wt[10], tat[10];
    int done[10] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter AT and BT for P%d: ", pid[i]);
        scanf("%d %d", &at[i], &bt[i]);
    }

    printf("\nGantt Chart:\n|");

    while (completed < n) {
        int idx = -1, min_bt = 9999;

        for (i = 0; i < n; i++) {
            if (at[i] <= time && !done[i] && bt[i] < min_bt) {
                min_bt = bt[i];
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
        } else {
            printf(" P%d |", pid[idx]);
            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            done[idx] = 1;
            completed++;
        }
    }

    printf("\n\nPID\tAT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\n", pid[i],at[i], wt[i], tat[i]);

    return 0;
}