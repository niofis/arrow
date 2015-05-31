#include <stdio.h>
#include "arrow.h"

int main(int argc, char* argv[])
{

  const int size = 10240000;
  float* ps = arr_ps_new(size);
  float* ps2 = arr_ps_new(size);

  for(int i = 0; i < size; ++i) 
  {
    ps[i] = 1;
    ps2[i] = 2;
  }

  arr_ps_add(ps,ps,ps2);

  for(int i = 0; i < size; ++i)
  {
    printf("%f ", ps[i]);
  }

  printf("\n");

  arr_ps_del(ps);
  arr_ps_del(ps2);


  return 0;
}
