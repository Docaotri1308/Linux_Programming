#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <asm-generic/signal-defs.h>
#include <asm/signal.h>

void sig_handler1(int num)
{
    printf("This is Signal 1: %d\n",num);
    exit(EXIT_SUCCESS);
}

int main()
{   
    if (signal(SIGINT, sig_handler1) == SIG_ERR) {
        printf("Can not handler SIGINT1\n");
        exit(EXIT_FAILURE);
    }
    
    sigset_t block_mask;
    sigemptyset(&block_mask);
    sigaddset(&block_mask, SIGINT);
    
    if (sigprocmask(SIG_BLOCK, &block_mask, NULL) == 0) {
        printf("Blocking SIGINT\n");  
        if (sigismember(&block_mask, SIGINT) == 1) {
            printf("SIGINT is blocked!\n");
            sleep(2); 
        }
    }
    if (sigprocmask(SIG_UNBLOCK, &block_mask, NULL) == 0) {
        printf("Unblocking SIGINT\n");  
        if (sigismember(&block_mask, SIGINT) == 1) {
            printf("SIGINT is unblocked!\n");
            sleep(2); 
        }
    }

    while(1);
    
    return 0;
}