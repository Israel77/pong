#include <raylib.h>
#include "defs.h"
#include "ball.h"
#include "paddle.h"
#include "cpu.h"

void checkCollisions(Ball *ball, Paddle *leftPaddle, Paddle *rightPaddle)
{
	// Check collisions between ball and paddles
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
		ball->speedX *= -1;
	}
}

int main()
{
	Ball ball = { .x = SCREEN_WIDTH / 2,
		      .y = SCREEN_HEIGHT / 2,
		      .radius = 20.0f,
		      .speedX = BALL_SPEED,
		      .speedY = BALL_SPEED,
		      .color = WHITE };

	Paddle leftPaddle = { .x = PADDLE_OFFSET,
			      .y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2,
			      .width = PADDLE_WIDTH,
			      .height = PADDLE_HEIGHT,
			      .speed = PADDLE_SPEED };

	Paddle rightPaddle = { .x = SCREEN_WIDTH - PADDLE_OFFSET - PADDLE_WIDTH,
			       .y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2,
			       .width = PADDLE_WIDTH,
			       .height = PADDLE_HEIGHT,
			       .speed = PADDLE_SPEED };

	int playerScore = 0;
	int cpuScore = 0;

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
	SetTargetFPS(FPS);

	while (!WindowShouldClose()) {
		BeginDrawing();

		updateCPUPaddle(&leftPaddle, &ball, SCREEN_HEIGHT);
		updatePlayerPaddle(&rightPaddle, SCREEN_HEIGHT);
		updateBall(&ball, SCREEN_WIDTH, SCREEN_HEIGHT, &cpuScore,
			   &playerScore);

		checkCollisions(&ball, &leftPaddle, &rightPaddle);

		ClearBackground(BLACK);
		DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT,
			 WHITE);
		drawPaddle(&leftPaddle);
		drawPaddle(&rightPaddle);
		drawBall(&ball);
		DrawText(TextFormat("%i", cpuScore), SCREEN_WIDTH / 4, 30, 80,
			 WHITE);
		DrawText(TextFormat("%i", playerScore), SCREEN_WIDTH * 3 / 4,
			 30, 80, WHITE);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}