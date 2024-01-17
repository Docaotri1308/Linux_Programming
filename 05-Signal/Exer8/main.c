#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void sig_handler1(int num) {
    printf("This is Signal 1: %d\n",num);
    exit(EXIT_SUCCESS);
}

void sig_handler2(int num) {
    printf("This is Signal 2: %d\n",num );
}

void sig_handler3(int num) {
    printf("This is Signal 3: %d\n",num);
}

int main() {

    if (signal(SIGINT,sig_handler1) == SIG_ERR) {
        printf("Can not handler SIGINT1\n");
        exit(EXIT_FAILURE);
    }
    
    if (signal(SIGUSR1,sig_handler2) == SIG_ERR) {
        printf("Can not handler SIGUER21\n");
        exit(EXIT_FAILURE);
    }
        
    if (signal(SIGUSR2,sig_handler3) == SIG_ERR) {
        printf("Can not handler SIGUER3\n");
        exit(EXIT_FAILURE);
    }

    while(1) {
        printf("main() program is running ...\n");
        sleep(1);
    }
    
    return 0;
}