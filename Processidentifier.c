#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main() 
{
    pid_t pid;  // Process ID type
    // Create a new process
    pid = fork();
    if (pid < 0) 
	{ // fork() failed
        fprintf(stderr, "Fork Failed");
        return 1;
    } 
	else if (pid == 0) 
	{// Child process
        printf("Child Process:\n");
        printf("PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
    } 
	else 
	{// Parent process
        printf("Parent Process:\n");
        printf("PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
    }
    return 0;
}

