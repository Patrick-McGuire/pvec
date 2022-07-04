#include "pvec.h"

/* Format for pvec:
 *  First memory block:
 *      <64bit address of next element><64bit length>
 *  Element memory block:
 *      <64bit address of next element><64bit value>
 */

uint64_t pvec_countDigits(uint64_t num) {
    return num < 10 ? num > 0 : pvec_countDigits(num / 10) + 1;
}

void pvec_print(uint64_t *pvec) {
    uint32_t digits = 0;                                        // Keep track of the total number of digits we will need to print
    uint64_t len = pvec_getLength(pvec);                        // Get the number of elements in the pvec
    for (int i = 0; i < len; i++) {                              // Count the total number of digits
        uint32_t temp = pvec_countDigits(pvec_getValue(pvec, i));
        digits += temp == 0 ? 1 : temp;
    }
    uint32_t strSize = digits + (len * 2) + 4;                  // Calculate the buffer size needed
    char *buf = malloc(strSize);
    buf[0] = '{';
    buf[1] = ' ';
    char *ptr = &buf[2];                                        // Get all values from the pvec and add them to the buffer
    for (int i = 0; i < len - 1; i++) {
        uint64_t val = pvec_getValue(pvec, i);
        sprintf(ptr, "%lu, ", val);
        uint32_t temp = pvec_countDigits(val);
        ptr = &ptr[(temp == 0 ? 1 : temp) + 2];
    }
    sprintf(ptr, "%lu }\n", pvec_getValue(pvec, len - 1));
    printf("%s", buf);                                          // Print the result
    free(buf);
}

uint64_t pvec_getLength(uint64_t *pvec) {
    return pvec[1];                                 // Retrieve the length of the pvec
}

uint64_t *pvec_getPointerToElement(uint64_t *pvec, uint64_t index) {
    uint64_t len = pvec_getLength(pvec);            // Get length of the pvec
    if (index > len) {                               // Clip the index
        index = len;
    }
    uint64_t *elementPtr = pvec;                    // Current block pointer
    for (int i = 0; i < index; i++) {
        elementPtr = (uint64_t *) elementPtr[0];     // Iterate to the next block
    }
    return elementPtr;                              // Return pointer to the desired block
}

uint64_t *pvec_newPvec() {
    uint64_t *pvecPtr = calloc(2, sizeof(uint64_t));        // Get the memory needed for a array of length 0
    pvecPtr[1] = 0;                                         // Set the length to 0
    return pvecPtr;
}

void pvec_append(uint64_t *pvec, uint64_t val) {
    uint64_t *lastElePtr = pvec_getPointerToElement(pvec, pvec_getLength(pvec));     // Get the pointer to the last element of the array
    uint64_t *nextEle = calloc(2, sizeof(uint64_t));                                 // Get the memory for the next element
    nextEle[1] = val;                                                                // Set the value in the block allocated
    lastElePtr[0] = (uint64_t) nextEle;                                              // Save the pointer to this block in the last block
    pvec[1]++;                                                                       // Increment the stored length of the pvec
}

uint64_t pvec_pop(uint64_t *pvec) {
    uint64_t *lastElePtr = pvec_getPointerToElement(pvec, pvec_getLength(pvec));     // Get the pointer to the last element of the array
    uint64_t out = lastElePtr[1];                                                    // Save the last value in the pvec so we can free the memory
    pvec[1]--;                                                                       // Decrease the length by 1
    free(lastElePtr);                                                                // Free the memory
    return out;                                                                      // Return desired value
}

uint64_t pvec_remove(uint64_t *pvec, uint64_t index) {
    if (index >= pvec_getLength(pvec) - 1) {                                       // If we are removing the last element we can just pop it
        return pvec_pop(pvec);
    }
    // Get the pointers needed
    uint64_t *eleToRemove = pvec_getPointerToElement(pvec, index + 1);
    uint64_t *prevEle = pvec_getPointerToElement(pvec, index);
    uint64_t *nextEle = pvec_getPointerToElement(pvec, index + 2);
    uint64_t out = eleToRemove[1];                                                // Save the value to return
    prevEle[0] = (uint64_t) nextEle;                                              // Adjust the pointer saved in the previous element to reference the next element
    pvec[1]--;                                                                    // Adjust the length of the array
    free(eleToRemove);                                                            // Free the now unused memory
    return out;
}

void pvec_insert(uint64_t *pvec, uint64_t index, uint64_t val) {
    if (index >= pvec_getLength(pvec) - 1) {                                       // If we are insert the last element we can just append it
        pvec_append(pvec, val);
        return;
    }
    // Get the pointers needed
    uint64_t *prevEle = pvec_getPointerToElement(pvec, index);
    uint64_t *nextEle = pvec_getPointerToElement(pvec, index + 1);
    uint64_t *eleToAdd = calloc(2, sizeof(uint64_t));
    eleToAdd[0] = (uint64_t) nextEle;
    eleToAdd[1] = val;
    prevEle[0] = (uint64_t) eleToAdd;
    pvec[1]++;
}

uint64_t pvec_getValue(uint64_t *pvec, uint64_t index) {
    return pvec_getPointerToElement(pvec, index + 1)[1];          // Get the pointer to the block at the specified index, then get the value from that block
}

void pvec_setValue(uint64_t *pvec, uint64_t index, uint64_t val) {
    pvec_getPointerToElement(pvec, index + 1)[1] = val;           // Set the value in the appropriate block
}

void pvec_delete(uint64_t *pvec) {
    while (pvec_getLength(pvec) > 0) {                                // Pop every element
        pvec_pop(pvec);
    }
    free(pvec);                                                       // Free the initial block
}

void pvec_transferElement(uint64_t *pvec1, uint64_t index1, uint64_t *pvec2, uint64_t index2) {
    if (index1 > pvec_getLength(pvec1) - 1) {
        index1 = pvec_getLength(pvec1) - 1;
    }
    if (index2 > pvec_getLength(pvec2)) {
        index2 = pvec_getLength(pvec2);
    }
    // Get pointers to all involved memory locations
    uint64_t *elePrev1 = pvec_getPointerToElement(pvec1, index1);
    uint64_t *eleToTransfer = (uint64_t *) elePrev1[0];
    uint64_t *eleNext1 = (uint64_t *) eleToTransfer[0];
    uint64_t *elePrev2 = pvec_getPointerToElement(pvec2, index2);
    uint64_t *eleNext2 = (uint64_t *) elePrev2[0];
    // Update saved pointers
    elePrev1[0] = (uint64_t) eleNext1;                                          // Remove eleToTransfer from the first list
    elePrev2[0] = (uint64_t) eleToTransfer;                                     // Added eleToTransfer to the second list
    eleToTransfer[0] = (uint64_t) eleNext2;                                     // Add on the end of the second list
    // Adjust the lengths
    pvec1[1]--;
    pvec2[1]++;
}




