#include <raylib.h>
#include "paddle.h"

void drawPaddle(Paddle *paddle)
{
	DrawRectangle(paddle->x, paddle->y, paddle->width, paddle->height,
		      WHITE);
}

void updatePlayerPaddle(Paddle *paddle, int screenHeight)
{
	if (IsKeyDown(KEY_UP)) {
		paddle->y -= paddle->speed;
		if (paddle->y < 0)
			paddle->y = 0;
	}
	if (IsKeyDown(KEY_DOWN)) {
		paddle->y += paddle->speed;
		if (paddle->y + paddle->height > screenHeight)
			paddle->y = screenHeight - paddle->height;
	}
}