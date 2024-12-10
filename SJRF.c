#include <stdio.h>
#define MAX 10

int main() {
    int arrival_time[MAX], burst_time[MAX];
    // int priority[MAX];
    int completion_time[MAX], waiting_time[MAX], turnaround_time[MAX];
    int n, i, j;
    float avg_waiting_time, avg_turnaround_time;
    
    printf("Enter the total number of processes (max %d): ", MAX);
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time of Process %d: ", i + 1);
        scanf("%d", &arrival_time[i]);
        printf("Enter Burst Time of Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        // printf("Enter Priority of Process %d (lower number means higher priority): ", i + 1);
        // scanf("%d", &priority[i]);
    }

    int completed[MAX] = {0};
    int time = 0, count = 0;
    int process_id;

    while (count < n) {
        int highest_bt = 100; // Arbitrary large number
        process_id = -1;

        // Find the process with the highest priority that has arrived
        for (i = 0; i < n; i++) {
            if (!completed[i] && arrival_time[i] <= time && burst_time[i] < highest_bt) {
                highest_bt = burst_time[i];
                process_id = i;
            }
        }

        if (process_id != -1) {
            // Execute the selected process
            time += burst_time[process_id];
            completion_time[process_id] = time;
            turnaround_time[process_id] = completion_time[process_id] - arrival_time[process_id];
            waiting_time[process_id] = turnaround_time[process_id] - burst_time[process_id];
            completed[process_id] = 1;
            count++;

        } else {
            // If no process is ready to execute, increment time
            time++;
        }
    }

    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            i + 1,
            arrival_time[i],
            burst_time[i],
           
            completion_time[i],
            waiting_time[i],
            turnaround_time[i]);
    }

    avg_waiting_time = (float)total_waiting_time / n;
    avg_turnaround_time = (float)total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}

//- - - - -- - - -- - - -- - - - - -- - - - - -- - -- - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - -- - - -- - -- - - - - 
// #include<stdio.h>
// #define MAX 10
// int main(){
//     int n,i,j;
//     int at[MAX],bt[MAX],ct[MAX],wt[MAX],tat[MAX];
//     float avg_wt,avg_tat;
//     printf("Enter the number of procesess (MAX %d):\n",MAX);
//     scanf("%d",&n);

   
//     for(i=0;i<n;i++){
//     printf("\nEnter the arrival Time  :");
//     scanf("%d",&at[i]);
//      printf("\nEnter the  Burst Time :");
//      scanf("%d",&bt[i]);

//     }
    
//     int completed[MAX]={0};
//     int time=0,count=0;
//     int processid;

//     while(count<n){
//         int hightest_bt=100;
//         processid=-1;

//             for(i =0;i<n;i++){
//                 if(!completed[i] && at[i]<=time && bt[i]<hightest_bt){
//                     hightest_bt=bt[i];
//                     processid=i;

//                 }
//             }

//         if(processid != -1){
//             time+=bt[processid];
//             ct[processid]=time;
//             tat[processid]=ct[processid]-at[processid];
//             wt[processid]=tat[processid]-bt[processid];
//             completed[processid]=1;
//             count++;
//         }else{
//              time++;}

        
//     }
//     int total_tat=0;
//     int total_wt=0;

//     printf("\n Process \t arrival Time \t burst Time\t Completion Time \t waiting time \t turnaround time \n");
//     for(i=0;i<n;i++){
//         total_tat+=tat[i];
//         total_wt+=wt[i];
//         printf("%d\t %d \t\t %d \t\t %d \t\t%d \t\t%d \n",i+1,at[i],bt[i],ct[i],wt[i],tat[i]);
//     }
//     avg_tat=(float)total_tat/n;
//     avg_wt=(float)total_wt/n;

//     printf("\n Average TAT is %.2d",avg_tat);
//     printf("\n Average WT is %.2f",avg_wt);
    

//     return 0;
// }

