#include <stdio.h>
#include <stdlib.h>
#include "fibonacci.h"

int main(void) {
    int n = 10;  // Example: computing the 10th Fibonacci number

    printf("iterative_fibonacci(%d) = %d\n", n, iterative_fibonacci(n));
    printf("recursive_fibonacci(%d) = %d\n", n, recursive_fibonacci(n));

    // For dynamic programming, create arrays of size n+1 (initialized to -1)
    int *f_dpbu = malloc((n + 1) * sizeof(int));
    int *f_dptd = malloc((n + 1) * sizeof(int));
    
    for(int i = 0; i <= n; i++) {
        f_dpbu[i] = -1;
        f_dptd[i] = -1;
    }

    printf("dpbu_fibonacci(%d) = %d\n", n, dpbu_fibonacci(f_dpbu, n));
    printf("dptd_fibonacci(%d) = %d\n", n, dptd_fibonacci(f_dptd, n));

    free(f_dpbu);
    free(f_dptd);

    return 0;
}
