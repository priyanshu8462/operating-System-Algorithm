//PROGRAM TO IMPLEMENT FIRST-COME-FIRST-SERVE SCHEDULING ALGORITHM
#include<iostream>
#include<conio.h>
#include<string.h>
using namespace std;

struct ProcessDetail{
	string process_name;
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
	double total_wait_time, total_turnaround_time, average_wait_time, average_turnaround_time ;
	int number_of_process;
	ProcessDetail * process;
	public:
		SchedulingAlgorithm(){
			total_wait_time=0;
			total_turnaround_time=0; 
			average_wait_time=0; 
			average_turnaround_time = 0;
		}
		void input();
		void FCFS();
		void output();
		void sort_arrival_time();	
		string to_string(int x){
			return "P" + (x+1);
		}	
};

void SchedulingAlgorithm::input(){
	cout<<"\nEnter number of processes :";
	cin>>number_of_process;
	process = new ProcessDetail[number_of_process];
	
	//enter detail for each process
	for(int i=0;i<number_of_process;i++){
		cout<<"\n\nEnter details for process "<<i+1;
		process[i].process_name = to_string(i);
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
		process[0].complete_time = process[0].burst_time;
		 
		//calculate wait time for each process
		process[0].wait_time = 0;
		for(int i=1;i<number_of_process;i++){
			process[i].wait_time = process[i-1].arrival_time + process[i-1].wait_time + process[i-1].burst_time - process[i].arrival_time ;
			if(process[i].wait_time<0)
				process[i].wait_time=0;
		//for visual representation
			process[i].start_time = process[i-1].arrival_time + process[i-1].wait_time + process[i-1].burst_time;
			process[i].complete_time = process[i-1].arrival_time + process[i-1].wait_time + process[i-1].burst_time + process[i].burst_time; 		
		}
		
		//total wait time
		for(int i=0;i<number_of_process;i++){
			total_wait_time += process[i].wait_time; 
		}
		
		//average wait time
		average_wait_time = total_wait_time/number_of_process;
		
		//calculate turnaround time for each process
		process[0].turnaround_time = process[0].burst_time;
		for(int i=1;i<number_of_process;i++){
		process[i].turnaround_time = process[i-1].arrival_time + process[i-1].wait_time + process[i-1].burst_time + process[i].burst_time - process[i].arrival_time ;	
		}
		
		//total wait time
		for(int i=0;i<number_of_process;i++){
			total_turnaround_time += process[i].turnaround_time; 
		}
		
		//average wait time
		average_turnaround_time = total_turnaround_time/number_of_process;
	}



//show output
void SchedulingAlgorithm::output(){
	//Tabular Output
	cout<<"\n\n  =================================================================";
		cout<<"\n   "<<"   PID"<<"   ArrivalTime"<<"   BurstTime"<<"   Wait time"<<"   Turnaround time";
		cout<<"\n   ---------------------------------------------------------------";
	for(int i=0;i<number_of_process;i++){
		cout<<"\n   "<<"    "<<process[i].pid<<"        "<<process[i].arrival_time<<"             "<<process[i].burst_time<<"             "<<process[i].wait_time<<"           "<<process[i].turnaround_time;
	
	}
	cout<<"\n  =================================================================";
	
	
	cout<<"\n\n\nGANTT CHART :\n";
	//Gantt Chart
		cout<<endl;
		for(int k=0;k<number_of_process;k++){
			cout<<"----------  ";	
		}
		cout<<endl;
		for(int k=0;k<number_of_process;k++){
			cout<<"|         |  ";	
		}
		cout<<endl;
		for(int k=0;k<number_of_process;k++){
			cout<<"|    P"<<process[k].pid<<"   |  ";	
		}
		cout<<endl;
		for(int k=0;k<number_of_process;k++){
			cout<<"|         |  ";	
		}
		cout<<endl;
		for(int k=0;k<number_of_process;k++){
			cout<<"----------  ";	
		}
		cout<<endl;
		for(int k=0;k<number_of_process;k++){
			cout<<process[k].start_time<<"         "<<process[k].complete_time;	
		}
		
	
	
	//Analysis
	cout<<"\n\nTotal Wait Time :"<<total_wait_time;
	cout<<"\nAverage Wait Time :"<<average_wait_time;
	cout<<"\n\nTotal Turnaround Time :"<<total_turnaround_time;
	cout<<"\nAverage Turnaround Time :"<<average_turnaround_time;
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
