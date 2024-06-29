#include "bit.h"

bitset* createBitMask(int p1, int p2, int p3) {
	bitset* bit = create_bitset(9);

	set_bit(bit, p1);
	set_bit(bit, p2);
	set_bit(bit, p3);

	return bit;
}

// decide winner. (1 = X, 2 = O, 0 = draw, -1 = continue
int logic(bitset* xBoard, bitset* oBoard, bitset** bitmask, size_t size) {
	//can't do xBoard | oBoard without having some sort of memory leak
	//bro I miss classes 😭
	bitset* temp = create_bitset(9);

	for(int i = 0; i < size; i++) {
		bitset_and(xBoard, bitmask[i], temp);

		if(bitset_equal(temp, bitmask[i]))
			return 1;

		bitset_and(oBoard, bitmask[i], temp);

		if(bitset_equal(temp, bitmask[i]))
			return 2;
	}
	
	bitset_or(xBoard, oBoard, temp);

	//printf("%d", bitset_count(temp));
	if(bitset_count(temp) == 9) {
		return 0;
	}
	
	free_bitset(temp);

	return -1;
}

void draw(bitset* xBoard, bitset* oBoard) {
	for(int i = 0; i < 9; i++) {
		printf("%c | ", (test_bit(xBoard, i)) ? 'X' : (test_bit(oBoard, i)) ? 'O': i+'0'+1);

		if((i+1) % 3 == 0) printf("\n");
	}
}

void player_turn(char* plr, bitset* bit) {
	int loc;

	printf("Select a spot (1-9): ");
	scanf("%d", &loc);

	if(!(0 <= loc && loc <= 9)) {
		printf("INVALID!!");
		return;
	}

	set_bit(bit, loc-1);

	*plr = (*plr == 'X') ? 'O' : 'X';
}

int main() {
	bitset* xBoard = create_bitset(9);
	bitset* oBoard = create_bitset(9);
	char player = 'X';

	bitset* bitmask[] = {
		//rows
		createBitMask(0, 1, 2),
		createBitMask(3, 4, 5),
		createBitMask(6, 7, 8),

		//cols
		createBitMask(0, 3, 6),
		createBitMask(1, 4, 7),
		createBitMask(2, 5, 8),

		// diag
		createBitMask(0, 4, 8),
		createBitMask(6, 4, 2),
	};
	size_t size = sizeof(bitmask) / sizeof(bitset*);
	bool run = true;
	
	while(run) {
		draw(xBoard, oBoard);
		player_turn(&player, (player == 'X' ? xBoard : oBoard));
		
		switch(logic(xBoard, oBoard, bitmask, size)) {
			case 1:
				printf("X IS THE WINNER");
				run = false; break;

			case 2:
				printf("O IS THE WINNER");
				run = false; break;

			case 0:
				printf("DRAW!!");
				run = false; break;
		}
	}

	for(int i = 0; i < ( sizeof(bitmask) / sizeof(bitset*) ); i++) {
		free_bitset(bitmask[i]);
	}

	free_bitset(xBoard);
	free_bitset(oBoard);
}

