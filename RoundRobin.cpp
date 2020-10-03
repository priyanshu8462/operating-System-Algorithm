//WAP to implement Round Robin scheduling algorithm
#include<iostream>
#include<conio.h>
#include<iomanip>
using namespace std;

struct ProcessDetail{
	int pid;
	int arrival_time;
	int burst_time;
	int remaining_burst_time;
	
	int response_time;
	int wait_time;
	int turnaround_time;
	
	int start_time;
	int complete_time;
};


class SchedulingAlgorithm{
	double total_wait_time, total_turnaround_time, total_response_time, average_wait_time, average_turnaround_time, average_response_time;
	int total_time,p,counter,time_quantum ;
	int number_of_process, current_time;
	ProcessDetail * process;
	ProcessDetail * TEMP;
	public:
		SchedulingAlgorithm(){
			total_wait_time=0;
			total_turnaround_time=0; 
			average_wait_time=0; 
			average_turnaround_time = 0;
			total_response_time=0; 
			average_response_time = 0;
			current_time=0;
			total_time=0;
			p=0;
			counter=0;
			time_quantum=0;
		}
		void input();
		void output();
		void sort_arrival_time();
		void RoundRobin();
};

//input
void SchedulingAlgorithm::input(){
	cout<<"\nEnter number of processes :";
	cin>>number_of_process;
	process = new ProcessDetail[number_of_process];
	//enter detail for each process
	for(int i=0;i<number_of_process;i++){
		cout<<"\n\nEnter details for process "<<i+1;
		process[i].pid = i+1;
		cout<<"\n\t1. PID :"<<process[i].pid;
		cout<<"\n\t2. Enter Arrival Time :";
		cin>>process[i].arrival_time;
		cout<<"\t3. Enter Burst Time :";
		cin>>process[i].burst_time;
		
		total_time +=process[i].burst_time;  
		process[i].remaining_burst_time = process[i].burst_time;
	}
	cout<<"\nEnter time quantum :";
	cin>>time_quantum;
}

//function to sort process according to their arrival time
void SchedulingAlgorithm::sort_arrival_time(){
	for(int i=0;i<number_of_process-1;i++){
		int min = i;
		for(int j=i+1;j<number_of_process;j++){
			if(process[j].arrival_time<process[min].arrival_time)
				min=j;
		}
		
		if(process[min].arrival_time!=process[i].arrival_time)
		{
			ProcessDetail temp=process[min];
			process[min]=process[i];
			process[i]=temp;		
		}
	}
}

//function to imply Round Robin scheduling
void SchedulingAlgorithm::RoundRobin(){
	TEMP = new ProcessDetail[total_time];
	current_time = process[0].arrival_time;
	while(counter < number_of_process){
			for(int i=0; i<number_of_process; i++){
				
				if(process[i].arrival_time > current_time  && counter!=i){
					break;
				}
					
				else if(process[i].arrival_time > current_time  && counter==i){
					current_time = process[i].arrival_time;
				}	
				
				if(process[i].remaining_burst_time == 0){
					continue;
				}
				
				if(process[i].remaining_burst_time == process[i].burst_time ){
					process[i].start_time = current_time;
					process[i].response_time=current_time - process[i].arrival_time;
				}
				
					TEMP[p].pid = process[i].pid;
					TEMP[p].start_time = current_time;
				
				if(process[i].remaining_burst_time > time_quantum){
					current_time += time_quantum;
					process[i].remaining_burst_time -= time_quantum;
				}
				
				else if(process[i].remaining_burst_time <= time_quantum) {
					current_time +=  process[i].remaining_burst_time;
					process[i].remaining_burst_time = 0;
					process[i].complete_time = current_time;
					process[i].turnaround_time = process[i].complete_time - process[i].arrival_time;
					process[i].wait_time = process[i].turnaround_time - process[i].burst_time;
					counter++;
				}
				
				
				TEMP[p].complete_time=current_time;
				p++;		
				
			}
	}
}

void SchedulingAlgorithm::output(){
	
	cout<<"\n\n  ====================================================================================================\n";
	
	cout<<setw(1)<<"\tPID"<<setw(15)<<"Arrival Time"<<setw(15)<<"Burst Time"<<setw(15)<<"Waiting Time"<<setw(20)<<"Turnaround Time"<<setw(20)<<"Response Time";
	cout<<"\n    ------------------------------------------------------------------------------------------------\n";
	for(int i=0;i<number_of_process;i++){
		cout<<"   "<<setw(5)<<process[i].pid<<setw(12)<<process[i].arrival_time<<setw(15)<<process[i].burst_time<<setw(15)<<process[i].wait_time<<setw(20)<<process[i].turnaround_time<<setw(20)<<process[i].response_time<<endl;
	}
	cout<<"  ====================================================================================================";

	int l=0;
	cout<<"\n\n ( start : "<<TEMP[0].start_time<<" ) ------ P"<<TEMP[0].pid<<" ------ (complete : ";
	while(TEMP[l].pid == TEMP[0].pid){
		l++;
	}
	cout<<TEMP[l-1].complete_time<<") ====>";
	for(int i=l; i<p; i++){
	int k=i+1;
		cout<<" ( start : "<<TEMP[i].start_time<<" ) ------ P"<<TEMP[i].pid<<" ------ (complete : ";
		while(TEMP[k].pid == TEMP[i].pid){
			k++;
			i++;
	}	
		cout<<TEMP[i].complete_time<<") ====>";
	}
	cout<<"ALL PROCESS EXECUTED \n\n";
		
}


int main(){
	SchedulingAlgorithm obj;
	obj.input();
	obj.sort_arrival_time();
	obj.RoundRobin();
	obj.output();
	getch();
	return 0;
}


/*
				output
				
	TEST CASE 1 :
	
Enter number of processes :3


Enter details for process 1
        1. PID :1
        2. Enter Arrival Time :0
        3. Enter Burst Time :24


Enter details for process 2
        1. PID :2
        2. Enter Arrival Time :0
        3. Enter Burst Time :3


Enter details for process 3
        1. PID :3
        2. Enter Arrival Time :0
        3. Enter Burst Time :3

Enter time quantum :4


  ====================================================================================================
        PID   Arrival Time     Burst Time   Waiting Time     Turnaround Time       Response Time
    ------------------------------------------------------------------------------------------------
       1           0             24              6                  30                   0
       2           0              3              4                   7                   4
       3           0              3              7                  10                   7
  ====================================================================================================

 ( start : 0 ) ------ P1 ------ (complete : 4) ====> ( start : 4 ) ------ P2 ------ (complete : 7) ====> ( start : 7 ) ------ P3 ------ (complete : 10) ====> ( start : 10 ) ------ P1 ------ (complete : 30) ====>ALL PROCESS EXECUTED


-----------------------------------------------------------------------------------------------------------------------------------------

TEST CASE 2 :


Enter number of processes :3


Enter details for process 1
        1. PID :1
        2. Enter Arrival Time :1
        3. Enter Burst Time :24


Enter details for process 2
        1. PID :2
        2. Enter Arrival Time :6
        3. Enter Burst Time :3


Enter details for process 3
        1. PID :3
        2. Enter Arrival Time :7
        3. Enter Burst Time :3

Enter time quantum :4


  ====================================================================================================
        PID   Arrival Time     Burst Time   Waiting Time     Turnaround Time       Response Time
    ------------------------------------------------------------------------------------------------
       1           1             24              6                  30                   0
       2           6              3              3                   6                   3
       3           7              3              5                   8                   5
  ====================================================================================================

 ( start : 1 ) ------ P1 ------ (complete : 9) ====> ( start : 9 ) ------ P2 ------ (complete : 12) ====> ( start : 12 ) ------ P3 ------ (complete : 15) ====> ( start : 15 ) ------ P1 ------ (complete : 31) ====>ALL PROCESS EXECUTED


-------------------------------------------------------------------------------------------------------------------------------------

TEST CASE 3 :


Enter number of processes :3


Enter details for process 1
        1. PID :1
        2. Enter Arrival Time :1
        3. Enter Burst Time :8


Enter details for process 2
        1. PID :2
        2. Enter Arrival Time :15
        3. Enter Burst Time :6


Enter details for process 3
        1. PID :3
        2. Enter Arrival Time :16
        3. Enter Burst Time :4

Enter time quantum :4


  ====================================================================================================
        PID   Arrival Time     Burst Time   Waiting Time     Turnaround Time       Response Time
    ------------------------------------------------------------------------------------------------
       1           1              8              0                   8                   0
       2          15              6              4                  10                   0
       3          16              4              3                   7                   3
  ====================================================================================================

 ( start : 1 ) ------ P1 ------ (complete : 9) ====> ( start : 15 ) ------ P2 ------ (complete : 19) ====> ( start : 19 ) ------ P3 ------ (complete : 23) ====> ( start : 23 ) ------ P2 ------ (complete : 25) ====>ALL PROCESS EXECUTED

			


*/
