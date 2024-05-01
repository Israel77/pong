#include "pid.h"

void initPIDController(PIDController *controller, double kp, double ki,
		       double kd)
{
	controller->kp = kp;
	controller->ki = ki;
	controller->kd = kd;
	controller->integral = 0.0;
	controller->derivative = 0.0;
	controller->prevError = 0.0;
}

double updatePIDController(PIDController *controller, double error, double dt)
{
	controller->integral += error * dt;
	controller->derivative = (error - controller->prevError) / dt;
	double output = controller->kp * error +
			controller->ki * controller->integral +
			controller->kd * controller->derivative;
	controller->prevError = error;
	return output;
}