#include "cpu.h"
#include "pid.h"
#include "../core/paddle.h"

// Function that returns 1 if number is positive or -1 if its negative
int _sign(float num)
{
	return (num > 0) - (num < 0);
}

// Default values for PID Controller
PIDController pidController = { .kp = 0.4f,
				.ki = 0.0f,
				.kd = 0.7f,
				.derivative = 0.0,
				.integral = 0.0,
				.prevError = 0.0 };

void updateCPUPaddle(Paddle *paddle, Ball *ball, int screenHeight)
{
	// Simple AI logic
	// const int PADDLE_CENTER = paddle->y + paddle->height / 2;
	// if (ball->y > PADDLE_CENTER) {
	// 	paddle->y += paddle->speed;
	// } else if (ball->y < PADDLE_CENTER) {
	// 	paddle->y -= paddle->speed;
	// }
	updateCPUPaddleWithController(paddle, ball, screenHeight,
				      &pidController);
}

void updateCPUPaddleWithController(Paddle *paddle, Ball *ball, int screenHeight,
				   PIDController *controller)
{
	const int PADDLE_CENTER = paddle->y + paddle->height / 2;

	float pError = ball->y - PADDLE_CENTER;
	float action = updatePIDController(&pidController, pError, 1);
	paddle->y += paddle->speed * _sign(action);

	clampPaddleHeight(paddle, screenHeight);
}
