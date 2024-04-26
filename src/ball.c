#include <raylib.h>
#include "ball.h"

void drawBall(Ball *ball)
{
	DrawCircle((int)ball->x, (int)ball->y, ball->radius, ball->color);
}

void updateBall(Ball *ball, int screenWidth, int screenHeight)
{
	ball->x += ball->speedX;
	ball->y += ball->speedY;

	// Check for screen boundaries and reverse direction if necessary
	if (ball->x - ball->radius <= 0 ||
	    ball->x + ball->radius >= screenWidth) {
		ball->speedX *= -1;
	}
	if (ball->y - ball->radius <= 0 ||
	    ball->y + ball->radius >= screenHeight) {
		ball->speedY *= -1;
	}
}