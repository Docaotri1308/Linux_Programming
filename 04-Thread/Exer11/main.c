#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

pthread_t thread_id1, thread_id2;

typedef struct {
    char Name[20];
    int BirthDay;
    char PhoneNum[20];
    char Home[20];
} Human;

static void *threadHandler(void *args) {
    pthread_t tid = pthread_self();
    Human *info = (Human*)args;
    if (pthread_equal(tid, thread_id1)) {
        printf("This is thread 1, ---> tid1: %ld\n", tid);
    }
    else {
        printf("This is thread 2, ---> tid2: %ld\n", tid);
        printf("Print Information:\n- Name: %s\n- Birth: %d\n- Phone: %s\n- Home: %s\n", info->Name, info->BirthDay, info->PhoneNum, info->Home);
    }
}

int main(void)
{
    int ret;
    Human CaoTris = {"Tris", 2002, "0931081664", "Cu Chi"};

    if( pthread_create(&thread_id1,NULL,&threadHandler,NULL)) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    sleep(2);

    if ( pthread_create(&thread_id2,NULL,&threadHandler,&CaoTris)) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    
    return 0;
}