#include<iostream>
#include<fcntl.h>
#include<unistd.h>
using namespace std;

int main(int argc, char *argv[]){
	int fd_read,fd_write,x;
	char buffer[100];
	if(argc!=3){
		cout<<"\nWrong Number of Command Line Arguments !!";
		return 0;
	}
	
	fd_read = open(argv[1], O_RDONLY);
	fd_write = opwen(argv[2], O_CREAT | O_WRONLY |);
	if(fd_read<0){
		cout<<"\nError in reading file";
		return 0;
	}
	
	if(fd_write == -1){
		cout<<"\nError in Destination file";
	}
	x=read(fd_read, buffer,sizeof(char));
	while(x>0){
		int x = write(fd_write, buffer , x);
		if(x<0){
			cout<<"\nERROR WHILE WRITING ";
		}
		x=read(fd_read, buffer,sizeof(char));
	}
	
	if(x<0){
		cout<<"\nEnd of file is reached OR error while reading file";
	}
	
	close(fd_read);
	close(fd_write);
	
	cout<<"\nDATA COPIED SUCCESSFULLY";
	x=read(fd_read, buffer,sizeof(char));
	while(x>0){
		cout<<buffer;
	}
	
	cout<<endl;
	close{fd_write};
	return 0;
	
}
