#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

char receive_buff[256];
char send_buff[256];

static void func(int signum) {
    wait(NULL);
    printf("Child process termination\n");
}

int main(int argc, char const *argv[]) {
    int rd = 0;
    int fds1[2];
    int fds2[2];

    /*
    | ---------------- |
    | pipe1:           |
    | - parent: writer |
    | - child : reader |
    |                  |
    | pipe2:           |
    | - parent: reader |
    | - child : writer |
    | ---------------- |
    */

    if (pipe(fds1) < 0) {
        printf("pipe1() unsuccessfully\n");
        exit(1);
    }
    if (pipe(fds2) < 0) {
        printf("pipe2() unsuccessfully\n");
        exit(1);
    }

    pid_t process_pid = fork();

    if (process_pid >= 0) {
        if (process_pid == 0) {
            printf("\nThis is Child process, my PID: %d\n", getpid());

            if (close(fds1[1]) == -1) {
                printf("close(fds1[1]) failed\n");
            }
            if (close(fds2[0]) == -1) {
                printf("close(fds2[0]) failed\n");
            }

            while(1) {
                rd = read(fds1[0], receive_buff, 256);
                if (rd == -1) {
                    printf("read() failed\n");
                    exit(0);
                } 
                else if (rd == 0) {                           // All write is closed, block the write end of the pipe
                    printf("Pipe end-of-pipe\n");
                    break;
                } 
                else {
                    printf("\nMessage from Parent process: %s", receive_buff);
                }
                
                printf("\nMessage to Parent process: ");
                fgets(send_buff, 256, stdin);
                write(fds2[1], send_buff, 256);
            }
        } 
        else {
            sleep(1);
            
            // Prevent zombie process
            signal(SIGCHLD, func);

            printf("\nThis is Parent process, my PID: %d\n", getpid());

            if (close(fds1[0]) == -1) {
                printf("close(fds1[0]) failed\n");
            }
            if (close(fds2[1]) == -1) {
                printf("close(fds2[1]) failed\n");
            }

            while(1) {
                printf("\nMessage to Child process: ");
                fgets(send_buff, 256, stdin);
                write(fds1[1], send_buff, 256);

                rd = read(fds2[0], receive_buff, 256);
                if (rd == -1) {
                    printf("read() failed\n");
                    exit(0);
                } 
                else if (rd == 0) {                           // All write is closed, block the write end of the pipe
                    printf("Pipe end-of-pipe\n");
                    break;
                } 
                else {
                    printf("\nMessage from Parent process: %s", receive_buff);
                }
            }
        }
    } 
    else {
        printf("fork() failed\n");
    }
    
    return 0;
}