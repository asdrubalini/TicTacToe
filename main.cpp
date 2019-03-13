#include <iostream>

const int PLAYGROUND_SIZE = 9; // 3x3
unsigned const int PLAYER_ONE = -1;
unsigned const int PLAYER_TWO = 1;
unsigned const int NO_PLAYER = 0;

unsigned int playground[PLAYGROUND_SIZE] = {
	NO_PLAYER, NO_PLAYER, NO_PLAYER,
	NO_PLAYER, NO_PLAYER, NO_PLAYER,
	NO_PLAYER, NO_PLAYER, NO_PLAYER
};

unsigned const int* COMBINATIONS[8][3] = {
	// Rows
	{&playground[0], &playground[1], &playground[2]},
	{&playground[3], &playground[4], &playground[5]},
	{&playground[6], &playground[7], &playground[8]},

	// Columns
	{&playground[0], &playground[3], &playground[6]},
	{&playground[1], &playground[4], &playground[7]},
	{&playground[2], &playground[5], &playground[8]},

	// Diagonals
	{&playground[0], &playground[4], &playground[8]},
	{&playground[2], &playground[4], &playground[6]}
};

int check_tris() {
	// Check new tris
	unsigned int winner = NO_PLAYER;

	for (int i = 0; i < 8; i++) {
		unsigned const int *current[3] = {*COMBINATIONS[0], *COMBINATIONS[1], *COMBINATIONS[2]};
		unsigned int sum = *current[0] + *current[1] + *current[2];
		
		switch (sum) {
			case -3:
				winner = PLAYER_ONE;
				break;
			case 3:
				winner = PLAYER_TWO;
				break;
		}
	}

	return winner;
}

bool is_valid_move(int pos) {
	// Check if the desired move is valid or not
	unsigned int current = playground[pos];
	return (current == NO_PLAYER);
}

int add_move(int pos, unsigned int player) {
	playground[pos] = player;
}

void print_winner() {
	switch (check_tris()) {
		case PLAYER_ONE:
			std::cout << "Player one won" << std::endl;
			break;
		case PLAYER_TWO:
			std::cout << "Player two won" << std::endl;
			break;
		case NO_PLAYER:
			// Nobody won
			break;
	}
}

void print_playground() {
	for (int i = 0; i < sizeof(playground) / sizeof(playground[0]); i++) {
		printf("%d ", playground[i]);
		if (i % 3 == 2) {
			printf("\n");
		}
	}
}


int main()  {
	// We manually add a tris
	add_move(0, PLAYER_ONE);
	add_move(3, PLAYER_ONE);
	add_move(6, PLAYER_ONE);

	// Print playground and winner, which should is PLAYER_ONE
	print_playground();
	print_winner();

	std::cin.ignore();
    return 0;
}