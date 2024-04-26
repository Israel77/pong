#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include "defs.h"
#include "ball.h"

void drawBall(Ball *ball)
{
	DrawCircle((int)ball->x, (int)ball->y, ball->radius, ball->color);
}

Ball resetBall(int screenWidth, int screenHeight)
{
	Ball ball;

	const int angle = rand() * 2 * M_PI;
	const int speedX = BALL_SPEED * cos(angle);
	const int speedY = BALL_SPEED * sin(angle);

	ball.x = screenWidth / 2;
	ball.y = screenHeight / 2;
	ball.radius = BALL_RADIUS;
	ball.speedX = speedX;
	ball.speedY = speedY;
	ball.color = WHITE;

	return ball;
}

void updateBall(Ball *ball, int screenWidth, int screenHeight, int *leftScore,
		int *rightScore)
{
	ball->x += ball->speedX;
	ball->y += ball->speedY;

	// Check for screen boundaries and reverse direction if necessary
	if (ball->x - ball->radius <= 0) {
		ball->speedX *= -1;
		(*rightScore)++;
		*ball = resetBall(screenWidth, screenHeight);
	}

	if (ball->x + ball->radius >= screenWidth) {
		ball->speedX *= -1;
		(*leftScore)++;
		*ball = resetBall(screenWidth, screenHeight);
	}

	if (ball->y - ball->radius <= 0 ||
	    ball->y + ball->radius >= screenHeight) {
		ball->speedY *= -1;
	}
}
