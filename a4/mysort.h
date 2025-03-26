#ifndef MYSORT_H
#define MYSORT_H

/**
 * Use selection sort algorithm to sort an array of pointers such that their pointed values 
 * are in increasing order. (Assumes that the pointers refer to integers.)
 *
 * @param a[]  Array of void pointers.
 * @param left The starting index in the array.
 * @param right The ending index in the array.
 */
void select_sort(void *a[], int left, int right);

/**
 * Use quick sort algorithm to sort an array of pointers such that their pointed values 
 * are in increasing order. (Assumes that the pointers refer to integers.)
 *
 * @param a[]  Array of void pointers.
 * @param left The starting index in the array.
 * @param right The ending index in the array.
 */
void quick_sort(void *a[], int left, int right);

/**
 * Use either selection sort or quick sort algorithm to sort an array of pointers such that 
 * their pointed values are in the order defined by the given comparison function.
 *
 * @param a[]  Array of void pointers.
 * @param left The starting index in the array.
 * @param right The ending index in the array.
 * @param cmp  Pointer to a comparison function used to compare the pointed values.
 *             The function should return a negative value if the first argument is less than 
 *             the second, zero if equal, and a positive value otherwise.
 */
void my_sort(void *a[], int left, int right, int (*cmp)(void*, void*));

#endif /* MYSORT_H */
