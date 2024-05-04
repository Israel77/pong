#include "cpu.h"
#include "pid.h"
#include <stdio.h>
#include <stdio.h>
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

	// Avoid stalling
	const int DRAW_LIMIT = 5;
	const int FRAME_LIMIT = 7200;
	int framesSinceLastPoint = 0;
	int forcedResets = 0;

	// Seeds initial random number generator
	srand(time(NULL));
	while (player1Score < WINNING_SCORE && player2Score < WINNING_SCORE &&
	       forcedResets < DRAW_LIMIT) {
		// Updates paddle positions
		updateCPUPaddleWithController(&leftPaddle, &ball, screenHeight,
					      leftController);
		updateCPUPaddleWithController(&rightPaddle, &ball, screenHeight,
					      rightController);

		// Checks for collisions between ball and paddles
		resolveBallPaddleCollision(&ball, &leftPaddle, &rightPaddle);

		int _prevScore = player1Score + player2Score;
		// Updates ball position and checks for scoring
		updateBall(&ball, screenWidth, screenHeight, &player1Score,
			   &player2Score);

		if (_prevScore != player1Score + player2Score) {
			framesSinceLastPoint = 0;
		} else {
			framesSinceLastPoint++;
		}

		if (framesSinceLastPoint >= FRAME_LIMIT) {
			// printf("Stalling reached, resetting ball\n");
			ball = resetBall(screenWidth, screenHeight, ball.color);
			forcedResets++;
		}
	}

	// printf("Game over\n");
	return (Result){ .player1Score = player1Score,
			 .player2Score = player2Score,
			 .forcedFinish = forcedResets >= DRAW_LIMIT };
}