#pragma once

#include <stdint.h>
#include <math.h>

typedef struct _arrow_t arrow_t;

arrow_t*
  arrow_new(uintptr_t length);

void
  arrow_delete(arrow_t **arrow);

float
  arrow_get_x(arrow_t *arrow, uintptr_t index);

float
  arrow_get_y(arrow_t *arrow, uintptr_t index);

float
  arrow_get_z(arrow_t *arrow, uintptr_t index);

void
  arrow_set_x(arrow_t *arrow, uintptr_t index, float value);

void
  arrow_set_y(arrow_t *arrow, uintptr_t index, float value);

void
  arrow_set_z(arrow_t *arrow, uintptr_t index, float value);

void
  arrow_set_xyz(arrow_t *arrow, uintptr_t index, float x, float y, float z);

void
  arrow_add(arrow_t *dest, arrow_t *a1, arrow_t *a2);

void
  arrow_sub(arrow_t *dest, arrow_t *a1, arrow_t *a2);

void
  arrow_div(arrow_t *dest, arrow_t *a1, arrow_t *a2);

void
  arrow_mul(arrow_t *dest, arrow_t *a1, arrow_t *a2);

void
  arrow_dot(arrow_t *dest, attow_t *a1, arrow_t *a2);

void
  arrow_cross(arrow_t *dest, attow_t *a1, arrow_t *a2);
