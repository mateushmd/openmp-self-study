#include <stdio.h>

#define PROMPT "Let's count from 1 to 4!\n"

void count_function_scope();
void count_for_scope();
void count_for_scope_shared();

int main()
{
  int opt;
  
  (void)scanf("%d", &opt);

  switch(opt)
  {
    case 1: count_function_scope(); break;
    case 2: count_for_scope(); break;
    case 3: count_for_scope_shared(); break;
  }

  return 0;
}

void count_function_scope()
{
  #pragma omp parallel
  {
    printf("Let's count from 1 to 4!\n");

    int i;

    for(i = 1; i <= 4; i++)
      printf("%d\n", i);
  }
}

void count_for_scope()
{
  printf("Let's count from 1 to 4!\n");

  #pragma omp parallel
  for(int i = 1; i <= 4; i++)
      printf("%d\n", i);
}

void count_for_scope_shared()
{
  printf("Let's count from 1 to 4!\n");

  int i;

  // weird behaviour here
  // i became a shared resource. Now threads
  // will sooner or later access an i that was modified
  // by another thread, creating a race condition
  // won't work as expected
  #pragma omp parallel
  for(i = 1; i <= 4; i++)
      printf("%d\n", i);
}

