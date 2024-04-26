#ifndef PADDLE_H
#define PADDLE_H

typedef struct {
	int x;
	int y;
	int width;
	int height;
	int speed;
} Paddle;

void drawPaddle(Paddle *paddle);
void updatePlayerPaddle(Paddle *paddle, int screenHeight);

#endif