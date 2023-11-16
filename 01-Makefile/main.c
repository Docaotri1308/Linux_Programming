#include <stdio.h>
#include "inc/hello.h"
#include "inc/mymath.h"

int main()
{
    hello();
    printf("13 + 8 = %d\n", sum(13, 8));
    return 0;
}