#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <raylib.h>
#include "defs.h"
#include "ball.h"
#include "paddle.h"
#include "cpu.h"

Color backgroundColor = { 46, 196, 182, 255 };
Color paddleColor = { 245, 247, 73, 255 };
Color ballColor = { 255, 51, 102, 255 };
Color textColor = { 255, 51, 102, 200 };

/**
 * checkCollisions - Check for collisions between ball and paddles
 * @ball: Pointer to ball object
 * @leftPaddle: Pointer to left paddle  
 * @rightPaddle: Pointer to right paddle
 */
void checkCollisions(Ball *ball, Paddle *leftPaddle, Paddle *rightPaddle)
{
	Vector2 ballPos = { ball->x, ball->y };

	bool didBallCollide =
		CheckCollisionCircleRec(
			ballPos, ball->radius,
			(Rectangle){ leftPaddle->x, leftPaddle->y,
				     leftPaddle->width, leftPaddle->height }) ||
		CheckCollisionCircleRec(
			ballPos, ball->radius,
			(Rectangle){ rightPaddle->x, rightPaddle->y,
				     rightPaddle->width, rightPaddle->height });

	if (didBallCollide) {
		if (ball->x < SCREEN_WIDTH / 2) {
			ball->speedX = fabs(ball->speedX);
		} else if (ball->x >= SCREEN_WIDTH / 2) {
			ball->speedX = -fabs(ball->speedX);
		}

		// Change ball y-direction slightly to make it more interesting
		int randomOffset = GetRandomValue(-5, 5);
		ball->speedY += randomOffset * 0.1;
	}
}

/**
 * gameLoop - Main game loop
 * @leftPaddle: Pointer to left CPU paddle
 * @rightPaddle: Pointer to right player paddle  
 * @ball: Pointer to ball object
 * @cpuScore: Pointer to CPU's score
 * @playerScore: Pointer to player's score
 * @screenWidth: Width of screen
 * @screenHeight: Height of screen
 * @seed: Pointer to seed for random number generator
 */
void gameLoop(Paddle *leftPaddle, Paddle *rightPaddle, Ball *ball,
	      int *cpuScore, int *playerScore, int screenWidth,
	      int screenHeight, unsigned int *seed)
{
	BeginDrawing();

	// Updates paddle positions
	updateCPUPaddle(leftPaddle, ball, screenHeight);
	updatePlayerPaddle(rightPaddle, screenHeight);

	// Seed the random number generator with a unique value
	*seed ^= time(NULL) ^ leftPaddle->y * 19 ^ rightPaddle->y * 257 ^
		 (*cpuScore * 37 + *playerScore * 97);
	srand(*seed);

	// Checks for collisions between ball and paddles
	checkCollisions(ball, leftPaddle, rightPaddle);

	// Updates ball position and checks for scoring
	updateBall(ball, screenWidth, screenHeight, cpuScore, playerScore);

	// Draws the game elements
	ClearBackground(backgroundColor);
	DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
	drawPaddle(leftPaddle);
	drawPaddle(rightPaddle);
	drawBall(ball);
	DrawText(TextFormat("%i", *cpuScore), screenWidth / 4, 30, 80,
		 textColor);
	DrawText(TextFormat("%i", *playerScore), screenWidth * 3 / 4, 30, 80,
		 textColor);

	EndDrawing();
}

/**
 * parseArgs - Parse command line arguments for screen dimensions  
 * @argc: Number of arguments
 * @argv: Argument strings
 * @screenWidth: Pointer to screen width value
 * @screenHeight: Pointer to screen height value
 */
void parseArgs(int argc, char *argv[], int *screenWidth, int *screenHeight)
{
	if (argc < 1)
		return;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--width") == 0 && i + 1 < argc) {
			*screenWidth = atoi(argv[i + 1]);
		} else if (strcmp(argv[i], "--height") == 0 && i + 1 < argc) {
			*screenHeight = atoi(argv[i + 1]);
		}
	}
}

/**
 * main - Entry point for the game
 */
int main(int argc, char *argv[])
{
	int screenWidth = SCREEN_WIDTH;
	int screenHeight = SCREEN_HEIGHT;

	parseArgs(argc, argv, &screenWidth, &screenHeight);

	Paddle leftPaddle = { .x = PADDLE_OFFSET,
			      .y = screenHeight / 2 - PADDLE_HEIGHT / 2,
			      .width = PADDLE_WIDTH,
			      .height = PADDLE_HEIGHT,
			      .speed = PADDLE_SPEED,
			      .color = paddleColor };

	Paddle rightPaddle = { .x = screenWidth - PADDLE_OFFSET - PADDLE_WIDTH,
			       .y = screenHeight / 2 - PADDLE_HEIGHT / 2,
			       .width = PADDLE_WIDTH,
			       .height = PADDLE_HEIGHT,
			       .speed = PADDLE_SPEED,
			       .color = paddleColor };

	Ball ball = resetBall(screenWidth, screenHeight, ballColor);

	int playerScore = 0;
	int cpuScore = 0;

	InitWindow(screenWidth, screenHeight, "Pong");
	SetTargetFPS(60);

	unsigned int seed = time(NULL);
	while (!WindowShouldClose()) {
		gameLoop(&leftPaddle, &rightPaddle, &ball, &cpuScore,
			 &playerScore, screenWidth, screenHeight, &seed);
	}

	CloseWindow();
	return 0;
}
