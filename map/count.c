#include <stdio.h>

int main()
{
  printf("Let's count from 1 to 4!\n");

  int i;

  // i will be automatically privatized.
  // There isn't a loop for each thread anymore,
  // the same loop will be split into small
  // tasks for each thread to solve.
  // map pattern
  #pragma omp parallel for
  for(i = 1; i <= 4; i++)
    printf("%d\n", i);
}
