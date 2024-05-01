#include "cpu.h"
#include "pid.h"
#include "../core/paddle.h"

// Function that returns 1 if number is positive or -1 if its negative
int _sign(float num)
{
	return (num > 0) - (num < 0);
}

PIDController pidController = { .kp = 0.4f,
				.ki = 0.0f,
				.kd = 0.7f,
				.derivative = 0.0,
				.integral = 0.0,
				.prevError = 0.0 };

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

	float pError = ball->y - PADDLE_CENTER;
	float action = updatePIDController(&pidController, pError, 1);
	paddle->y += paddle->speed * _sign(action);

	clampPaddleHeight(paddle, screenHeight);
}
