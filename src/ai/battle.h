#ifndef ARENA_H
#define ARENA_H

#include "../core/ball.h"
#include "../core/paddle.h"
#include "../core/collisions.h"

// Function pointer to a function that can update the paddle position
// based on the ball position
typedef void (*PaddleUpdateFunction)(Paddle *paddle, Ball *ball,
				     int screenHeight);
;

typedef struct {
	int leftScore;
	int rightScore;
} Result;

Result battle(PaddleUpdateFunction leftController,
	      PaddleUpdateFunction rightController);

#endif