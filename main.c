#include <stdio.h>
#include <stdlib.h>
#include "pvec.h"

void pvec_demo() {
    // Initialize the pvec
    uint64_t *longPvec = pvec_newPvec();
    uint64_t *pvec2 = pvec_newPvec();

    // Create the long pvec with values and print it
    for(int i = 0; i < 500; i++) {
        pvec_append(longPvec, i);
    }
    printf("1: ");
    pvec_print(longPvec);
    // Create the short pvec with values and print it
    for(int i = 0; i < 10; i++) {
        pvec_append(pvec2, i + 1);
    }
    printf("2: ");
    pvec_print(pvec2);
    // Operate on the first pvec
    pvec_remove(longPvec, 0);
    pvec_remove(longPvec, 1);
    pvec_insert(longPvec, 3, 5);
    printf("1: ");
    pvec_print(longPvec);
    // Operate on the second pvec
    pvec_pop(pvec2);
    pvec_setValue(pvec2, 4, 99);
    printf("2: ");
    pvec_print(pvec2);
    // Print the length
    printf("1: %lu\n", pvec_getLength(longPvec));
    printf("2: %lu\n", pvec_getLength(pvec2));
    pvec_delete(longPvec);
    pvec_delete(pvec2);
}


int main() {
    pvec_demo();
//    main();
    return 0;
}

