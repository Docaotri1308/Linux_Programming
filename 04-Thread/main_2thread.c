#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int fd;
char buff[18] = "Hello Mr.Phong !\n";
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void *thr_handle(void *argv)
{
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < 1000; i++) {
        write(fd, buff, strlen(buff));
    }

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main()
{
    clock_t start_time = clock();

    pthread_t tid;
    int ret;

    fd = open("Text_multi_thread.txt", O_RDWR | O_APPEND | O_CREAT, 0777);
    if (fd == -1) {
        printf("open() file Text_multi_thread.txt failed\n");
    }

    if (ret = pthread_create(&tid, NULL, &thr_handle, NULL)) {
        printf("pthread_create() error number = %d\n", ret);
        return -1;
    }

    pthread_join(tid, NULL);
    
    clock_t end_time = clock();
    printf("Time used in single_thread: %f\n", (double)(end_time - start_time)/CLOCKS_PER_SEC);

    close(fd);
    
    return 0;

}