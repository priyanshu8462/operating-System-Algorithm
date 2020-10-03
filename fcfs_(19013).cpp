//PROGRAM TO IMPLEMENT FIRST-COME-FIRST-SERVE SCHEDULING ALGORITHM
#include<iostream>
#include<conio.h>
#include<iomanip>
using namespace std;

struct ProcessDetail{
	int pid;
	int arrival_time;
	int burst_time;
	
	int response_time;
	int wait_time;
	int turnaround_time;
	
	int start_time;
	int complete_time;
};

class SchedulingAlgorithm{
	double total_wait_time, total_turnaround_time, total_response_time, average_wait_time, average_turnaround_time, average_response_time ;
	int number_of_process;
	ProcessDetail * process;
	public:
		SchedulingAlgorithm(){
			total_wait_time=0;
			total_turnaround_time=0; 
			average_wait_time=0; 
			average_turnaround_time = 0;
			total_response_time=0; 
			average_response_time = 0;

		}
		void input();
		void FCFS();
		void output();
		void sort_arrival_time();	
};

void SchedulingAlgorithm::input(){
	cout<<"\nEnter number of processes :";
	cin>>number_of_process;
	process = new ProcessDetail[number_of_process];
	
	//enter detail for each process
	for(int i=0;i<number_of_process;i++){
		cout<<"\n\nEnter details for process "<<i+1;
		cout<<"\n\t1. Enter PID :";
		cin>>process[i].pid;
		cout<<"\t2. Enter Arrival Time :";
		cin>>process[i].arrival_time;
		cout<<"\t3. Enter Burst Time :";
		cin>>process[i].burst_time;
	}
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

//void fcfs
void SchedulingAlgorithm::FCFS(){
	
		//for visual representation
		process[0].start_time = process[0].arrival_time;
		process[0].complete_time = process[0].arrival_time + process[0].burst_time;
		 
		//wait time for first process
		process[0].wait_time = 0;
		//turnaround time for first process
		process[0].turnaround_time = process[0].burst_time;
		
		
		//calculate wait time, turnaroundtime and response time for rest processes
		for(int i=1;i<number_of_process;i++){
			//for wait time
			process[i].wait_time = process[i-1].arrival_time + process[i-1].wait_time + process[i-1].burst_time - process[i].arrival_time ;
			if(process[i].wait_time<0)
				process[i].wait_time=0;
		
			
			//for visual representation
			process[i].start_time = process[i-1].arrival_time + process[i-1].wait_time + process[i-1].burst_time ;
			process[i].complete_time = process[i-1].arrival_time + process[i-1].wait_time + process[i-1].burst_time + process[i].burst_time;
			
			if((process[i].arrival_time - process[i-1].complete_time) > 0){
				process[i].start_time += process[i].arrival_time - process[i-1].complete_time;
				process[i].complete_time += process[i].arrival_time - process[i-1].complete_time;
			}
			else{
				process[i].start_time+=0;
				process[i].complete_time+=0;
			}
			
			//for turnaround time
			process[i].turnaround_time = process[i].complete_time - process[i].arrival_time ;	
					 		
		}
		
		//response time
		for(int i=0;i<number_of_process;i++){
			process[i].response_time = process[i].start_time - process[i].arrival_time; 
		}
		
		//total wait, turnaround and response time
		for(int i=0;i<number_of_process;i++){
			total_wait_time += process[i].wait_time; 
			total_turnaround_time += process[i].turnaround_time; 
			total_response_time += process[i].response_time; 
		}
		
		//average wait time
		average_wait_time = total_wait_time/number_of_process;
				
		//average turnaround time
		average_turnaround_time = total_turnaround_time/number_of_process;
		
		//average response time
		average_response_time = total_response_time/number_of_process;
	}



//show output
void SchedulingAlgorithm::output(){
	//Tabular Output
	cout<<"\n\n  =====================================================================================";
		cout<<"\n   "<<"   PID"<<"   ArrivalTime"<<"   BurstTime"<<"   Wait time"<<"   Turnaround time"<<"     Response Time";
		cout<<"\n   -----------------------------------------------------------------------------------";
	for(int i=0;i<number_of_process;i++){
		cout<<"\n   "<<setw(5)<<process[i].pid<<setw(9)<<process[i].arrival_time<<setw(14)<<process[i].burst_time<<setw(12)<<process[i].wait_time<<setw(14)<<process[i].turnaround_time<<setw(18)<<process[i].response_time;
	}
	cout<<"\n  =====================================================================================";
	
	
	cout<<"\n\n\nGANTT CHART :\n";
	//Gantt Chart
		cout<<endl;
		for(int k=0;k<number_of_process;k++){
			cout<<"------------  ";
		}
		cout<<endl;
		for(int k=0;k<number_of_process;k++){
			cout<<"|          |  ";
		}
		cout<<endl;
		for(int k=0;k<number_of_process;k++){
			cout<<"|    "<<process[k].pid<<"     |  ";
		}
		cout<<endl;
		for(int k=0;k<number_of_process;k++){
			cout<<"|          |  ";
		}
		cout<<endl;
		for(int k=0;k<number_of_process;k++){
			cout<<"------------  ";
		}
		cout<<endl;
		for(int k=0;k<number_of_process;k++){
				cout<<process[k].start_time<<setw(11)<<process[k].complete_time<<setw(3);
		}
	
	
	//Analysis
	cout<<"\n\nTotal Wait Time :"<<total_wait_time;
	cout<<"\nAverage Wait Time :"<<average_wait_time;
	cout<<"\n\nTotal Turnaround Time :"<<total_turnaround_time;
	cout<<"\nAverage Turnaround Time :"<<average_turnaround_time;
	cout<<"\n\nTotal Response Time :"<<total_response_time;
	cout<<"\nAverage Response Time :"<<average_response_time;
}

int main(){
	SchedulingAlgorithm obj;
	obj.input();
	obj.sort_arrival_time();
	obj.FCFS();
	obj.output();
	getch();
	return 0;
}


/*
				OUTPUT


TEST CASE 1


Enter number of processes :5


Enter details for process 1
        1. Enter PID :1
        2. Enter Arrival Time :5
        3. Enter Burst Time :3


Enter details for process 2
        1. Enter PID :2
        2. Enter Arrival Time :3
        3. Enter Burst Time :5


Enter details for process 3
        1. Enter PID :3
        2. Enter Arrival Time :1
        3. Enter Burst Time :2


Enter details for process 4
        1. Enter PID :4
        2. Enter Arrival Time :4
        3. Enter Burst Time :3


Enter details for process 5
        1. Enter PID :5
        2. Enter Arrival Time :15
        3. Enter Burst Time :2


  =====================================================================================
      PID   ArrivalTime   BurstTime   Wait time   Turnaround time     Response Time
   -----------------------------------------------------------------------------------
       3        1             2           0             2                 0
       2        3             5           0             5                 0
       4        4             3           4             7                 4
       1        5             3           6             9                 6
       5       15             2           0             2                 0
  =====================================================================================


GANTT CHART :

------------  ------------  ------------  ------------  ------------
|          |  |          |  |          |  |          |  |          |
|    3     |  |    2     |  |    4     |  |    1     |  |    5     |
|          |  |          |  |          |  |          |  |          |
------------  ------------  ------------  ------------  ------------
1          3  3          8  8         11 11         14 15         17

Total Wait Time :10
Average Wait Time :2

Total Turnaround Time :25
Average Turnaround Time :5

Total Response Time :10
Average Response Time :2




-------------------------------------------------------------------------------------


TEST CASE 2


Enter number of processes :3


Enter details for process 1
        1. Enter PID :1
        2. Enter Arrival Time :7
        3. Enter Burst Time :8


Enter details for process 2
        1. Enter PID :2
        2. Enter Arrival Time :2
        3. Enter Burst Time :3


Enter details for process 3
        1. Enter PID :3
        2. Enter Arrival Time :10
        3. Enter Burst Time :4


  =====================================================================================
      PID   ArrivalTime   BurstTime   Wait time   Turnaround time     Response Time
   -----------------------------------------------------------------------------------
       2        2             3           0             3                 0
       1        7             8           0             8                 0
       3       10             4           5             9                 5
  =====================================================================================


GANTT CHART :

------------  ------------  ------------
|          |  |          |  |          |
|    2     |  |    1     |  |    3     |
|          |  |          |  |          |
------------  ------------  ------------
2          5  7         15 15         19

Total Wait Time :5
Average Wait Time :1.66667

Total Turnaround Time :20
Average Turnaround Time :6.66667

Total Response Time :5
Average Response Time :1.66667

*/				
