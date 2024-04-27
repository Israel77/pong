#ifndef BALL_H
#define BALL_H

#include <raylib.h>

typedef struct {
	int x;
	int y;
	double radius;
	int speedX;
	int speedY;
	Color color;
} Ball;

void drawBall(Ball *ball);
Ball resetBall(int screenWidth, int screenHeight, Color color);
void updateBall(Ball *ball, int screenWidth, int screenHeight, int *leftScore,
		int *rightScore);

#endif