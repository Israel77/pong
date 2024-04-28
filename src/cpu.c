#include "cpu.h"
#include "paddle.h"

// Function that returns 1 if number is positive or -1 if its negative
int _sign(float num)
{
	return (num > 0) - (num < 0);
}

int lastYPosition = 0;
void updateCPUPaddle(Paddle *paddle, Ball *ball, int screenHeight)
{
	const int PADDLE_CENTER = paddle->y + paddle->height / 2;

	// Simple AI logic
	// if (ball->y > PADDLE_CENTER) {
	// 	paddle->y += paddle->speed;
	// } else if (ball->y < PADDLE_CENTER) {
	// 	paddle->y -= paddle->speed;
	// }

	// Implement a PID control system to smoothly track the ball's position
	static float pError = 0.0f, iError = 0.0f, dError = 0.0f;
	static const float kP = 0.4f, kI = 0.0f, kD = 0.7f;

	// Calculate the errors for the PID controller
	pError = ball->y - PADDLE_CENTER;
	iError += pError;
	dError = ball->y - lastYPosition;

	// Apply the PID control formula to update the paddle position
	paddle->y +=
		paddle->speed * _sign(kP * pError + kI * iError + kD * dError);

	clampPaddleHeight(paddle, screenHeight);
	lastYPosition = ball->y;
}
