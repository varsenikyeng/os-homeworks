#include <stdio.h>
struct Process {
	int pid;
	int arrival_time;
	int burst_time;
	int turnaround_time;
	int waiting_time;
	int response_time;
};

void sortByArrTime(struct Process p[], int n){
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if(p[i].arrival_time > p[j].arrival_time){
				struct Process temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
}
void printOutput(struct Process p[], int n){
        printf("PID\tAT\tBT\tWT\tTAT\tRT\n");
        for(int i = 0; i < n; i++){
                printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].waiting_time,p[i].turnaround_time, p[i].response_time);
        }
}
void fcfs(struct Process p[], int n){
	sortByArrTime(p, n);

	int current_time = 0;
	float total_wt = 0;
	float total_tat = 0;
	float total_rt = 0;
	printf("\n=== First Come First Served (FCFS) ===\nGantt Chart: ");
	for (int i = 0; i < n; i++){
		if (current_time < p[i].arrival_time)
			current_time = p[i].arrival_time;
		printf("| P%d",p[i].pid);
		p[i].waiting_time = current_time - p[i].arrival_time;
		p[i].response_time = current_time - p[i].arrival_time;
		current_time += p[i].burst_time;
		p[i].turnaround_time = current_time - p[i].arrival_time;
		total_wt += p[i].waiting_time;
		total_rt += p[i].response_time;
		total_tat += p[i].turnaround_time;
	}
	printf( "| \n");

	printOutput(p, n);
	printf("Average Waiting Time: %.2lf \n", total_wt/n);
	printf("Average Turnaround Time: %.2lf \n", total_tat/n);
	printf("Average Response Time: %.2lf \n", total_rt/n);

}
void sjf(struct Process p[], int n){
        sortByArrTime(p, n);

        int current_time = 0;
        float total_wt = 0;
        float total_tat = 0;
        float total_rt = 0;
        printf("\n=== Shortest Job First (SJF) ===\nGantt Chart: ");
        for (int i = 0; i < n; i++){
                if (current_time < p[i].arrival_time)
                        current_time = p[i].arrival_time;
		int index = i;
		for (int j= i + 1; j < n; j++){
			if(p[j].arrival_time <= current_time && p[j].burst_time < p[index].burst_time)
				index = j;
		}
		if(index != i){
			struct Process temp = p[i];
			p[i] = p[index];
			p[index] = temp;
		}
                printf("| P%d",p[i].pid);
                p[i].waiting_time = current_time - p[i].arrival_time;
                p[i].response_time = current_time - p[i].arrival_time;
                current_time += p[i].burst_time;
                p[i].turnaround_time = current_time - p[i].arrival_time;
                total_wt += p[i].waiting_time;
                total_rt += p[i].response_time;
                total_tat += p[i].turnaround_time;
        }
        printf( "| \n");

        printOutput(p, n);
        printf("Average Waiting Time: %.2lf \n", total_wt/n);
        printf("Average Turnaround Time: %.2lf \n", total_tat/n);
        printf("Average Response Time: %.2lf \n", total_rt/n);

}

int main(){
	int n;
	printf("Enter the number of processes : ");
	scanf("%d", &n);
	struct Process example[n];
	for(int i = 1; i<=n; i++){
		example[i-1].pid = i;
		printf("Enter the arrival time and burst time for process %d : ", i);
		scanf("%d",&example[i-1].arrival_time);
		scanf("%d", &example[i-1].burst_time);
	}

	fcfs(example, n);
	sjf(example, n);

}
