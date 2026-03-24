#include <stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n];
    int completed[n];
    for (int i = 0; i < n; i++) completed[i] = 0;

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("\nProcess %d\n", pid[i]);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    int time = 0, done = 0;

    while (done < n) {
        int idx = -1;
        int minBT = 1e9;

        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= time && bt[i] < minBT) {
                minBT = bt[i];
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
        } else {
            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed[idx] = 1;
            done++;
        }
    }

    printf("\nPID AT BT CT TAT WT\n");
    for (int i = 0; i < n; i++) {
        printf("%d  %d  %d  %d  %d  %d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    return 0;
}