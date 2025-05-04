#include <stdio.h>

const long long MAX_STEP = 1000000000;

double step;

int main()
{
  int i;
  double x, pi, sum = 0.0;
  step = 1.0 / (double)MAX_STEP;

  // optimal solution for this problem
  // will sum the partial results of each thread,
  // generating a single value at the end.
  // reduce pattern
  #pragma omp parallel for private(x) reduction(+:sum)
  for(i = 0; i < MAX_STEP; i++)
  {
    x = (i + 0.5) * step; 
    sum = sum + 4.0 / (1.0 + x * x); 
  }

  pi = sum * step;

  printf("pi = %f\n", pi);
}
