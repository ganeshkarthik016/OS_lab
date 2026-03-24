#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int at;        
    int bt;        
    int rt;        
    int pr;       
    int ct;        
    int tat;      
    int wt;       
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess %d\n", p[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Priority (lower = higher priority): ");
        scanf("%d", &p[i].pr);
        p[i].rt = p[i].bt;
    }

    int time = 0, completed = 0;
    int prev = -1;

    while (completed < n) {
        int idx = -1;
        int bestPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                if (p[i].pr < bestPriority) {
                    bestPriority = p[i].pr;
                    idx = i;
                }
        
                else if (p[i].pr == bestPriority &&
                         p[i].at < p[idx].at) {
                    idx = i;
                }
            }
        }

      
        if (idx == -1) {
            time++;
            continue;
        }

 
        p[idx].rt--;
        time++;

       
        if (p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
        }
    }

    float avg_wt = 0, avg_tat = 0;

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);

        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }


    return 0;
}