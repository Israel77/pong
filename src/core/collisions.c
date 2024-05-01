#include "defs.h"
#include "ball.h"
#include "paddle.h"
#include "collisions.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

/**
 * checkCollisions - Check for collisions between ball and paddles
 * @ball: Pointer to ball object
 * @leftPaddle: Pointer to left paddle  
 * @rightPaddle: Pointer to right paddle
 */
void resolveBallPaddleCollision(Ball *ball, Paddle *leftPaddle,
				Paddle *rightPaddle)
{
	Vector2 ballPos = { ball->x, ball->y };

	bool didBallCollide =
		CheckCollisionCircleRec(
			ballPos, ball->radius,
			(Rectangle){ leftPaddle->x, leftPaddle->y,
				     leftPaddle->width, leftPaddle->height }) ||
		CheckCollisionCircleRec(
			ballPos, ball->radius,
			(Rectangle){ rightPaddle->x, rightPaddle->y,
				     rightPaddle->width, rightPaddle->height });

	if (didBallCollide) {
		if (ball->x < SCREEN_WIDTH / 2) {
			ball->speedX = fabs(ball->speedX);
		} else if (ball->x >= SCREEN_WIDTH / 2) {
			ball->speedX = -fabs(ball->speedX);
		}

		// Change ball y-direction slightly to make it more interesting
		int seed = rand() ^ time(NULL) ^ leftPaddle->y * 19 ^
			   rightPaddle->y * 257;
		int randomOffset = GetRandomValue(-5, 5);
		ball->speedY += randomOffset * 0.1;
	}
}