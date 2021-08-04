#define _GNU_SOURCE    // to use strnlen(), getline(), ssize() for bytes check
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int fib(int * array, long int num)
{
    if (num < 2)
    {
        array[num] = num;
        return array[num];
    }
    // memoization
    if (0 != array[num])
    {
        return array[num];
    }
    else
    {
        array[num] = fib(array, num-1) + fib(array, num-2);
        return array[num];
    }
    
}

int main(){

    int * array = calloc(1, 1024);
    for (long int idx = 1; idx < 50; ++idx)
    {
        printf("fib %d\n", fib(array, idx));
    }
    free(array);
    return 0;
}