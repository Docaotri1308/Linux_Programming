#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

int main()
{
    clock_t start_time = clock();

    int fd;
    char buff[18] = "Hello Mr.Phong !\n";
    
    fd = open("Text_single_thread.txt", O_RDWR | O_APPEND | O_CREAT, 0777);
    if (fd == -1) {
        printf("open() file Text_single_thread.txt failed\n");
    }

    for (int i = 0; i < 1000; i++) {
        write(fd, buff, strlen(buff));
    }

    clock_t end_time = clock();
    printf("Time used in single_thread: %f\n", (double)(end_time - start_time)/CLOCKS_PER_SEC);

    close(fd);

    return 0;
}