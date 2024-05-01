#ifndef PID_H
#define PID_H

typedef struct {
	double kp, ki, kd;
	double integral, derivative, prevError;
} PIDController;

void initPIDController(PIDController *controller, double kp, double ki,
		       double kd);

double updatePIDController(PIDController *controller, double error, double dt);

#endif