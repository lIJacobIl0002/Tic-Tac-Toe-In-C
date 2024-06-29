#include "bit.h"
#include <stdbool.h> // bro wtf? why is bool not builtin??
										 // this can't be real

bitset* create_bitset(size_t size) {
	bitset* bit = malloc(sizeof(bitset));
	bit->arr = calloc(sizeof(unsigned int), size);
	bit->size = size;


	return bit;
}

void set_bit(bitset* bitset, size_t idx) {
	bitset->arr[idx] = 1;
}

void print_bitset(bitset* bitset) {
	for(int i = 0; i < bitset->size; i++) {
		printf("%d", bitset->arr[i]);

		if((i+1) % 8 == 0) printf(" ");
	}
	printf("\n");
}

int test_bit(bitset* bitset, size_t idx) {
	if(bitset->size < idx) {
		printf("can't index %llu when bitset size is %llu", idx, bitset->size);
		exit(1);
	}

	return bitset->arr[idx];
}

void clear_bit(bitset* bitset, size_t idx) {
	if(bitset->size < idx) {
		printf("can't clear %llu when bitset size is %llu", idx, bitset->size);
		exit(1);
	}

	bitset->arr[idx] = 0;
}

//memory leaks everywhere OH MY GOD I HATE C
void bitset_or(bitset* dest, bitset* src, bitset* out) {
	for(int i = 0; i < dest->size; i++) {
		out->arr[i] = dest->arr[i] | src->arr[i];
	}
}

//fix this disgusting shit (I hate C)
void bitset_and(bitset* dest, bitset* src, bitset* out) {
	for(int i = 0; i < dest->size; i++) 
		out->arr[i] = dest->arr[i] & src->arr[i];	
}

bool bitset_equal(bitset* dest, bitset* src) {
	for(int i = 0; i < dest->size; i++)
		if(dest->arr[i] != src->arr[i])
			return false;

	return true;
}

// count the number bits
int bitset_count(bitset* dest) {
	int out = 0;
	for(int i = 0; i < dest->size; i++)
		out += dest->arr[i];

	return out;
}

void free_bitset(bitset* bitset) {
	free(bitset->arr);
	free(bitset);
}

