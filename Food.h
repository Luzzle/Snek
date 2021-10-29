#pragma once

#include <random>
#include <time.h>
#include <raylib.h>

class Food {

public:
	int x;
	int y;

	// randomize the position of the fruit piece.
	void SpawnFruit() {
		time_t t;
		srand((unsigned)time(&t));

		x = rand() % 20;
		y = rand() % 20;
	}

	// draw the fruit piece
	void Draw() {
		DrawRectangle(x * 25 + 5, y * 25 + 5, 15, 15, RED);
	}
};