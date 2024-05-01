#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "ball.h"
#include "paddle.h"

void resolveBallPaddleCollision(Ball *ball, Paddle *leftPaddle,
				Paddle *rightPaddle);

#endif