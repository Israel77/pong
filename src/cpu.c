#include "cpu.h"
#include "paddle.h"

void updateCPUPaddle(Paddle *paddle, Ball *ball, int screenHeight)
{
	const int PADDLE_CENTER = paddle->y + paddle->height / 2;

	if (ball->y > PADDLE_CENTER) {
		paddle->y += paddle->speed;
	} else if (ball->y < PADDLE_CENTER) {
		paddle->y -= paddle->speed;
	}

	clampPaddleHeight(paddle, screenHeight);
}
