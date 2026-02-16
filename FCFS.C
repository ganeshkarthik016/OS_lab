#include <stdio.h>
#include <string.h>
void calculateTimes(int n, int bt[], int at[] , int p[]) {
    int wt[n], tat[n], ct[n];
    float total_wt = 0, total_tat = 0;
    ct[0] = at[0] + bt[0]; 
    for (int i = 1; i < n; i++) {
        if (at[i] > ct[i-1]) {
            ct[i] = at[i] + bt[i];
        } else {
            ct[i] = ct[i-1] + bt[i];
        }
    }
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("p%d\t%d\t%d\t%d\t%d\t%d\n",p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int bt[n], at[n];
int p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        p[i] = i+1;
    }

    for(int i = 0;i<n;i++){
        for(int j = i+1;j<n;j++){
            if(at[i]>at[j]){
                int t,t1;
                t = at[i];
                at[i] = at[j];
                at[j] = t;
                t1 = bt[i];
                bt[i] = bt[j];
                bt[j] = bt[i];
                int t2;
                t2 = p[i];
                p[i] = p[j];
                p[j] = t2;
            }
        }
    }
    calculateTimes(n, bt, at,p);
    return 0;
}