
#ifndef BIT_H
#define BIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // this is so tragic 😭

#define BITS_PER_WORD (sizeof(unsigned int) * 8)
#define BITSET_SIZE(n) ((n + BITS_PER_WORD - 1) / BITS_PER_WORD)

typedef struct {
    unsigned int *arr;
    size_t size;
} bitset;

bitset *create_bitset(size_t num_bits);
void free_bitset(bitset *bitset);
void set_bit(bitset *bitset, size_t index);
void clear_bit(bitset *bitset, size_t index);
int test_bit(bitset *bitset, size_t index);
void print_bitset(bitset *bitset);
void bitset_or(bitset *dest, bitset *src, bitset* out);
void bitset_and(bitset *dest, bitset *src, bitset* out);
int bitset_count(bitset *dest);
bool bitset_equal(bitset *dest, bitset *srg);

#endif // BIT_H
