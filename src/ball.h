#ifndef BALL_H
#define BALL_H

#include <raylib.h>

typedef struct {
	int x;
	int y;
	float radius;
	int speedX;
	int speedY;
	Color color;
} Ball;

void drawBall(Ball *ball);
Ball resetBall(int screenWidth, int screenHeight);
void updateBall(Ball *ball, int screenWidth, int screenHeight, int *leftScore,
		int *rightScore);

#endif