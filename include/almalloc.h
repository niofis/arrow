#pragma once

#include <stdlib.h>
#include <stdint.h>

void* aligned_malloc(int aligment_bytes, long size)
{
  uintptr_t* ptr;
  uintptr_t* aligned_ptr;
  int ptr_size;

  ptr_size = sizeof(uintptr_t);

  ptr = malloc(aligment_bytes + size + ptr_size);
  aligned_ptr = ptr;
  aligned_ptr = aligned_ptr + ptr_size;
  aligned_ptr += (uintptr_t)aligned_ptr % (uintptr_t)aligment_bytes;

  *((uintptr_t*)aligned_ptr - 1) = (uintptr_t)ptr;

  return aligned_ptr;

}

void aligned_free(void* aligned_memory)
{
  uintptr_t* ptr;

  ptr = ((uintptr_t*)aligned_memory - 1);

  ptr = (uintptr_t*) *ptr;

  free(ptr);

}
