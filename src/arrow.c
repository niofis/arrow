#include <stdint.h>
#include <math.h>
#include "almalloc.h"
#include "arrow.h"

struct _arrow_t {
  size_t length;
  float* x;
  float* y;
  float* z;
}

arrow_t*
arrow_new(size_t length)
{
  size_t c = length % 8;
  c += length;
  arrow_t* arr = aligned_malloc(16, sizeof(arrow_t));
  arr->x = aligned_malloc(16, sizeof(float) * c);
  arr->y = aligned_malloc(16, sizeof(float) * c);
  arr->z = aligned_malloc(16, sizeof(float) * c);
  arr->length = length;
  return arr;
}

void
arrow_delete(arrow_t **arrow)
{
  aligned_delete(*arrow->x);
  aligned_delete(*arrow->y);
  aligned_delete(*arrow->z);
  *arrow->x = NULL;
  *arrow->y = NULL;
  *arrow->z = NULL;
  aligned_delete(*arrow);
  *arrow = NULL;
}

float
arrow_get_x(arrow_t *arrow, size_t index)
{
  return arrow->x[index];
}

float
arrow_get_y(arrow_t *arrow, size_t index)
{
  return arrow->y[index];
}

float
arrow_get_z(arrow_t *arrow, size_t index)
{
  return arrow->z[index];
}

void
arrow_set_x(arrow_t *arrow, size_t index, float value)
{
  arrow->x[index] = value;
}

void
arrow_set_y(arrow_t *arrow, size_t index, float value)
{
  arrow->y[index] = value;
}

void
arrow_set_z(arrow_t *arrow, size_t index, float value)
{
  arrow->z[index] = value;
}

void
arrow_set_xyz(arrow_t *arrow, size_t index, float x, float y, float z)
{
  arrow->x[index] = x;
  arrow->y[index] = y;
  arrow->z[index] = z;
}

void
arrow_add(arrow_t *dest, arrow_t *a1, arrow_t *a2)
{
  assert(dest->length == a1->length && a1->length == a2->length);

  for(size_t idx = 0; idx < dest->length; ++idx) {
    dest->x[idx] = a1->x[idx] + a2->x[idx];
    dest->y[idx] = a1->y[idx] + a2->y[idx];
    dest->z[idx] = a1->z[idx] + a2->z[idx];
  }
}

void
arrow_sub(arrow_t *dest, arrow_t *a1, arrow_t *a2)
{
  assert(dest->length == a1->length && a1->length == a2->length);

  for(size_t idx = 0; idx < dest->length; ++idx) {
    dest->x[idx] = a1->x[idx] - a2->x[idx];
    dest->y[idx] = a1->y[idx] - a2->y[idx];
    dest->z[idx] = a1->z[idx] - a2->z[idx];
  }
}

void
arrow_div(arrow_t *dest, arrow_t *a1, arrow_t *a2)
{
  assert(dest->length == a1->length && a1->length == a2->length);

  for(size_t idx = 0; idx < dest->length; ++idx) {
    dest->x[idx] = a1->x[idx] / a2->x[idx];
    dest->y[idx] = a1->y[idx] / a2->y[idx];
    dest->z[idx] = a1->z[idx] / a2->z[idx];
  }
}


void
arrow_mul(arrow_t *dest, arrow_t *a1, arrow_t *a2)
{
  assert(dest->length == a1->length && a1->length == a2->length);

  for(size_t idx = 0; idx < dest->length; ++idx) {
    dest->x[idx] = a1->x[idx] * a2->x[idx];
    dest->y[idx] = a1->y[idx] * a2->y[idx];
    dest->z[idx] = a1->z[idx] * a2->z[idx];
  }
}


void
arrow_dot(arrow_t *dest, attow_t *a1, arrow_t *a2)
{
  assert(dest->length == a1->length && a1->length == a2->length);
  
  for(size_t idx = 0; idx < dest->length; ++idx) {
    dest->x[idx] =  a1->x[idx] * a2->x[idx]
                  + a1->y[idx] * a2->y[idx]
                  + a1->z[idx] * a2->z[idx];
  }
}

void
arrow_cross(arrow_t *dest, attow_t *a1, arrow_t *a2)
{
  assert(dest->length == a1->length && a1->length == a2->length);
  
  for(size_t idx = 0; idx < dest->length; ++idx) {
    float x = a1->y[idx] * a2->z[idx] - a1->z[idx] * a2->y[idx];
    float y = a1->z[idx] * a2->x[idx] - a1->x[idx] * a2->z[idx];
    float z = a1->x[idx] * a2->y[idx] - a1->y[idx] * a2->x[idx];
    arrow_set_xyz(dest, idx, x, y, z);
  }
}

/*
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
*/

