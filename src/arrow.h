#pragma once
#ifndef ARROW
#define ARROW

#define arr_ps float

arr_ps* arr_ps_new(int length);
void arr_ps_del(arr_ps* arr);

/***Arithmetic operations***/
void arr_ps_add(arr_ps* dest, arr_ps* arr1, arr_ps* arr2);
void arr_ps_sub(arr_ps* dest, arr_ps* arr1, arr_ps* arr2);
void arr_ps_mul(arr_ps* dest, arr_ps* arr1, arr_ps* arr2);

#endif