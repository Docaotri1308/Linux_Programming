#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    pid_t process_pid = fork();

    if (process_pid >= 0) {
        if (process_pid == 0) {
            printf("This is Process_B --- child process \n");
            printf("My PID is %d, my parent PID is: %d\n", getpid(), getppid());
        }
        else {
            printf("This is Process_A --- parent process \n");
            printf("My PID is: %d\n", getpid());
        }
    }
    else {
        printf("Function fork() unsuccessfully\n");
    }
    return 0;
}
