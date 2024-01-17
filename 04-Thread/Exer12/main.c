#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_t thread_id1, thread_id2, thread_id3;
int cond_var = 1;
int fd;

typedef struct {
    char Name[20];
    char PhoneNum[20];
    char Home[20];
} Human;

static void *threadHandle_1(void *args) {
    while(1) {
        pthread_mutex_lock(&mutex);

        while(cond_var != 1) {
            pthread_cond_wait(&cond, &mutex);
        }

        pthread_t tid = pthread_self();
        Human *info = (Human*)args;

        printf("This is thread 1, ---> tid1: %ld\n", tid);

        printf("Name: ");
        fgets(info->Name, sizeof(info->Name), stdin);
        info->Name[strcspn(info->Name, "\n")] = '\0';

        printf("Phone: ");
        fgets(info->PhoneNum, sizeof(info->PhoneNum), stdin);
        info->PhoneNum[strcspn(info->PhoneNum, "\n")] = '\0';

        printf("Home: ");
        fgets(info->Home, sizeof(info->Home), stdin);
        info->Home[strcspn(info->Home, "\n")] = '\0';

        cond_var = 2;
        
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }
}

static void *threadHandle_2(void *args) {
    while(1) {
        pthread_mutex_lock(&mutex);

        while(cond_var != 2) {
            pthread_cond_wait(&cond, &mutex);
        }

        pthread_t tid = pthread_self();
        Human *info = (Human*)args;
        char buff[100];

        printf("This is thread 2, ---> tid2: %ld\n", tid);

        sprintf(buff, "Name - Phone - Home: %s - %s - %s \n", info->Name, info->PhoneNum, info->Home);
        write(fd, buff, strlen(buff));

        cond_var = 3;

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }
}

static void *threadHandle_3(void *args) {
    while(1) {
        pthread_mutex_lock(&mutex);

        while(cond_var != 3) {
            pthread_cond_wait(&cond, &mutex);
        }

        pthread_t tid = pthread_self();
        Human *info = (Human*)args;
        char buff[100];

        printf("This is thread 3, ---> tid3: %ld\n", tid);

        sprintf(buff, "Name - Phone - Home: %s - %s - %s \n", info->Name, info->PhoneNum, info->Home);
        printf("%s", buff);

        cond_var = 1;

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }
}

int main() {
    while(1) {
        Human person;
        int ret;

        fd = open("Infor_Student.txt", O_RDWR | O_APPEND | O_CREAT, 0777);
        if (fd == -1) {
            printf("open() file Infor_Student.txt failed\n");
        }

        if (ret = pthread_create(&thread_id1, NULL, &threadHandle_1, &person)) {
            printf("Thread 1 create error number = %d\n", ret);
            return -1;
        }

        if (ret = pthread_create(&thread_id2, NULL, &threadHandle_2, &person)) {
            printf("Thread 1 create error number = %d\n", ret);
            return -1;
        }

        if (ret = pthread_create(&thread_id3, NULL, &threadHandle_3, &person)) {
            printf("Thread 1 create error number = %d\n", ret);
            return -1;
        }

        pthread_join(thread_id1, NULL);
        pthread_join(thread_id2, NULL);
        pthread_join(thread_id3, NULL);
    }

    close(fd);

    return 0;
}