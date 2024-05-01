#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <raylib.h>
#include "core/defs.h"
#include "core/ball.h"
#include "core/paddle.h"
#include "core/cpu.h"
#include "core/collisions.h"
#include "argparse.h"

Color backgroundColor = { 46, 196, 182, 255 };
Color paddleColor = { 245, 247, 73, 255 };
Color ballColor = { 255, 51, 102, 255 };
Color textColor = { 255, 51, 102, 200 };

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
	      int screenHeight)
{
	BeginDrawing();

	// Updates paddle positions
	updateCPUPaddle(leftPaddle, ball, screenHeight);
	updatePlayerPaddle(rightPaddle, screenHeight);

	// Checks for collisions between ball and paddles
	resolveBallPaddleCollision(ball, leftPaddle, rightPaddle);

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

	// Seeds initial random number generator
	srand(time(NULL));
	while (!WindowShouldClose()) {
		gameLoop(&leftPaddle, &rightPaddle, &ball, &cpuScore,
			 &playerScore, screenWidth, screenHeight);
	}

	CloseWindow();
	return 0;
}
