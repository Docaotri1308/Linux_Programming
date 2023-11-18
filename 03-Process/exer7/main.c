#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

void func_child(int signum)
{
    printf("This is function to avoid Zombie process\n");
    wait(NULL);
}

int main()
{
    pid_t process_pid = fork();
    if (process_pid >= 0)
    {
        if (process_pid == 0)
        {
            printf("This is Process_B --- child process, my PID is: %d\n", getpid());
        }
        else                    // When a child is terminated, a corresponding SIGCHLD signal is delivered to the parent
        {
            signal(SIGCHLD, func_child);
            printf("This is Process_A --- parent process\n");
            while(1);
        }
    }
    else 
    {
        printf("fork() unsuccessfully\n");
    }
}