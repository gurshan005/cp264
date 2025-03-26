// heap.c
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to swap two elements
static void heap_swap(HEAPDATA *a, HEAPDATA *b) {
    HEAPDATA temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify up from given index
static void heapify_up(HEAP *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->hda[index].key < heap->hda[parent].key) {
            heap_swap(&heap->hda[index], &heap->hda[parent]);
            index = parent;
        } else break;
    }
}

// Heapify down from given index
static void heapify_down(HEAP *heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->hda[left].key < heap->hda[smallest].key)
        smallest = left;
    if (right < heap->size && heap->hda[right].key < heap->hda[smallest].key)
        smallest = right;

    if (smallest != index) {
        heap_swap(&heap->hda[index], &heap->hda[smallest]);
        heapify_down(heap, smallest);
    }
}

HEAP *new_heap(int capacity) {
    HEAP *heap = (HEAP *)malloc(sizeof(HEAP));
    heap->size = 0;
    heap->capacity = capacity;
    heap->hda = (HEAPDATA *)malloc(capacity * sizeof(HEAPDATA));
    return heap;
}

void heap_insert(HEAP *heap, HEAPDATA data) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->hda = realloc(heap->hda, heap->capacity * sizeof(HEAPDATA));
    }
    heap->hda[heap->size] = data;
    heapify_up(heap, heap->size);
    heap->size++;
}

HEAPDATA heap_find_min(HEAP *heap) {
    return heap->hda[0];
}

HEAPDATA heap_extract_min(HEAP *heap) {
    HEAPDATA min_data = heap->hda[0];
    heap->hda[0] = heap->hda[--heap->size];
    heapify_down(heap, 0);

    if (heap->capacity > 4 && heap->size <= heap->capacity / 4) {
        heap->capacity /= 2;
        heap->hda = realloc(heap->hda, heap->capacity * sizeof(HEAPDATA));
    }
    return min_data;
}

int heap_change_key(HEAP *heap, int index, KEYTYPE new_key) {
    KEYTYPE old_key = heap->hda[index].key;
    heap->hda[index].key = new_key;
    if (new_key < old_key)
        heapify_up(heap, index);
    else
        heapify_down(heap, index);

    return index;
}

int heap_search_value(HEAP *heap, VALUETYPE val) {
    for (int i = 0; i < heap->size; i++)
        if (heap->hda[i].value == val)
            return i;
    return -1;
}

void heap_clean(HEAP **heapp) {
    if (heapp && *heapp) {
        free((*heapp)->hda);
        free(*heapp);
        *heapp = NULL;
    }
}

void heap_sort(HEAPDATA *arr, int n) {
    HEAP *temp_heap = new_heap(n);
    for (int i = 0; i < n; i++)
        heap_insert(temp_heap, arr[i]);

    for (int i = n - 1; i >= 0; i--)
        arr[i] = heap_extract_min(temp_heap);

    heap_clean(&temp_heap);
}