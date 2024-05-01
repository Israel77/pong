#ifndef ARENA_H
#define ARENA_H

#include "../core/ball.h"
#include "../core/paddle.h"
#include "../core/collisions.h"
#include "pid.h"

typedef struct {
	int leftScore;
	int rightScore;
} Result;

Result battle(PIDController *leftController, PIDController *rightController);

#endif