#include "bigint.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * Creates a BIGINT from the given digit string.
 * Each character in the string is assumed to be a digit.
 * The BIGINT stores the number in the same order as the string:
 * head node = most significant digit, tail node = least significant digit.
 */
BIGINT bigint(char *digitstr) {
    if (digitstr == NULL) {
        return NULL;
    }
    
    // Allocate and initialize a new DLL (BIGINT)
    BIGINT b = (BIGINT)malloc(sizeof(DLL));
    if (b == NULL) {
        fprintf(stderr, "Memory allocation failed in bigint()\n");
        exit(EXIT_FAILURE);
    }
    b->length = 0;
    b->start = b->end = NULL;
    
    // Process each character in the string
    for (int i = 0; digitstr[i] != '\0'; i++) {
        char ch = digitstr[i];
        if (!isdigit(ch)) {
            // If non-digit is encountered, you may choose to handle the error.
            continue;
        }
        // Create a new node for this digit
        NODE *node = dll_node(ch);
        // Insert at the end so that the order of digits is preserved.
        dll_insert_end(b, node);
    }
    return b;
}

/*
 * Adds two BIGINT numbers and returns their sum as a BIGINT.
 * The addition is performed by iterating from the least significant digits
 * (the tail nodes) towards the most significant digits.
 */
BIGINT bigint_add(BIGINT op1, BIGINT op2) {
    // Allocate and initialize a new BIGINT to hold the sum.
    BIGINT result = (BIGINT)malloc(sizeof(DLL));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed in bigint_add()\n");
        exit(EXIT_FAILURE);
    }
    result->length = 0;
    result->start = result->end = NULL;
    
    NODE *p1 = op1->end;  // pointer to least significant digit of operand1
    NODE *p2 = op2->end;  // pointer to least significant digit of operand2
    int carry = 0;
    
    while (p1 != NULL || p2 != NULL || carry != 0) {
        int d1 = (p1 != NULL) ? (p1->data - '0') : 0;
        int d2 = (p2 != NULL) ? (p2->data - '0') : 0;
        int sum = d1 + d2 + carry;
        int digit = sum % 10;
        carry = sum / 10;
        
        // Create a node for the resulting digit.
        NODE *node = dll_node((char)(digit + '0'));
        // Since we are adding from the least significant end,
        // insert each new digit at the start to obtain the proper order.
        dll_insert_start(result, node);
        
        if (p1 != NULL) p1 = p1->prev;
        if (p2 != NULL) p2 = p2->prev;
    }
    
    return result;
}

/*
 * Computes and returns Fibonacci(n) as a BIGINT.
 * For n <= 0, returns BIGINT representing 0.
 * For n = 1 or n = 2, returns BIGINT representing 1.
 * Uses an iterative algorithm with BIGINT addition.
 */
BIGINT bigint_fibonacci(int n) {
    if (n <= 0) {
        return bigint("0");
    }
    if (n == 1 || n == 2) {
        return bigint("1");
    }
    
    BIGINT f1 = bigint("1");
    BIGINT f2 = bigint("1");
    BIGINT sum = NULL;
    
    for (int i = 3; i <= n; i++) {
        sum = bigint_add(f1, f2);
        // Clean up f1 before reassigning to avoid memory leaks.
        dll_clean(f1);
        free(f1);
        f1 = f2;
        f2 = sum;
    }
    // f2 now holds Fibonacci(n)
    return f2;
}
