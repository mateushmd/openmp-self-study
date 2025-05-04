#include <stdio.h>

const long long MAX_STEP = 1000000000;

double step;

void pi_single_thread();
void pi_map();
void pi_map_private();
void pi_map_critical();

int main(int argc, char** argv)
{
  if(argc != 2 || argv[1][0] < '1' || argv[1][0] > '4')
  {
    printf("expected exatcly one argument (integer)");
    return 1;
  }

  switch(argv[1][0] - '1')
  {
    case 0: pi_single_thread(); break;
    case 1: pi_map(); break;
    case 2: pi_map_private(); break;
    case 3: pi_map_critical(); break;
  }

  return 0;
}

void pi_single_thread()
{
  int i;
  double x, pi, sum = 0.0;
  step = 1.0 / (double)MAX_STEP;

  for(i = 0; i < MAX_STEP; i++)
  {
    x = (i + 0.5) * step;
    sum = sum + 4.0 / (1.0 + x * x); 
  }

  pi = sum * step;

  printf("pi = %f\n", pi);
}

void pi_map()
{
  int i;
  double x, pi, sum = 0.0;
  step = 1.0 / (double)MAX_STEP;

  // this won't work
  #pragma omp parallel for
  for(i = 0; i < MAX_STEP; i++)
  {
    // x is shared but depends only on a private resource
    // fine up until here 
    x = (i + 0.5) * step; 

    // sum is shared + depends on itself and another 
    // shared resouce, this is terrible 
    // race condition
    sum = sum + 4.0 / (1.0 + x * x); 
  }

  pi = sum * step;

  printf("pi = %f\n", pi);
}

void pi_map_private()
{
  int i;
  double x, pi, sum = 0.0;
  step = 1.0 / (double)MAX_STEP;

  // this won't work
  #pragma omp parallel for private(x)
  for(i = 0; i < MAX_STEP; i++)
  {
    // x is private now
    x = (i + 0.5) * step; 

    // sum is shared and depends on itself 
    // race condition
    sum = sum + 4.0 / (1.0 + x * x); 
  }

  pi = sum * step;

  printf("pi = %f\n", pi);
}

void pi_map_critical()
{
  int i;
  double x, pi, sum = 0.0;
  step = 1.0 / (double)MAX_STEP;

  // will work but slower than single-threaded 
  #pragma omp parallel for private(x)
  for(i = 0; i < MAX_STEP; i++)
  {
    // x is private now
    x = (i + 0.5) * step; 
    
    // removes race condition because threads will wait
    // but the queue adds bottleneck
    #pragma omp critical
    sum = sum + 4.0 / (1.0 + x * x); 
  }

  pi = sum * step;

  printf("pi = %f\n", pi);
}
