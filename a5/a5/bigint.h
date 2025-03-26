#ifndef BIGINT_H
#define BIGINT_H

#include "dllist.h"  // Contains definitions of NODE and DLL

/* 
 * Define BIGINT as a pointer to DLL.
 */
typedef DLL *BIGINT;

/* 
 * Creates and returns a BIGINT object by converting the digit string.
 * The digit string is assumed to consist solely of digit characters ('0'-'9').
 */
BIGINT bigint(char *digitstr);

/* 
 * Add two BIGINT operands and return the sum as a BIGINT.
 * @param oprand1 - first operand (BIGINT)
 * @param oprand2 - second operand (BIGINT)
 * @return the sum of oprand1 and oprand2 in BIGINT type.
 */
BIGINT bigint_add(BIGINT oprand1, BIGINT oprand2);

/* 
 * Compute and return Fibonacci(n).
 * @param n - input positive integer
 * @return Fibonacci(n) as a BIGINT.
 */
BIGINT bigint_fibonacci(int n);

#endif
