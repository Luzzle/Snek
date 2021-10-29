#pragma once

#include <raylib.h>
#include "Vec2.h"
#include <vector>
#include "Food.h"
#include <string>

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};


class Player {

private:
	// Private Variables

	// Used within the draw function to represent if the snake has just ate a piece, so it can add an extra piece
	// to the snake next time it updates positions.
	bool justAte = false;

	int lastPieceX;
	int lastPieceY;

public:
	bool isDead = false;
	
	// Enum class that holds the current direction of the snake.
	Direction currentDirection = DOWN;

	// Array representing each position of each part of the snake. 
	std::vector<Vec2> snakeParts;

	Player() {
		// Initializer function, just adds 5 pieces to the snake at the start.
		snakeParts.push_back({ 0, 0 });
		snakeParts.push_back({ 1, 0 });
		snakeParts.push_back({ 2, 0 });
		snakeParts.push_back({ 3, 0 });
		snakeParts.push_back({ 4, 0 });
	}

	void Draw() {

		// Just loops through each snake part and draws it
		for (int i = 0; i < snakeParts.size(); i++) {
			DrawRectangle(snakeParts[i].x * 25, snakeParts[i].y * 25, 25, 25, BLACK);
			DrawRectangleLines(snakeParts[i].x * 25, snakeParts[i].y * 25, 25, 25, RED); // Draw rectangle outline

		}

		// Adds a new piece to the snake if it needs to
		if (justAte) {
			snakeParts.push_back({ lastPieceX, lastPieceY });
			justAte = false;
		}

	}

	// Speaks for itself ngl
	void DeathScreen() {
		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawText("YOU DIED", 130, 100, 50, BLACK);

		EndDrawing();
	}

	void CheckDeath() {
		// If snake head go into snake piece then ded
		for (int i = 1; i < snakeParts.size(); i++) {
			if (snakeParts[0].x == snakeParts[i].x && snakeParts[0].y == snakeParts[i].y) {
				isDead = true;
			}
		}
	}

	void UpdatePos(Food* fruit)
	{
		// ok this is where the code becomes interesting

		// stores the position of the last piece of the snake BEFORE it moves. Now u might be wondering why.
		// essentially whenever a new piece gets added it adds it into the OLD position of the previous last piece
		// of the snake, just avoids any annoying direction / collision bullfuckery (yes i know i swore im 18 im allowed)
		lastPieceX = snakeParts[snakeParts.size() - 1].x;
		lastPieceY = snakeParts[snakeParts.size() - 1].y;


		// moves the snake depending on the direction of the snake.
		switch (currentDirection) {

		case UP:
		{
			// ok so, im not gonna comment this for each other direction since its basically the same
			for (int i = snakeParts.size() - 1; i >= 0; i--) {
				if (i == 0)
					// if its the head of the snake, move the head in the current direction
				{
					snakeParts[i].y -= 1;

					// if the heads about to go offscreen (again this value changes depending on the direction)
					// it teleports it over to the other side of the screen, makes it look like its going around.
					if (snakeParts[i].y == -1)
						snakeParts[i].y = 19;

				}
				else {
					// if its not the head, the other body part assumes the position of the piece before it.
					// essentially this creates the effect of the snakes body following itself.
					snakeParts[i].x = snakeParts[i - 1].x;
					snakeParts[i].y = snakeParts[i - 1].y;
				}
			}

			break;
		}

		case LEFT:
		{

			for (int i = snakeParts.size() - 1; i >= 0; i--) {
				if (i == 0)
				{
					snakeParts[0].x -= 1;

					if (snakeParts[0].x == -1)
						snakeParts[0].x = 19;
				}
				else {
					snakeParts[i].x = snakeParts[i - 1].x;
					snakeParts[i].y = snakeParts[i - 1].y;
				}
			}

			break;
		}

		case DOWN:
		{
			
			for (int i = snakeParts.size() - 1; i >= 0; i--) {
				if (i == 0)
				{
					snakeParts[i].y += 1;

					if (snakeParts[i].y == 20)
						snakeParts[i].y = 0;

				}
				else {
					snakeParts[i].x = snakeParts[i - 1].x;
					snakeParts[i].y = snakeParts[i - 1].y;
				}
			}
			break;
		}

		case RIGHT:
		{
			for (int i = snakeParts.size() - 1; i >= 0; i--) {
				if (i == 0)
				{
					snakeParts[0].x += 1;

					if (snakeParts[0].x == 20)
						snakeParts[0].x = 0;

				}
				else {
					snakeParts[i].x = snakeParts[i - 1].x;
					snakeParts[i].y = snakeParts[i - 1].y;
				}
			}

			break;
		}
		}

		CheckDeath(); // speaks for itself

		// if the snakes head touches the fruit
		if (snakeParts[0].x == fruit->x && snakeParts[0].y == fruit->y) {
			
			bool insidePlayer = true;

			// create a new fruit
			fruit->SpawnFruit();

			while (insidePlayer) {
				
				for (int i = 0; i < snakeParts.size(); i++) {

					// if the new fruit thing is created inside of the snake, it then regenerates the random position
					// until its not inside the snake
					if (fruit->x == snakeParts[i].x && fruit->y == snakeParts[i].y) {
						fruit->SpawnFruit();
					}
					else {
						insidePlayer = false;
					}

				}

			}
			// the snek eat fruit
			justAte = true;
		}
	}


};


