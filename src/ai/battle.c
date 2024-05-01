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

	int player1Score = 0;
	int player2Score = 0;

	// Seeds initial random number generator
	srand(time(NULL));
	while (player1Score < WINNING_SCORE && player2Score < WINNING_SCORE) {
		// Updates paddle positions
		updateCPUPaddleWithController(&leftPaddle, &ball, screenHeight,
					      leftController);
		updateCPUPaddleWithController(&rightPaddle, &ball, screenHeight,
					      rightController);

		// Checks for collisions between ball and paddles
		resolveBallPaddleCollision(&ball, &leftPaddle, &rightPaddle);

		// Updates ball position and checks for scoring
		updateBall(&ball, screenWidth, screenHeight, &player1Score,
			   &player2Score);
	}

	return (Result){ .player1Score = player1Score,
			 .player2Score = player2Score };
}