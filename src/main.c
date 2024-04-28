#include <math.h>
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

// Check collisions between ball and paddles
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

int main()
{
	Paddle leftPaddle = { .x = PADDLE_OFFSET,
			      .y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2,
			      .width = PADDLE_WIDTH,
			      .height = PADDLE_HEIGHT,
			      .speed = PADDLE_SPEED,
			      .color = paddleColor };

	Paddle rightPaddle = { .x = SCREEN_WIDTH - PADDLE_OFFSET - PADDLE_WIDTH,
			       .y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2,
			       .width = PADDLE_WIDTH,
			       .height = PADDLE_HEIGHT,
			       .speed = PADDLE_SPEED,
			       .color = paddleColor };

	Ball ball = resetBall(SCREEN_WIDTH, SCREEN_HEIGHT, ballColor);

	int playerScore = 0;
	int cpuScore = 0;

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
	SetTargetFPS(FPS);

	unsigned int seed = time(NULL) ^ leftPaddle.y ^ rightPaddle.y;
	while (!WindowShouldClose()) {
		BeginDrawing();

		updateCPUPaddle(&leftPaddle, &ball, SCREEN_HEIGHT);
		updatePlayerPaddle(&rightPaddle, SCREEN_HEIGHT);

		// Seed the random number generator with a unique value
		seed ^= time(NULL) ^ leftPaddle.y * 19 ^ rightPaddle.y * 257 ^
			(cpuScore * 37 + playerScore * 97);
		srand(seed);

		checkCollisions(&ball, &leftPaddle, &rightPaddle);
		updateBall(&ball, SCREEN_WIDTH, SCREEN_HEIGHT, &cpuScore,
			   &playerScore);

		ClearBackground(backgroundColor);
		DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT,
			 WHITE);
		drawPaddle(&leftPaddle);
		drawPaddle(&rightPaddle);
		drawBall(&ball);
		DrawText(TextFormat("%i", cpuScore), SCREEN_WIDTH / 4, 30, 80,
			 textColor);
		DrawText(TextFormat("%i", playerScore), SCREEN_WIDTH * 3 / 4,
			 30, 80, textColor);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}