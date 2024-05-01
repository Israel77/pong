#ifndef CPU_H
#define CPU_H

#include "../core/paddle.h"
#include "../core/ball.h"
#include "pid.h"

void updateCPUPaddle(Paddle *paddle, Ball *ball, int screenHeight);
void updateCPUPaddleWithController(Paddle *paddle, Ball *ball, int screenHeight,
				   PIDController *controller);
#endif