#pragma once
#ifndef ARROW
#define ARROW

#include <stdint.h>
#include "almalloc.h"

struct arr_desc
{
  uint32_t length;
  uint32_t pad[3];
};

float* arr_ps_new(int length)
{
  void* arr;
  struct arr_desc* desc;

  arr = aligned_malloc(16, sizeof(struct arr_desc) + sizeof(float)*length);

  desc = arr;
  desc->length = length;

  return arr;
}

void arr_ps_del(void* arr)
{
  void* ptr = arr - sizeof(struct arr_desc);
  
  aligned_free(ptr);
}

/***Arithmetic operations***/
void arr_ps_add(float* dest, float* arr1, float* arr2);
void arr_ps_sub(float* dest, float* arr1, float* arr2);
void arr_ps_mul(float* dest, float* arr1, float* arr2);
void arr_ps_div(float* dest, float* arr1, float* arr2);

#endif
