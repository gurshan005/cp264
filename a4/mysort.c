#include "mysort.h"

/* 
 * Auxiliary function to swap two elements in the array.
 */
static void swap(void **a, void **b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * Default comparison function.
 * Assumes that the void pointers refer to integers.
 * Returns -1 if *(int *)p1 < *(int *)p2, 1 if greater, and 0 if equal.
 */
static int default_compare(void *p1, void *p2) {
    int a = *(int *)p1;
    int b = *(int *)p2;
    if (a < b)
        return -1;
    else if (a > b)
        return 1;
    else
        return 0;
}

/*
 * Partition function used in quick sort.
 * It reorders the array segment [left, right] so that all elements less than or equal to 
 * the pivot are to its left and the others to its right. Returns the final pivot index.
 */
static int partition(void *a[], int left, int right, int (*cmp)(void*, void*)) {
    void *pivot = a[right];  // Choose the rightmost element as the pivot.
    int i = left - 1;
    int j;
    for (j = left; j < right; j++) {
        if (cmp(a[j], pivot) <= 0) {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[right]);
    return i + 1;
}

/*
 * Recursive quick sort implementation that uses the provided comparison function.
 */
static void quick_sort_with_cmp(void *a[], int left, int right, int (*cmp)(void*, void*)) {
    if (left < right) {
        int pivot_index = partition(a, left, right, cmp);
        quick_sort_with_cmp(a, left, pivot_index - 1, cmp);
        quick_sort_with_cmp(a, pivot_index + 1, right, cmp);
    }
}

/*
 * Implementation of selection sort.
 * Iterates over the array segment [left, right] and finds the minimum element in the unsorted 
 * portion to swap with the element at the current index.
 */
void select_sort(void *a[], int left, int right) {
    int i, j, min_index;
    for (i = left; i <= right; i++) {
        min_index = i;
        for (j = i + 1; j <= right; j++) {
            if (default_compare(a[j], a[min_index]) < 0) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(&a[i], &a[min_index]);
        }
    }
}

/*
 * Implementation of quick sort using the default comparison function.
 */
void quick_sort(void *a[], int left, int right) {
    quick_sort_with_cmp(a, left, right, default_compare);
}

/*
 * Generic sort function that uses quick sort with the caller-supplied comparison function.
 */
void my_sort(void *a[], int left, int right, int (*cmp)(void*, void*)) {
    quick_sort_with_cmp(a, left, right, cmp);
}
