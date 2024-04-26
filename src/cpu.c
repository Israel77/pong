#include "cpu.h"

void updateCPUPaddle(Paddle *paddle, Ball *ball, int screenHeight)
{
	const int PADDLE_CENTER = paddle->y + paddle->height / 2;

	if (ball->y > PADDLE_CENTER) {
		paddle->y += paddle->speed;
		if (paddle->y + paddle->height > screenHeight)
			paddle->y = screenHeight - paddle->height;
	} else if (ball->y < PADDLE_CENTER) {
		paddle->y -= paddle->speed;
	}
}