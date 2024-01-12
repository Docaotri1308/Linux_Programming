#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    char *data = mmap(0, 1, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (data == MAP_FAILED)
    {
       printf(" Do mmap process memory is failed\n");
    }

    *data = 64;

    pid_t process_pid = fork();
    
    if (process_pid >= 0) {
        if (process_pid == 0) {
            printf("This is child process, my PID is: %d\n", getpid());
            printf("Value in child process = %c\n", ++(*data));
            if (munmap(data, sizeof(data)) == -1)
            {
               printf("munmap is failed !\n");
            }
            exit(0);
        } else {
            wait(NULL);
            
            printf("\nThis is parent process, my PID is: %d\n", getpid());
            printf("Value in parent process = %c\n", ++(*data));
            if (munmap(data, sizeof(data)) == -1)
            {
                printf("munmap is failed !\n");
            }
            exit(0);
        }
    } else {
        printf("fork() unsuccessfully\n");
    }

    return 0;
}