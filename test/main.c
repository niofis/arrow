#include <stdio.h>
#include <time.h>
#include "arrow.h"

int main(int argc, char* argv[])
{
  clock_t start;
  clock_t end;
  
  
  const uint32_t size = 512 * 1024 * 1024 / 4;
  float* ps = arr_ps_new(size);
  float* ps2 = arr_ps_new(size);

  for(int i = 0; i < size; ++i) 
  {
    ps[i] = 1;
    ps2[i] = 2;
  }

  start = clock();
  arr_ps_add(ps,ps,ps2);
  end = clock();
  printf("Elapsed: %fs\n", (end - start)/(double)CLOCKS_PER_SEC);

  /*
  for(int i = 0; i < size; ++i)
  {
    printf("%f ", ps[i]);
  }
  */

  printf("\n");

  system("pause");

  arr_ps_del(ps);
  arr_ps_del(ps2);


  return 0;
}
