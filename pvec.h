#include <stdio.h>
#include <stdlib.h>

#ifndef C_VECTOR_TESTS_PVEC_H
#define C_VECTOR_TESTS_PVEC_H

/**
 * Prints out a pvec
 * @param[in] pvec pvec to print
 */
void pvec_print(uint64_t *pvec);

/**
 * Creates a new pvec
 * @return pointer to pvec
 */
uint64_t * pvec_newPvec();

/**
 * Appends a new uint64_t to the pvec
 * @param[in,out] pvec pvec to append value to
 * @param[in] val value to append
 */
void pvec_append(uint64_t *pvec, uint64_t val);

/**
 * Removes the last element from the pvec
 * @param[in, out] pvec pvec to remove last element from
 * @return the element removed
 */
uint64_t pvec_pop(uint64_t *pvec);

/**
 * Inserts a value into a pvec at a specified index
 * @param[in, out] pvec pvec to insert into
 * @param[in] index index to insert into
 * @param[in] val value to insert
 */
void pvec_insert(uint64_t *pvec, uint64_t index, uint64_t val);

/**
 * Removes a value from a pvec at a specified index
 * @param[in, out] pvec pvec to remove from
 * @param[in] index index to remove from
 * @return value removed
 */
uint64_t pvec_remove(uint64_t *pvec, uint64_t index);

/**
 * Gets a value from the specified pvec
 * @param[in] pvec pvec to get value from
 * @param[in] index index to retrieve
 * @return value from pvec
 */
uint64_t pvec_getValue(uint64_t *pvec, uint64_t index);

/**
 * Sets a value in the specified pvec
 * @param[in, out] pvec pvec to set value to
 * @param[in] index index to set
 * @param[in] val value to set
 */
void pvec_setValue(uint64_t *pvec, uint64_t index, uint64_t val);

/**
 * Gets the length of a specified pvec
 * @param[in] pvec pvec to get length from
 * @return length of specified pvec
 */
uint64_t pvec_getLength(uint64_t *pvec);

/**
 * Deletes pvec by free memory used
 * @param pvec pvec to free
 */
void pvec_delete(uint64_t *pvec);

#endif //C_VECTOR_TESTS_PVEC_H
