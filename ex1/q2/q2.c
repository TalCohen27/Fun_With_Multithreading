#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>  
#include <fcntl.h>
#include <unistd.h>  
#include <math.h>
#include <string.h>
#include <sys/stat.h> 
#include <sys/wait.h>

#define NUM_CHILDREN 2

void do_son(int i, FILE *fp, int p[2]);

int main()
{
	int pid, waitStat, i, fd, p[2];
	FILE *fp;

	printf("Ex#1, Q2, Tal Cohen, id 302529672\n");
	close(0);
	fd = open("info.txt", O_RDONLY);
	if (fd <0) 
	{
		fprintf(stderr, "ERROR: open \"%s\" failed (%d). Exiting\n", "info.txt", fd);
		exit(2);
	}
    fp = fdopen(fd, "r"); 
    pipe(p);

	for(i = 0; i < NUM_CHILDREN; i++)
	{
		pid = fork();
		if(pid == 0)
		{
			do_son(i, fp, p);
		}
		else if(pid > 0)
		{
			printf("created child process %d\n", pid);
		}
		else
		{
			printf("fork error\n");
		}
	}

	close(p[0]);
    close(p[1]);

    for(i = 0; i < NUM_CHILDREN; i++)
    {
    	wait(&waitStat);
    }

return 0;

}

//The two children write and read to and 
//from the pipe
void do_son(int i, FILE *fp, int p[2])
{
	size_t size = 0;
	char *currLine = NULL;
	FILE *pr, *pw;

    pw = fdopen(p[1], "w");
    pr = fdopen(p[0], "r");

    if(i == 0)
    {
    	fclose(pr);
		while(getline(&currLine, &size, fp) > -1)
			fprintf(pw, "%d %s", getpid(), currLine);

		fclose(pw);
			
	}
	else if(i == 1)
	{
		fclose(pw);
		while(getline(&currLine, &size, pr) > -1)
		{
			if(currLine[strlen(currLine) - 1] == '\n')
				currLine[strlen(currLine) - 1] = '\0';
			printf("%s %d\n", currLine, getpid());
		}

		fclose(pr);		
	}

	fclose(fp);
	free(currLine);

	exit(1);
}
