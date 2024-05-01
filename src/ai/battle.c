#include "cpu.h"
#include "pid.h"
#include <time.h>
#include <stdlib.h>
#include "../core/defs.h"
#include "battle.h"

// Simulates the main game loop without the drawing functionality
Result battle(PIDController *leftController, PIDController *rightController)
{
	const int WINNING_SCORE = 30;
	int screenWidth = SCREEN_WIDTH;
	int screenHeight = SCREEN_HEIGHT;

	Paddle leftPaddle = { .x = PADDLE_OFFSET,
			      .y = screenHeight / 2 - PADDLE_HEIGHT / 2,
			      .width = PADDLE_WIDTH,
			      .height = PADDLE_HEIGHT,
			      .speed = PADDLE_SPEED,
			      .color = WHITE };

	Paddle rightPaddle = { .x = screenWidth - PADDLE_OFFSET - PADDLE_WIDTH,
			       .y = screenHeight / 2 - PADDLE_HEIGHT / 2,
			       .width = PADDLE_WIDTH,
			       .height = PADDLE_HEIGHT,
			       .speed = PADDLE_SPEED,
			       .color = WHITE };

	Ball ball = resetBall(screenWidth, screenHeight, WHITE);

	int leftScore = 0;
	int rightScore = 0;

	// Seeds initial random number generator
	srand(time(NULL));
	while (leftScore < WINNING_SCORE && rightScore < WINNING_SCORE) {
		// Updates paddle positions
		updateCPUPaddleWithController(&leftPaddle, &ball, screenHeight,
					      leftController);
		updateCPUPaddleWithController(&rightPaddle, &ball, screenHeight,
					      rightController);

		// Checks for collisions between ball and paddles
		resolveBallPaddleCollision(&ball, &leftPaddle, &rightPaddle);

		// Updates ball position and checks for scoring
		updateBall(&ball, screenWidth, screenHeight, &leftScore,
			   &rightScore);
	}

	return (Result){ .leftScore = leftScore, .rightScore = rightScore };
}