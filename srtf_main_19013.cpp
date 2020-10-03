//WAP to implement SRTF scheduling algorithm
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
	int total_time,q;
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
			q=0;
		}
		void input();
		void output();
		void sort_arrival_time();
		void assign_queue();
		void sort_remaining_burst_time(int start,int end);	
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

//function to sort process with same arrival time according to their burst time
void SchedulingAlgorithm::sort_remaining_burst_time(int start, int end){
	for(int i=start;i<end-1;i++){
		int min = i;
		for(int j=i+1;j<end;j++){
			if(process[j].burst_time<process[min].burst_time)
				min=j;
		}

		if(process[min].burst_time!=process[i].burst_time)
		{
			ProcessDetail temp=process[min];
			process[min]=process[i];
			process[i]=temp;		
		}
	}
}

//assign queue to processes
void SchedulingAlgorithm::assign_queue(){
	TEMP = new ProcessDetail[total_time];
	int i=0,p=0;
	while(i<number_of_process){
		
		//section for sorting the process wrt their remaining burst time at a particular currenttime
			int j=i;
			while(j<number_of_process){
				if(process[j].arrival_time>current_time){
					break;
				}
				j++;
			}
			sort_remaining_burst_time(i,j);
		
		if(current_time<process[i].arrival_time)
			current_time=process[i].arrival_time;
		
		if(process[i].remaining_burst_time==process[i].burst_time){
			process[i].response_time=current_time - process[i].arrival_time;	
			process[i].start_time=current_time;
		}
		TEMP[p].pid = process[i].pid;
		TEMP[p].start_time = current_time;
		
		process[i].remaining_burst_time--;
		current_time++;
		
		if(process[i].remaining_burst_time==0){
			process[i].complete_time=current_time;
			process[i].turnaround_time = process[i].complete_time - process[i].arrival_time;
			process[i].wait_time = process[i].turnaround_time - process[i].burst_time;
			
			total_wait_time+=process[i].wait_time;
			total_turnaround_time+=process[i].turnaround_time;
			total_response_time+=process[i].response_time;
			
			i++;
		}
		
		TEMP[p].complete_time=current_time;
		p++;		
	} 
	
	average_wait_time= total_wait_time/number_of_process;
	average_turnaround_time=total_turnaround_time/number_of_process;
	average_response_time=total_response_time/number_of_process;
}

//output
void SchedulingAlgorithm::output(){
	cout<<"\n\n  ====================================================================================================\n";
	
	cout<<setw(1)<<"\tPID"<<setw(15)<<"Arrival Time"<<setw(15)<<"Burst Time"<<setw(15)<<"Waiting Time"<<setw(20)<<"Turnaround Time"<<setw(20)<<"Response Time";
	cout<<"\n    ------------------------------------------------------------------------------------------------\n";
	for(int i=0;i<number_of_process;i++){
		cout<<"   "<<setw(5)<<process[i].pid<<setw(12)<<process[i].arrival_time<<setw(15)<<process[i].burst_time<<setw(15)<<process[i].wait_time<<setw(20)<<process[i].turnaround_time<<setw(20)<<process[i].response_time<<endl;
	}
	cout<<"  ====================================================================================================";

	
	cout<<"\n\n\nGANTT CHART :\n";
	//Gantt Chart
		cout<<endl;
		for(int k=0;k<total_time;k++){
			cout<<"------  ";
		}
		
		cout<<endl;
		for(int k=0;k<total_time;k++){
			cout<<"| "<<TEMP[k].pid<<"  |  ";
		}
		
		cout<<endl;
		for(int k=0;k<total_time;k++){
			cout<<"------  ";
		}
		cout<<endl;
		for(int i=0;i<total_time;i++)
		cout<<TEMP[i].start_time<<setw(5)<<TEMP[i].complete_time<<setw(3);
		cout<<endl;

		int l=0;
		cout<<"\n\n ( start : "<<TEMP[0].start_time<<" ) ------ P"<<TEMP[0].pid<<" ------ (complete : ";
		while(TEMP[l].pid == TEMP[0].pid){
			l++;
		}
		cout<<TEMP[l-1].complete_time<<") ====>";
		for(int i=l; i<total_time; i++){
			int k=i+1;
			cout<<" ( start : "<<TEMP[i].start_time<<" ) ------ P"<<TEMP[i].pid<<" ------ (complete : ";
			while(TEMP[k].pid == TEMP[i].pid){
				k++;
				i++;
			}	
			cout<<TEMP[i].complete_time<<") ====>";
		}
		cout<<"ALL PROCESS EXECUTED \n\n";
			
		cout<<endl<<"Average Waiting Time = "<<average_wait_time;
		cout<<endl<<"Average Turnaround Time = "<<average_turnaround_time;
		cout<<endl<<"Average Response Time = "<<average_response_time<<endl;
		cout<<endl;
	
}


int main(){
	SchedulingAlgorithm obj;
	obj.input();
	obj.sort_arrival_time();
	obj.assign_queue();
	obj.output();
	getch();
	return 0;
}

/*
					OUTPUT
			======================
			
	TEST CASE 1 :
	
	
		Enter number of processes :4
		
		
		Enter details for process 1
		        1. PID :1
		        2. Enter Arrival Time :0
		        3. Enter Burst Time :8
		
		
		Enter details for process 2
		        1. PID :2
		        2. Enter Arrival Time :1
		        3. Enter Burst Time :4
		
		
		Enter details for process 3
		        1. PID :3
		        2. Enter Arrival Time :2
		        3. Enter Burst Time :6
		
		
		Enter details for process 4
		        1. PID :4
		        2. Enter Arrival Time :3
		        3. Enter Burst Time :2
		
		
		  ====================================================================================================
		        PID   Arrival Time     Burst Time   Waiting Time     Turnaround Time       Response Time
		    ------------------------------------------------------------------------------------------------
		       4           3              2              0                   2                   0
		       2           1              4              2                   6                   0
		       3           2              6              5                  11                   5
		       1           0              8             12                  20                   0
		  ====================================================================================================
		
		
		GANTT CHART :
		
		------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------
		| 1  |  | 2  |  | 2  |  | 4  |  | 4  |  | 2  |  | 2  |  | 3  |  | 3  |  | 3  |  | 3  |  | 3  |  | 3  |  | 1  |  | 1  |  | 1  |  | 1  |  | 1  |  | 1  |  | 1  |
		------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------
		0    1  1    2  2    3  3    4  4    5  5    6  6    7  7    8  8    9  9   10 10   11 11   12 12   13 13   14 14   15 15   16 16   17 17   18 18   19 19   20
		
		
		 ( start : 0 ) ------ P1 ------ (complete : 1) ====> ( start : 1 ) ------ P2 ------ (complete : 3) ====> ( start : 3 ) ------ P4 ------ (complete : 5) ====> 
		 ( start : 5 ) ------ P2 ------ (complete : 7) ====> ( start : 7 ) ------ P3 ------ (complete : 13) ====> ( start : 13 ) ------ P1 ------ (complete : 20) ====>ALL PROCESS EXECUTED
		
		
		Average Waiting Time = 4.75
		Average Turnaround Time = 9.75
		Average Response Time = 1.25

	----------------------------------------------------------------------------------------------------------------------------------------------------------	
	----------------------------------------------------------------------------------------------------------------------------------------------------------
	
	
	TEST CASE 2:
	
			
		Enter number of processes :4
		
		
		Enter details for process 1
		        1. PID :1
		        2. Enter Arrival Time :0
		        3. Enter Burst Time :8
		
		
		Enter details for process 2
		        1. PID :2
		        2. Enter Arrival Time :0
		        3. Enter Burst Time :4
		
		
		Enter details for process 3
		        1. PID :3
		        2. Enter Arrival Time :0
		        3. Enter Burst Time :6
		
		
		Enter details for process 4
		        1. PID :4
		        2. Enter Arrival Time :0
		        3. Enter Burst Time :2
		
		
		  ====================================================================================================
		        PID   Arrival Time     Burst Time   Waiting Time     Turnaround Time       Response Time
		    ------------------------------------------------------------------------------------------------
		       4           0              2              0                   2                   0
		       2           0              4              2                   6                   2
		       3           0              6              6                  12                   6
		       1           0              8             12                  20                  12
		  ====================================================================================================
		
		
		GANTT CHART :
		
		------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------
		| 4  |  | 4  |  | 2  |  | 2  |  | 2  |  | 2  |  | 3  |  | 3  |  | 3  |  | 3  |  | 3  |  | 3  |  | 1  |  | 1  |  | 1  |  | 1  |  | 1  |  | 1  |  | 1  |  | 1  |
		------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------
		0    1  1    2  2    3  3    4  4    5  5    6  6    7  7    8  8    9  9   10 10   11 11   12 12   13 13   14 14   15 15   16 16   17 17   18 18   19 19   20
		
		
		 ( start : 0 ) ------ P4 ------ (complete : 2) ====> ( start : 2 ) ------ P2 ------ (complete : 6) ====> ( start : 6 ) ------ P3 ------ (complete : 12) ====> 
		 ( start : 12 ) ------ P1 ------ (complete : 20) ====>ALL PROCESS EXECUTED
		
		
		Average Waiting Time = 5
		Average Turnaround Time = 10
		Average Response Time = 5
			
	  ----------------------------------------------------------------------------------------------------------------------------------------------------------	
	  ----------------------------------------------------------------------------------------------------------------------------------------------------------
	
		TEST CASE 3 :
			
				
		Enter number of processes :5
		
		
		Enter details for process 1
		        1. PID :1
		        2. Enter Arrival Time :1
		        3. Enter Burst Time :2
		
		
		Enter details for process 2
		        1. PID :2
		        2. Enter Arrival Time :5
		        3. Enter Burst Time :4
		
		
		Enter details for process 3
		        1. PID :3
		        2. Enter Arrival Time :6
		        3. Enter Burst Time :2
		
		
		Enter details for process 4
		        1. PID :4
		        2. Enter Arrival Time :9
		        3. Enter Burst Time :5
		
		
		Enter details for process 5
		        1. PID :5
		        2. Enter Arrival Time :4
		        3. Enter Burst Time :8
		
		
		  ====================================================================================================
		        PID   Arrival Time     Burst Time   Waiting Time     Turnaround Time       Response Time
		    ------------------------------------------------------------------------------------------------
		       1           1              2              0                   2                   0
		       3           6              2              0                   2                   0
		       2           5              4              2                   6                   0
		       4           9              5              2                   7                   2
		       5           4              8             11                  19                   0
		  ====================================================================================================
		
		
		GANTT CHART :
		
		------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------
		| 1  |  | 1  |  | 5  |  | 2  |  | 3  |  | 3  |  | 2  |  | 2  |  | 2  |  | 4  |  | 4  |  | 4  |  | 4  |  | 4  |  | 5  |  | 5  |  | 5  |  | 5  |  | 5  |  | 5  |  | 5  |
		------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------  ------
		1    2  2    3  4    5  5    6  6    7  7    8  8    9  9   10 10   11 11   12 12   13 13   14 14   15 15   16 16   17 17   18 18   19 19   20 20   21 21   22 22   23
		
		
		 ( start : 1 ) ------ P1 ------ (complete : 3) ====> ( start : 4 ) ------ P5 ------ (complete : 5) ====> ( start : 5 ) ------ P2 ------ (complete : 6) ====> 
		 ( start : 6 ) ------ P3 ------ (complete : 8) ====> ( start : 8 ) ------ P2 ------ (complete : 11) ====> ( start : 11 ) ------ P4 ------ (complete : 16) ====> 
		 ( start : 16 ) ------ P5 ------ (complete : 23) ====>ALL PROCESS EXECUTED
		
		
		Average Waiting Time = 3
		Average Turnaround Time = 7.2
		Average Response Time = 0.4
		


		
*/

