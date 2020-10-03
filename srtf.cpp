#include<iostream>
#include<conio.h>
using namespace std;

struct Process{
	
	int pid;
	int arr_t;
	int burst_t;
	int remainBurst_t;
	
	int response_t;
	int wait_t;
	int turnaround_t;
	
	int start_t;
	int completion_t;
};

class Schedulling{
	
    float totalTAT, totalWT, totalRT, avgTAT, avgWT, avgRT;
	int num, f, count;
	int gantt_p[50], gantt_t[50];
	public:
		Process *process;
		void getdata();
		void fcfs();
		void sjfs();
		void srtf();
		int getcount();
		int getnum();
		void showdata();
		void showsrtf();
		void sort_arrt();
		void sort_burst(int start, int end);
		void sort_rem_burst(int start, int end); 
};

void Schedulling::getdata(){
	
	cout<<"Enter number of processes: ";
	cin>>num;
	process = new Process[num];
	count = 0;
		cout<<"\nEnter pids of all processes: ";
		for(int j=1; j<=num; j++){
			cout<<"\nProcess "<<j<<": ";
			cin>>process[j-1].pid;
		}

		cout<<"\nEnter arrival time of all processes: ";
		for(int j=1; j<=num; j++){
			cout<<"\nProcess "<<j<<": ";
			cin>>process[j-1].arr_t;
			if(process[j-1].arr_t==0)
				count++;
		}		

		cout<<"\nEnter burst time of all processes: ";
		for(int j=1; j<=num; j++){
			cout<<"\nProcess "<<j<<": ";
			cin>>process[j-1].burst_t;
			process[j-1].remainBurst_t = process[j-1].burst_t;
		}

}

int Schedulling::getcount(){
	return count;
}

int Schedulling::getnum(){
	return num;
}

void Schedulling::sort_arrt(){
	
	for(int i=1,j; i<num; i++){
		//Process *temp;
		//int x = 0;
		int temp = process[i].arr_t;
		int temp1 = process[i].pid;
		int temp2 = process[i].burst_t;

		for(j=i; j>0 && temp<process[j-1].arr_t; --j){
			process[j].arr_t = process[j-1].arr_t;
			process[j].pid = process[j-1].pid;
			process[j].burst_t = process[j-1].burst_t;
		}
		
		process[j].arr_t = temp;	
		process[j].pid = temp1;
		process[j].burst_t = temp2;
	}
	
}

void Schedulling::sort_rem_burst(int start, int end){
	
	for(int i=start+1,j; i<end; i++){
		int temp = process[i].arr_t;
		int temp1 = process[i].pid;
		int temp2 = process[i].remainBurst_t;
		int temp3 = process[i].burst_t;

		for(j=i; j>start && temp2<process[j-1].remainBurst_t; --j){
			process[j].arr_t = process[j-1].arr_t;
			process[j].pid = process[j-1].pid;
			process[j].remainBurst_t = process[j-1].remainBurst_t;
			process[j].burst_t = process[j-1].burst_t;
		}
		
		process[j].arr_t = temp;	
		process[j].pid = temp1;
		process[j].remainBurst_t = temp2;
		process[j].burst_t = temp3;
	}
	
}

void Schedulling::sort_burst(int start, int end){
	
	for(int i=start+1,j; i<end; i++){
		int temp = process[i].arr_t;
		int temp1 = process[i].pid;
		int temp2 = process[i].burst_t;

		for(j=i; j>start && temp2<process[j-1].burst_t; --j){
			process[j].arr_t = process[j-1].arr_t;
			process[j].pid = process[j-1].pid;
			process[j].burst_t = process[j-1].burst_t;
		}
		
		process[j].arr_t = temp;	
		process[j].pid = temp1;
		process[j].burst_t = temp2;
	}
	
}

void Schedulling::fcfs(){
	
	for(int i=0; i<num; i++){
		
		if(i==0){ //for initial process wait time is always 0
			process[i].wait_t = 0;
		}
		else{
			//x contains total time process[i] waits from very start to the finished execution of last process
			int x = (process[i-1].arr_t + process[i-1].turnaround_t);
			
			/*checks if last process completed execution and process[i] didn't even arrive, then
			  what will be the waiting time of current process[i]
			  for eg: if last process finished execution at time unit 3 and next process arrived at 
			  time unit 4, then processor is ideal for 1 time unit, therefore the wait time for 
			  current process will be taken from 4 and hence will be 0 as it will start executing
			  as soon as it arrives, since processor is idle !*/
			if((x - process[i].arr_t) >= 0) 
				process[i].wait_t = x - process[i].arr_t;
			else
				process[i].wait_t = 0;
		}
		process[i].turnaround_t = process[i].wait_t + process[i].burst_t;
		
		process[i].response_t = process[i].wait_t;
	}
	
	totalTAT = 0.0;
	totalWT = 0.0;
	totalRT = 0.0;
	avgTAT = 0.0;
	avgWT = 0.0;
	avgRT = 0.0;
	
	for(int i=0; i<num; i++){
		
		totalTAT += process[i].turnaround_t;
		totalWT += process[i].wait_t;
		totalRT += process[i].response_t;
	}
	avgTAT = totalTAT/num;
	avgWT = totalWT/num;
	avgRT = totalRT/num;
}

void Schedulling::sjfs(){
	
	
	for(int i=0; i<num; i++){
		int current;
		
		if(i<num-1){
			
			if(i==0)
			current = 0;
			else
			current = (process[i-1].arr_t + process[i-1].turnaround_t);
			
			int j=i;
			while(j<num){
				
				if(current < process[j].arr_t) 
					break;
				j++;
			}
			sort_burst(i, j);
			
		
			if(current >= process[i].arr_t) 
				process[i].wait_t = current - process[i].arr_t;
			else
				process[i].wait_t = 0;
		}
		else{
			int current = (process[i-1].arr_t + process[i-1].turnaround_t);
			
			if(current >= process[i].arr_t) 
				process[i].wait_t = current - process[i].arr_t;
			else
				process[i].wait_t = 0;
		}
		process[i].turnaround_t = process[i].wait_t + process[i].burst_t;
		
		process[i].response_t = process[i].wait_t;
	}
	
	totalTAT = 0.0;
	totalWT = 0.0;
	totalRT = 0.0;
	avgTAT = 0.0;
	avgWT = 0.0;
	avgRT = 0.0;
	
	for(int i=0; i<num; i++){
		
		totalTAT += process[i].turnaround_t;
		totalWT += process[i].wait_t;
		totalRT += process[i].response_t;
	}
	avgTAT = totalTAT/num;
	avgWT = totalWT/num;
	avgRT = totalRT/num;
}

void Schedulling::srtf(){
	
	int current = 0;
	f=0;
	gantt_t[f] = 0;
	gantt_p[f] = process[0].pid;
	for(int i=0; i<num; i++){
			
		while(process[i].remainBurst_t!=0){
		
			int j=i;
			while(j<num){
				
				if(current < process[j].arr_t) 
					break;
				j++;
			}
			sort_rem_burst(i, j);
		
			if(current<process[i].arr_t)
				current=process[i].arr_t;
		
			if(process[i].remainBurst_t==process[i].burst_t){
				//process[i].response_t = current;
				process[i].start_t = process[i].arr_t;
				gantt_t[f] = current;
				gantt_p[f] = process[i].pid;
				f++;
			}
			
			current++;
			
			process[i].remainBurst_t -= 1;
			
		}
		if(process[i].remainBurst_t==0){
			
			if(i==num-2){
				gantt_t[f] = current;
				f++;
			}
			if(i==num-1){
				gantt_p[f-1] = process[i].pid;
			}
	
			process[i].completion_t = current;
			process[i].turnaround_t = process[i].completion_t - process[i].start_t;
			process[i].wait_t = process[i].turnaround_t - process[i].burst_t;
			process[i].response_t = process[i].wait_t;
		}
	}
	
	totalTAT = 0.0;
	totalWT = 0.0;
	totalRT = 0.0;
	avgTAT = 0.0;
	avgWT = 0.0;
	avgRT = 0.0;
	
	for(int i=0; i<num; i++){
		
		totalTAT += process[i].turnaround_t;
		totalWT += process[i].wait_t;
		totalRT += process[i].response_t;
	}
	avgTAT = totalTAT/num;
	avgWT = totalWT/num;
	avgRT = totalRT/num;
}

void Schedulling::showdata(){
	
	cout<<"===========================================================================================================================\n";
	cout<<"\n\tProcess ID \t ArrTime \t BurstTime \t WaitTime \t TurnATime \t ResponseTime\n";
	cout<<"---------------------------------------------------------------------------------------------------------------------------\n";
	for(int i=0; i<num; i++){
		cout<<"\n\t  "<<process[i].pid<<"\t \t "<<process[i].arr_t<<"\t \t "
		<<process[i].burst_t<<"\t \t "<<process[i].wait_t<<"\t \t "<<process[i].turnaround_t
		<<"\t \t "<<process[i].response_t;
	}
	cout<<endl;
	cout<<"============================================================================================================================\n";
	cout<<"\nAverage Waiting time: "<<avgWT;
	cout<<"\nAverage Turnaround time: "<<avgTAT;
	cout<<"\nAverage Response time: "<<avgRT;
	cout<<endl<<endl;
	
	for(int i=0; i<num; i++){
		
		if(i==0 || process[i].arr_t > process[i-1].completion_t){
			process[i].start_t = process[i].arr_t;
			process[i].completion_t = process[i].arr_t + process[i].burst_t;
		}
		else{
			process[i].start_t = process[i-1].completion_t;
			process[i].completion_t = process[i].start_t + process[i].burst_t;
		}
	}
	
	cout<<"------------GANTT CHART------------\n\n";
	
	for(int i=0; i<num; i++){
		
		cout<<"|---------|  ";
	}
	cout<<endl;
	for(int i=0; i<num; i++){
		
		cout<<"|         |  ";
	}
	cout<<endl;
	for(int i=0; i<num; i++){
		
		cout<<"|   P"<<process[i].pid<<"    |  ";
	}
	cout<<endl;
	for(int i=0; i<num; i++){
		
		cout<<"|---------|  ";
	}
	cout<<endl;
	for(int i=0; i<num; i++){
		if(process[i].start_t<10 && process[i].completion_t<10)
		    cout<<process[i].start_t<<"         "<<process[i].completion_t<<"  ";
		else
		    cout<<process[i].start_t<<"        "<<process[i].completion_t<<" ";
	}
	cout<<endl;
	
}

void Schedulling::showsrtf(){
	
	cout<<"===========================================================================================================================\n";
	cout<<"\n\tProcess ID \t ArrTime \t BurstTime \t WaitTime \t TurnATime \t ResponseTime\n";
	cout<<"---------------------------------------------------------------------------------------------------------------------------\n";
	for(int i=0; i<num; i++){
		cout<<"\n\t  "<<process[i].pid<<"\t \t "<<process[i].arr_t<<"\t \t "
		<<process[i].burst_t<<"\t \t "<<process[i].wait_t<<"\t \t "<<process[i].turnaround_t
		<<"\t \t "<<process[i].response_t;
	}
	cout<<endl;
	cout<<"============================================================================================================================\n";
	cout<<"\nAverage Waiting time: "<<avgWT;
	cout<<"\nAverage Turnaround time: "<<avgTAT;
	cout<<"\nAverage Response time: "<<avgRT;
	cout<<endl<<endl;
	
	int total = 0;
	for(int m=0; m<num; m++){
		total+=process[m].burst_t;
	}
	
	cout<<"------------GANTT CHART------------\n\n";

	gantt_t[f] = total;
	
	for(int i=0; i<f; i++){
		
		cout<<"|---------|  ";
	}
	cout<<endl;
	for(int i=0; i<f; i++){
		
		cout<<"|         |  ";
	}
	cout<<endl;
	for(int i=0; i<f; i++){
		
		cout<<"|   P"<<gantt_p[i]<<"    |  ";
	}
	cout<<endl;
	for(int i=0; i<f; i++){
		
		cout<<"|---------|  ";
	}
	cout<<endl;
	for(int i=0; i<f; i++){
		if(gantt_t[i]<10)
		    cout<<gantt_t[i]<<"         "<<gantt_t[i+1]<<"  ";
		else
		    cout<<gantt_t[i]<<"        "<<gantt_t[i+1]<<" ";
	}
	cout<<endl;
}

int main(){
	
	Schedulling s1;
	s1.getdata();
	int choice;
	cout<<"Enter your choice of Schedulling Algo:"
		  "\n1.FCFS"
		  "\n2.SJFS"
		  "\n3.SRTF\n";
	cin>>choice;
	switch(choice){
		case 1:{
			s1.sort_arrt();
			s1.fcfs();
			s1.showdata();
			break;
		}
		case 2:{
			s1.sort_arrt();
			s1.sjfs();
			s1.showdata();
			break;
		}
		case 3:{
			s1.sort_arrt();
			if(s1.getcount()==s1.getnum()){
				s1.sjfs();
				s1.showdata();
			}
			else{
				s1.srtf();
				s1.showsrtf();
			}
			break;
		}
		default: cout<<"Invalid choice!!";
		break;
	}
	
	getch();
	return 0;
}
