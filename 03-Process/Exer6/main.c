#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    pid_t process_pid = fork();
    int status, rv;
    
    if (process_pid >= 0) {
        if (process_pid == 0) {
            printf("This is the Process_B --- child process, my PID is: %d\n", getpid());
            // while(1);
            sleep(5);
            exit(0);
        }
        else {
            rv = waitpid(process_pid, &status, 0);
            if (rv == -1) {
                printf("waitpid() unsuccessful\n");
            }

            printf("\nThis is Process_A --- parent process, PID child process: %d\n", rv);

            if (WIFEXITED(status)) {
                printf("Normally termination, status = %d\n", WEXITSTATUS(status));
            }
            else if (WIFSIGNALED(status)) {
                printf("Killed by signal, value = %d\n", WTERMSIG(status));
            }
            else if (WIFSTOPPED(status)) {
                printf("Stopped by signal, value = %d\n", WSTOPSIG(status));
            }
        }
    }
    else {
        printf("fork() unsuccessfully\n");
    }
    return 0;
}