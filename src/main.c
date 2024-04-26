#include <raylib.h>
#include "ball.h"
#include "paddle.h"

int main()
{
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 900;

	const int PADDLE_WIDTH = 15;
	const int PADDLE_HEIGHT = SCREEN_HEIGHT / 10;
	const int PADDLE_OFFSET = 30;

	const int FPS = 60;

	const float BALL_SPEED = 7.0f;
	const int PADDLE_SPEED = 10;

	Ball ball = { .x = SCREEN_WIDTH / 2,
		      .y = SCREEN_HEIGHT / 2,
		      .radius = 20.0f,
		      .speedX = BALL_SPEED,
		      .speedY = BALL_SPEED,
		      .color = WHITE };

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
	SetTargetFPS(FPS);

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

	while (!WindowShouldClose()) {
		ClearBackground(BLACK);
		BeginDrawing();

		updatePlayerPaddle(&rightPaddle, SCREEN_HEIGHT);
		updateBall(&ball, SCREEN_WIDTH, SCREEN_HEIGHT);

		drawPaddle(&leftPaddle);
		drawPaddle(&rightPaddle);
		drawBall(&ball);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}