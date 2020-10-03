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
	int number_of_process, current_time;
	ProcessDetail * process;
	public:
		SchedulingAlgorithm(){
			total_wait_time=0;
			total_turnaround_time=0; 
			average_wait_time=0; 
			average_turnaround_time = 0;
			total_response_time=0; 
			average_response_time = 0;
			 current_time=0;

		}
		void input();
		void SRTF();
		void output();
		void sort_arrival_time();
		void assign_queue();
		void sort_burst_time(int start,int end);	
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

//function to apply sorting based on burst time
void SchedulingAlgorithm::assign_queue(){
	int i=0;
	int t=0;
	for(t=0;t<number_of_process;t++){
		i=t;
		while(process[i].arrival_time <= current_time && i<number_of_process){
			i++;
		}
		if((i-t)>1)
			sort_burst_time(t, i);
			
		current_time = current_time+process[t].burst_time;
	}
}
		
//srtf implementation
void SchedulingAlgorithm::SRTF(){
	
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



//output
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
	obj.assign_queue();
	obj.SRTF();
	obj.output();
	getch();
	return 0;
}


/*
			OUTPUT
		==============
		
	TEST CASE 1 :

Enter number of processes :6


Enter details for process 1
        1. PID :1
        2. Enter Arrival Time :2
        3. Enter Burst Time :5


Enter details for process 2
        1. PID :2
        2. Enter Arrival Time :4
        3. Enter Burst Time :2


Enter details for process 3
        1. PID :3
        2. Enter Arrival Time :6
        3. Enter Burst Time :1


Enter details for process 4
        1. PID :4
        2. Enter Arrival Time :12
        3. Enter Burst Time :5


Enter details for process 5
        1. PID :5
        2. Enter Arrival Time :13
        3. Enter Burst Time :4


Enter details for process 6
        1. PID :6
        2. Enter Arrival Time :0
        3. Enter Burst Time :6


  =====================================================================================
      PID   ArrivalTime   BurstTime   Wait time   Turnaround time     Response Time
   -----------------------------------------------------------------------------------
       6        0             6           0             6                 0
       3        6             1           0             1                 0
       2        4             2           3             5                 3
       1        2             5           7            12                 7
       5       13             4           1             5                 1
       4       12             5           6            11                 6
  =====================================================================================


GANTT CHART :

------------  ------------  ------------  ------------  ------------  ------------
|          |  |          |  |          |  |          |  |          |  |          |
|    6     |  |    3     |  |    2     |  |    1     |  |    5     |  |    4     |
|          |  |          |  |          |  |          |  |          |  |          |
------------  ------------  ------------  ------------  ------------  ------------
0          6  6          7  7          9  9         14 14         18 18         23

Total Wait Time :17
Average Wait Time :2.83333

Total Turnaround Time :40
Average Turnaround Time :6.66667

Total Response Time :17
Average Response Time :2.83333


------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------

  TEST CASE 2 :


Enter number of processes :4


Enter details for process 1
        1. PID :1
        2. Enter Arrival Time :0
        3. Enter Burst Time :6


Enter details for process 2
        1. PID :2
        2. Enter Arrival Time :0
        3. Enter Burst Time :8


Enter details for process 3
        1. PID :3
        2. Enter Arrival Time :0
        3. Enter Burst Time :7


Enter details for process 4
        1. PID :4
        2. Enter Arrival Time :0
        3. Enter Burst Time :3


  =====================================================================================
      PID   ArrivalTime   BurstTime   Wait time   Turnaround time     Response Time
   -----------------------------------------------------------------------------------
       4        0             3           0             3                 0
       1        0             6           3             9                 3
       3        0             7           9            16                 9
       2        0             8          16            24                16
  =====================================================================================


GANTT CHART :

------------  ------------  ------------  ------------
|          |  |          |  |          |  |          |
|    4     |  |    1     |  |    3     |  |    2     |
|          |  |          |  |          |  |          |
------------  ------------  ------------  ------------
0          3  3          9  9         16 16         24

Total Wait Time :28
Average Wait Time :7

Total Turnaround Time :52
Average Turnaround Time :13

Total Response Time :28
Average Response Time :7


------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------

  TEST CASE 3 :


Enter number of processes :6


Enter details for process 1
        1. PID :1
        2. Enter Arrival Time :2
        3. Enter Burst Time :5


Enter details for process 2
        1. PID :2
        2. Enter Arrival Time :4
        3. Enter Burst Time :2


Enter details for process 3
        1. PID :3
        2. Enter Arrival Time :6
        3. Enter Burst Time :1


Enter details for process 4
        1. PID :4
        2. Enter Arrival Time :12
        3. Enter Burst Time :5


Enter details for process 5
        1. PID :5
        2. Enter Arrival Time :8
        3. Enter Burst Time :4


Enter details for process 6
        1. PID :6
        2. Enter Arrival Time :0
        3. Enter Burst Time :6


  =====================================================================================
      PID   ArrivalTime   BurstTime   Wait time   Turnaround time     Response Time
   -----------------------------------------------------------------------------------
       6        0             6           0             6                 0
       3        6             1           0             1                 0
       2        4             2           3             5                 3
       5        8             4           1             5                 1
       1        2             5          11            16                11
       4       12             5           6            11                 6
  =====================================================================================


GANTT CHART :

------------  ------------  ------------  ------------  ------------  ------------
|          |  |          |  |          |  |          |  |          |  |          |
|    6     |  |    3     |  |    2     |  |    5     |  |    1     |  |    4     |
|          |  |          |  |          |  |          |  |          |  |          |
------------  ------------  ------------  ------------  ------------  ------------
0          6  6          7  7          9  9         13 13         18 18         23

Total Wait Time :21
Average Wait Time :3.5

Total Turnaround Time :44
Average Turnaround Time :7.33333

Total Response Time :21
Average Response Time :3.5  


------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------

  TEST CASE 4 :
	

Enter number of processes :7


Enter details for process 1
        1. PID :1
        2. Enter Arrival Time :3
        3. Enter Burst Time :1


Enter details for process 2
        1. PID :2
        2. Enter Arrival Time :28
        3. Enter Burst Time :3


Enter details for process 3
        1. PID :3
        2. Enter Arrival Time :0
        3. Enter Burst Time :7


Enter details for process 4
        1. PID :4
        2. Enter Arrival Time :0
        3. Enter Burst Time :5


Enter details for process 5
        1. PID :5
        2. Enter Arrival Time :7
        3. Enter Burst Time :2


Enter details for process 6
        1. PID :6
        2. Enter Arrival Time :12
        3. Enter Burst Time :4


Enter details for process 7
        1. PID :7
        2. Enter Arrival Time :1
        3. Enter Burst Time :6


  =====================================================================================
      PID   ArrivalTime   BurstTime   Wait time   Turnaround time     Response Time
   -----------------------------------------------------------------------------------
       4        0             5           0             5                 0
       1        3             1           2             3                 2
       7        1             6           5            11                 5
       5        7             2           5             7                 5
       6       12             4           2             6                 2
       3        0             7          18            25                18
       2       28             3           0             3                 0
  =====================================================================================


GANTT CHART :

------------  ------------  ------------  ------------  ------------  ------------  ------------
|          |  |          |  |          |  |          |  |          |  |          |  |          |
|    4     |  |    1     |  |    7     |  |    5     |  |    6     |  |    3     |  |    2     |
|          |  |          |  |          |  |          |  |          |  |          |  |          |
------------  ------------  ------------  ------------  ------------  ------------  ------------
0          5  5          6  6         12 12         14 14         18 18         25 28         31

Total Wait Time :32
Average Wait Time :4.57143

Total Turnaround Time :60
Average Turnaround Time :8.57143

Total Response Time :32
Average Response Time :4.57143

	
*/				

