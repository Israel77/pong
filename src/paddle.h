#ifndef PADDLE_H
#define PADDLE_H

#include <raylib.h>

typedef struct {
	int x;
	int y;
	int width;
	int height;
	int speed;
	Color color;
} Paddle;

void drawPaddle(Paddle *paddle);
void updatePlayerPaddle(Paddle *paddle, int screenHeight);
void clampPaddleHeight(Paddle *paddle, int screenHeight);

#endif