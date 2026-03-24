#include<stdio.h>
#include<stdlib.h>
int main(){
    int n;
    printf("Enter the no.of process ");
    scanf("%d",&n);
    int pid[10],at[10],bt[10],ct[10],tat[10],wt[10];
    for(int i=0;i<n;i++){
        pid[i]=i+1;
        printf("enter the arrival time for the process %d:",pid[i]);
        scanf("%d",&at[i]);
        printf("enter the burst time for the process %d:",pid[i]);
        scanf("%d",&bt[i]);
    }
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(at[i] > at[j]) {
             
                int temp = at[i];
                at[i] = at[j];
                at[j] = temp;

          
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

      
                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }
    ct[0] = at[0] + bt[0];
    wt[0] = 0;
    tat[0] = bt[0];
    for(int i=0;i<n;i++){
        if(ct[i-1]<at[i]){
            ct[i]=at[i]+bt[i];

        }
        else{
            ct[i]=ct[i-1]+bt[i];
        }
        wt[i]=ct[i-1]-at[i];
        if(wt[i]<0){
            wt[i]=0;
        }
        tat[i]=wt[i]+bt[i];
    }
    int avg_wt=0,avg_tat=0;
    for(int i=0;i<n;i++){
        avg_wt+=wt[i];
        avg_tat+=tat[i];
    }
    avg_wt/=n;
    avg_tat/=n;
    for(int i=0;i<n;i++){
         printf("\nProcess\tAT\tBT\tWT\tTAT");
    for(i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d",
               pid[i], at[i], bt[i], wt[i], tat[i]);
    }
    }
        printf("\n\nAverage Waiting Time = %d", avg_wt);
    printf("\nAverage Turnaround Time = %d", avg_tat);
    return 0;
    
}