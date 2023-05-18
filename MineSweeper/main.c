#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

int showMap(char map[12][30], bool view[12][30]) {
	int n = 0;
	printf("\t");
	for (int i = 1; i < 31; i++) {
		if (i < 10)
			printf("%d ", i);
		else
			printf("%d ", i / 10);
	}
	printf("\n");
	printf("\t");
	for (int i = 1; i < 31; i++) {
		if (i >= 10)
			printf("%d ", i % 10);
		else
			printf("  ");
	}
	printf("\n\t___________________________________________________________\n");
	for (int i = 0; i < 12; i++) {
		printf("%d\t", i+1);
		for (int j = 0; j < 30; j++) {
			if (view[i][j] == true)
				printf("%c ", map[i][j]);
			else {
				printf("@ ");
				n++;
			}
		}
		printf("\n");
	}
	printf("\n");
	return n;
}

void showMapToLoser(char map[12][30]) {
	printf("\t");
	for (int i = 1; i < 31; i++) {
		if (i < 10)
			printf("%d ", i);
		else
			printf("%d ", i / 10);
	}
	printf("\n");
	printf("\t");
	for (int i = 1; i < 31; i++) {
		if (i >= 10)
			printf("%d ", i % 10);
		else
			printf("  ");
	}
	printf("\n\t___________________________________________________________\n");
	for (int i = 0; i < 12; i++) {
		printf("%d\t", i + 1);
		for (int j = 0; j < 30; j++) {
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void addProximities(char map[12][30], int proximities[12][30]) {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 30; j++) {
			proximities[i][j] = 0;
		}
	}

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 30; j++) {
			if (map[i][j] == '*') {
				if (i-1 >= 0) {
					if (j-1 >= 0) 
						proximities[i - 1][j - 1]++;
					if(j+1 <= 29)
						proximities[i - 1][j + 1]++;
					proximities[i - 1][j]++;
				}
				if (i+1 <= 11) {
					if(j-1 >= 0)
						proximities[i + 1][j - 1]++;
					if(j+1 <= 29)
						proximities[i + 1][j + 1]++;
					proximities[i + 1][j]++;
				}
				if(j-1 >= 0)
					proximities[i][j - 1]++;
				if(j+1 <= 29)
					proximities[i][j + 1]++;
			}
		}
	}

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 30; j++) {
			if (proximities[i][j] != 0 && map[i][j] != '*')
				map[i][j] = proximities[i][j] + '0';
		}
	}
}

int showNeighboring(int a, int b, bool view[12][30], char map[12][30], int proximities[12][30]) {
	if (view[a][b] == true) {
		printf("\n You already see it!! Try again");
		return 0;
	}
	if (map[a][b] != '*') {
		view[a][b] = true;
		if (proximities[a][b] == 0) {
			for (int i = 0; a - i >= 0 && map[a - i][b] != '*'; i++) {
				view[a - i][b] = true;
				if (proximities[a - i][b] != 0)
					break;
				for (int j = 0; b - j >= 0 && map[a - i][b - j] != '*'; j++) {
					view[a - i][b - j] = true;
					if (proximities[a - i][b - j] != 0)
						break;
				}
				for (int j = 0; b + j <= 29 && map[a - i][b + j] != '*'; j++) {
					view[a - i][b + j] = true;
					if (proximities[a - i][b + j] != 0)
						break;
				}
			}
			for (int i = 0; a + i <= 11 && map[a + i][b] != '*'; i++) {
				view[a + i][b] = true;
				if (proximities[a + i][b] != 0)
					break;
				for (int j = 0; b - j >= 0 && map[a + i][b - j] != '*'; j++) {
					view[a + i][b - j] = true;
					if (proximities[a + i][b - j] != 0)
						break;
				}
				for (int j = 0; b + j <= 29 && map[a + i][b + j] != '*'; j++) {
					view[a + i][b + j] = true;
					if (proximities[a + i][b + j] != 0)
						break;
				}
			}

			for (int i = 0; b - i >= 0 && map[a][b - i] != '*'; i++) {
				view[a][b - i] = true;
				if (proximities[a][b - i] != 0)
					break;
				for (int j = 0; a - j >= 0 && map[a - j][b - i] != '*'; j++) {
					view[a - j][b - i] = true;
					if (proximities[a - j][b - i] != 0)
						break;
				}
				for (int j = 0; a + j <= 11 && map[a + j][b - i] != '*'; j++) {
					view[a + j][b - i] = true;
					if (proximities[a + j][b - i] != 0)
						break;
				}
			}
			for (int i = 0; b + i <= 29 && map[a][b + i] != '*'; i++) {
				view[a][b + i] = true;
				if (proximities[a][b + i] != 0)
					break;
				for (int j = 0; a - j >= 0 && map[a - j][b + i] != '*'; j++) {
					view[a - j][b + i] = true;
					if (proximities[a - j][b + i] != 0)
						break;
				}
				for (int j = 0; a + j <= 11 && map[a + j][b + i] != '*'; j++) {
					view[a + j][b + i] = true;
					if (proximities[a + j][b + i] != 0)
						break;
				}
			}
			
			if (a - 1 >= 0) {
				if (b - 1 >= 0)
					if (map[a - 1][b - 1] != '*')
						view[a - 1][b - 1] = true;
				if (b + 1 <= 29)
					if (map[a - 1][b + 1] != '*')
						view[a - 1][b + 1] = true;
				if (map[a - 1][b] != '*')
					view[a - 1][b] = true;
			}
			if (a + 1 <= 11) {
				if (b - 1 >= 0)
					if (map[a + 1][b - 1] != '*')
						view[a + 1][b - 1] = true;
				if (b + 1 <= 29)
					if (map[a + 1][b + 1] != '*')
						view[a + 1][b + 1] = true;
				if (map[a + 1][b] != '*')
					view[a + 1][b] = true;
			}
			if (b - 1 >= 0)
				if (map[a][b - 1] != '*')
					view[a][b - 1] = true;
			if (b + 1 <= 29)
				if (map[a][b + 1] != '*')
					view[a][b + 1] = true;
					
		}
		return 1;
	}
	else
		return 1;
}

int checkForWin(bool view[12][30], char map[12][30]) {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 30; j++) {
			if (view[i][j] != true && map[i][j] != '*')
				return 0;
		}
	}
	return 1;
}

void clearMap(bool view[12][30], char map[12][30]) {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 30; j++) {
			map[i][j] = '.';
			view[i][j] = false;
		}
	}
}

int main() {
	char map[12][30];
	int proximities[12][30];
	bool view[12][30];
	int numBombs, diff;
	int numMoves, left = 0;
	int againNum;
	bool again = true;
	while (again) {
		againNum = -1;
		diff = 0;
		numMoves = 0;
		numBombs = 20;
		clearMap(view, map);

		printf("Hello! Choose a difficulty level (1 - easy, 2 - normal, 3 - hard): ");
		if (!scanf_s("%d", &diff)) {
			printf("No letters!\n");
			scanf_s("%*[^\n]");
		}

		while (diff > 3 || diff < 1) {
			printf("It's not an option! Choose a difficulty level (1 - easy, 2 - normal, 3 - hard): ");
			if (!scanf_s("%d", &diff)) {
				printf("No letters!\n");
				scanf_s("%*[^\n]");
			}
		}

		if (diff == 1) numBombs = 10;
		else if (diff == 3) numBombs = 30;

		srand(time(NULL));

		for (int i = 0; i < numBombs; i++) {
			int randX = rand() % 30;
			int randY = rand() % 12;
			if (map[randY][randX] == '.') {
				map[randY][randX] = '*';
			}
			else
				i--;
		}

		addProximities(map, proximities);
		int winOrLose = 0;
		int a, b;

		while (winOrLose == 0) {
			b = -1;
			printf("Your move ('a b' with a 1-12 and b 1-30): ");
			if (!scanf_s("%d %d", &a, &b)) {
				printf("Invalid! Try again\n");
				scanf_s("%*[^\n]");
				continue;
			}
			if (a < 1 || a > 12 || b < 1 || b > 30) {
				printf("Invalid! Try again\n");
				scanf_s("%*[^\n]");
				continue;
			}
			if (map[a - 1][b - 1] == '*') {
				numMoves++;
				winOrLose = -1;
				break;
			}
			else {
				numMoves += showNeighboring(a - 1, b - 1, view, map, proximities);
				printf("\n");
				left = showMap(map, view) - numBombs;
			}
			winOrLose = checkForWin(view, map);
		}

		if (winOrLose == -1) {
			if (left == 0) left = 12 * 30 - numBombs;
			printf("BOOOOOOOOOM!! You lost(\n");
			showMapToLoser(map);
		}

		else {
			printf("Congrats! You won\n");
		}

		

		printf("STATISCTICS \nNumber of moves: %d \nDifficulty: %s \nNumber of cells left: %d\n", numMoves, (diff == 1) ? "Easy (10 bombs)" : (diff == 2) ? "Normal (20 bombs)" : "Hard (30 bombs)", left);
		printf("Do you want to play again? (1 for 'yes', 0 for 'no'): ");
		
		
		if (!scanf_s("%d", &againNum)) {
			printf("No letters!\n");
			scanf_s("%*[^\n]");
		}

		while (againNum < 0 || againNum > 1) {
			printf("Please, choose between 1 (yes) and 0 (no): ");
			if (!scanf_s("%d", &againNum)) {
				printf("No letters!\n");
				scanf_s("%*[^\n]");
			}
		}

		if (againNum == 1) again = true;
		else again = false;
		
	}
	return 0;
}