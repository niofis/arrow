#pragma once

#include <stdint.h>
#include <math.h>

typedef struct _arrow_t arrow_t;

arrow_t*
  arrow_new(uintptr_t length);

void
  arrow_delete(arrow_t **arrow);

float
  arrow_get(uintptr_t index);

void
  arrow_set(uintptr_t index, float value);

//the user must ensure that values lenght equals arrow_t length
void
  arrow_set_all(arrow_t, float* values); 

//might not always return a valid pointer, it depends on the destination device
float*
  arrow_get_array_ptr(arrow_t *arrow);

void
  arrow_add(arrow_t *dest, arrow_t *a1, arrow_t *a2);

void
  arrow_sub(arrow_t *dest, arrow_t *a1, arrow_t *a2);

void
  arrow_div(arrow_t *dest, arrow_t *a1, arrow_t *a2);

void
  arrow_mul(arrow_t *dest, arrow_t *a1, arrow_t *a2);
