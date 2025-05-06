#include <stdio.h>
#include <math.h>

#define MAX_NUM 5000000
#define BLOCK 100

int is_prime(long num);

long prime_single_thread();
long prime_reduction();
long prime_critical();
long prime_schedule();


int main(int argc, char** argv)
{
    if(argc != 2 || argv[1][0] < '1' || argv[1][0] > '9')
    {
        printf("expected a single argument (non zero integer)");
        return 1;
    }

    long r;

    switch(argv[1][0])
    {
        case '1':
            r = prime_single_thread();
            break;
        case '2':
            r = prime_reduction();
            break;
        case '3':
            r = prime_critical();
            break;
        case '4':
            r = prime_schedule();
            break;
    }

    printf("found %ld primes\n", r);
}

long prime_single_thread()
{
    if(MAX_NUM <= 1) return 0;
    else if (MAX_NUM == 2) return 1; 

    long count, sum, n;

    sum = 1;
    for(n = 3; n < MAX_NUM; n += 2)
    {
        count = is_prime(n);
        sum = sum + count;
    }

    return sum;
}

long prime_reduction()
{
    if(MAX_NUM <= 1) return 0;
    else if (MAX_NUM == 2) return 1; 

    long count, sum, n;

    sum = 1;
    #pragma omp parallel for private(count) reduction(+:sum)
    for(n = 3; n < MAX_NUM; n += 2)
    {
        count = is_prime(n);
        sum = sum + count;
    }

    return sum;
}

long prime_critical()
{
    if(MAX_NUM <= 1) return 0;
    else if (MAX_NUM == 2) return 1; 

    long count, sum, n;

    sum = 1;
    // here using a critical section isn't that big
    // of a problem. The bottleneck is on is_prime 
    // function, so there is little wainting on the
    // threads
    #pragma omp parallel for private(count)
    for(n = 3; n < MAX_NUM; n += 2)
    {
        count = is_prime(n);
        #pragma omp critical
        sum = sum + count;
    }

    return sum;
}

long prime_schedule()
{
    if(MAX_NUM <= 1) return 0;
    else if (MAX_NUM == 2) return 1; 

    long count, sum, n;

    sum = 1;
    // the best way to increase performance here is
    // distributing the workload between the threads.
    // This is because some iterations takes more time
    // than others, making the workload unbalanced between
    // the threads. By using worklooad distribution, we give
    // more work for threads that finish their job earlier,
    // getting a faster result in the end. And, with a dynamic
    // schedule, after a thread finishes its job, it will
    // search for more work to do while the others are
    // busy finishing theirs
    #pragma omp parallel for private(count) reduction(+:sum) schedule(dynamic, BLOCK)
    for(n = 3; n < MAX_NUM; n += 2)
    {
        count = is_prime(n);
        sum = sum + count;
    }

    return sum;
} 

int is_prime(long num)
{
    long d;

    if(num <= 1) return 0;

    else if(num > 3)
    {
        if(num % 2 == 0) return 0;

        long max_divisor = sqrt(num);

        for(d = 3; d <= max_divisor; d+=2)
            if(num % d == 0) return 0;
    }

    return 1;
}
