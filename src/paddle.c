#include <raylib.h>
#include "paddle.h"

void drawPaddle(Paddle *paddle)
{
	DrawRectangle(paddle->x, paddle->y, paddle->width, paddle->height,
		      paddle->color);
}

// Clamps paddle height within the screen boundaries
void clampPaddleHeight(Paddle *paddle, int screenHeight)
{
	if (paddle->y < 0) {
		paddle->y = 0;
	} else if (paddle->y + paddle->height > screenHeight) {
		paddle->y = screenHeight - paddle->height;
	}
}

void updatePlayerPaddle(Paddle *paddle, int screenHeight)
{
	if (IsKeyDown(KEY_UP)) {
		paddle->y -= paddle->speed;
	}
	if (IsKeyDown(KEY_DOWN)) {
		paddle->y += paddle->speed;
	}

	clampPaddleHeight(paddle, screenHeight);
}
