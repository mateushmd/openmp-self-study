#include <stdio.h>

int main()
{
  printf("Let's count from 1 to 4!\n");

  int i;

  // by making i private instead of shared,
  // we remove the race condition. Now all
  // threads will be able to print from 1 to 4,
  // not necessarily ordered tho
  #pragma omp parallel private(i)
  for(i = 1; i <= 4; i++)
    printf("%d\n", i);
}
