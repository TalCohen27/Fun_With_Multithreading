
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>  
#include <sys/wait.h>

#define RED 		"\e[0;0;31m"
#define GREEN		"\e[0;0;32m" 
#define YELLOW		"\e[0;0;33m"
#define NO_COLOR 	"\e[0m"

#define NUM_CHILDREN 3
#define DO_SLEEP 1
#define RAND 5

void do_son(int n);

char * names[]={"RED",
 "YELLOW",
 "GREEN"
};

char * codes[]={RED,
 YELLOW,
 GREEN
};

int main()
{
	int i, pid, status;

	printf("Ex#1, Q1, Tal Cohen, id 302529672\n");
	for(i = 0; i < NUM_CHILDREN; i++)
	{
		pid = fork();
		if(pid > 0)
		{
			printf("created a child process pid: %d\n", pid);
	    }
	   	else if(pid == 0)
	    {
	    	do_son(i);
		}
		else
		{
			printf("fork error\n");
		}
	}

	 printf("Parent process created 3 children. Terminating\n");

	  for(i = 0; i < NUM_CHILDREN; i++)
	  {
			pid = wait(&status);
			printf("Child process pid=%d terminated with %d\n", pid, WEXITSTATUS(status));
	  }

	  printf("parent process (pid=%d) exiting...", getpid());

	return 0;
}

void do_son(int n)
{		
	srand(time(NULL) ^ (getpid()<<16));
	int sleep_time = (rand() % RAND) + 1;

	if (DO_SLEEP) sleep(sleep_time); 
	printf("%sprocess %d (pid = %d) sleep-time is: %d seconds\n", codes[n], n, getpid(), sleep_time);
	printf("%s","HELLO\n");
	printf("%s", "FROM\n");
	printf("%s%s\n", names[n], NO_COLOR);

	exit(n*2);
}