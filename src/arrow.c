#include <stdint.h>
#include <math.h>
#include "almalloc.h"
#include "arrow.h"

struct _arrow_t {
  uintptr_t length;
  float* data;
}

arrow_t*
arrow_new(uintptr_t length)
{
  arrow_t* arr = aligned_malloc(16, sizeof(arrow_t));
  arr->data = aligned_malloc(16, sizeof(float) * length);
  return arr;
}

void
arrow_delete(arrow_t **arrow)
{
  aligned_delete(*arrow->data);
  *arrow->data = NULL;
  aligned_delete(*arrow);
  *arrow = NULL;
}

struct arr_desc
{
  uint32_t length;
  uint32_t pad[3];
};

struct arr_params
{
  void* dest;
  void* arr1;
  void* arr2;
  uint32_t length;
  uint32_t offset;
};
  

float* arr_ps_new(uint32_t length)
{
  uint8_t* arr;
  struct arr_desc* desc;

  arr = aligned_malloc(16, sizeof(struct arr_desc) + sizeof(float)*length);

  //use the initial part of the allocated memory
  //to store an arr_desc structure
  desc = (struct arr_desc*)arr;
  desc->length = length;
  
  //move the pointer forward the number of bytes of the arr_desc struct
  arr += sizeof(struct arr_desc);

  return (float*)arr;
}

void arr_ps_del(void* arr)
{
  //retrieve the original pointer
  void* ptr = (struct arr_desc*)arr - 1;

  aligned_free(ptr);
}

float arr_ps_get(uint64_t index)
{

}

float arr_ps_set(uint64_t index, float value)
{

}

float arr_ps_set_all(float* value)
{

}

struct arr_desc* arr_desc_get(void* arr)
{
  return (struct arr_desc*)arr - 1;
}

/***Arithmetic operations***/
void arr_ps_add(float* dest, float* arr1, float* arr2)
{
	const struct arr_desc* desc = arr_desc_get(arr1);
	const uint32_t size = desc->length;
	int i = 0;

	#pragma omp parallel for private(i) //num_threads(8)
	for (i = 0; i < size; ++i)
	{
		dest[i] = arr1[i] - arr2[i];
	};
}

void arr_ps_sub(float* dest, float* arr1, float* arr2)
{
	const struct arr_desc* desc = arr_desc_get(arr1);
	const uint32_t size = desc->length;
  int i = 0;

	#pragma omp parallel for private(i)
  for(i = 0; i < size; ++i)
  {
    dest[i] = arr1[i] - arr2[i];
  } 
}

void arr_ps_mul(float* dest, float* arr1, float* arr2)
{
  const struct arr_desc* desc = arr_desc_get(arr1);
  const uint32_t size = desc->length;
  int i = 0;

  #pragma omp parallel for private(i)
  for(i = 0; i < size; ++i)
  {
    dest[i] = arr1[i] * arr2[i];
  }
}

void arr_ps_div(float* dest, float* arr1, float* arr2)
{
  const struct arr_desc* desc = arr_desc_get(arr1);
  const uint32_t size = desc->length;
  int i = 0;

  #pragma omp parallel for private(i)
  for(i = 0; i < size; ++i)
  {
    dest[i] = arr1[i] / arr2[i];
  }
}

void arr_ps_sqrt(float* dest, float* arr1)
{
  const struct arr_desc* desc = arr_desc_get(arr1);
  const uint32_t size = desc->length;
  int i = 0;

  #pragma omp parallel for private(i)
  for(i = 0; i < size; ++i)
  {
    dest[i] = sqrtf(arr1[i]);
  }
}


