#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_FILE_1 "./file1"
#define FIFO_FILE_2 "./file2"

char receive_buff[256];
char send_buff[256];

int main(int argc, char const *argv[]) {
    int fd1, fd2;

    mkfifo(FIFO_FILE_1, 0666);
    mkfifo(FIFO_FILE_2, 0666);

    while(1) {
        fd2 = open(FIFO_FILE_2, O_RDONLY);                      // FIFO 2 use to read in process
        read(fd2, receive_buff, 256);
        printf("\nMessage from process_B: %s", receive_buff);

        fd1 = open(FIFO_FILE_1, O_WRONLY);                      // FIFO 1 use to write in process
        printf("\nMessage to process_B: ");
        fgets(send_buff, 256, stdin);
        write(fd1, send_buff, 256);
    }

    close(fd1);
    close(fd2);

    return 0;
}