#include "Player.h"
#include "Food.h"

int WinMain(void) {

	InitWindow(500, 500, "Snek");
	SetTargetFPS(60);

	// create the player and fruit objects
	Player player = Player();
	Food food = Food();
	// spawn the fruit
	food.SpawnFruit();

	// custom timer variable
	float timer = 0.0;

	// window loop
	while (!WindowShouldClose()) {

		BeginDrawing();

		// if the player is not ded, then not ded
		if (!player.isDead) {


			ClearBackground(RAYWHITE);
			
			// now this is also cool, essentially every window update, it counts the time between each frame
			// once 1/3 of a second has passed, it then and only then updates the position of the snake. 
			// best way to get a consistent movement speed on all framerates
			timer += GetFrameTime();

			// yeye
			if (timer >= 0.33) {
				timer = 0;

				player.UpdatePos(&food);


			}

			// draw both the snake and the fruit
			player.Draw();
			food.Draw();



			EndDrawing();

			// movement stuff
			if (IsKeyDown(KEY_W) && player.currentDirection != DOWN)
				player.currentDirection = UP;

			if (IsKeyDown(KEY_D) && player.currentDirection != LEFT)
				player.currentDirection = RIGHT;

			if (IsKeyDown(KEY_S) && player.currentDirection != UP)
				player.currentDirection = DOWN;

			if (IsKeyDown(KEY_A) && player.currentDirection != RIGHT)
				player.currentDirection = LEFT;

		}
		else {
			// f
			player.DeathScreen();
		}
	}

	return 0;

}