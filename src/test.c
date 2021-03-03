// CPP program to illustrate dup2()
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>

int main()
{
	int file_desc = open("tricky.txt",O_WRONLY | O_CREAT);

	// here the newfd is the file descriptor of stdout (i.e. 1)
	dup2(file_desc, 1) ;

	// All the printf statements will be written in the file
	// "tricky.txt"
	printf("lalala\n");

return 0;
}
